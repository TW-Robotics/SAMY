/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE', which is part of this source code package.
 *
 *    Copyright (c) 2020 fortiss GmbH, Stefan Profanter
 *    All rights reserved.
 */

#include <utility>

//
// Created by profanter on 12/4/18.
// Copyright (c) 2018 fortiss GmbH. All rights reserved.
//

#ifndef ROBOTICS_COMMON_OPCUA_HELPER_H
#define ROBOTICS_COMMON_OPCUA_HELPER_H
#pragma once

#include <future>
#include <sys/stat.h>

#ifdef UA_ENABLE_AMALGAMATION
#include "open62541.h"
#else

#include <open62541/server_config_default.h>
#include <open62541/client.h>
#include <open62541/plugin/pki_default.h>
#include <open62541/plugin/accesscontrol_default.h>

#if ((UA_OPEN62541_VER_MAJOR >= 1) && (UA_OPEN62541_VER_MINOR >= 1))
#include <open62541/plugin/nodestore_default.h>
#endif


#if ((UA_OPEN62541_VER_MAJOR >= 1) && (UA_OPEN62541_VER_MINOR >= 1))
#include <open62541/plugin/nodestore_default.h>
#endif

#include <open62541/client_config_default.h>

#endif

#include <logging_opcua.h>

#include <exception>
#include <spdlog/spdlog.h>
#include <sstream>

#include <fortiss_di_nodeids.h>

#define NAMESPACE_URI_DI "http://opcfoundation.org/UA/DI/"
#define NAMESPACE_URI_ROB "http://opcfoundation.org/UA/Robotics/"
#define NAMESPACE_URI_FOR_DI "https://fortiss.org/UA/Device/"
#define NAMESPACE_URI_FOR_ROB "https://fortiss.org/UA/Robotics/"


#ifndef RAD_TO_DEG
#define RAD_TO_DEG (180.0/M_PI)
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD (M_PI/180.0)
#endif

#include <synchronized.hpp>
#include <map>
#include <set>
#include <OpcUaServer.h>

typedef locked_ptr<UA_Client, std::mutex> LockedClient;
typedef synchronized<UA_Client> MutexedClient;

namespace SAMY {
    namespace OPCUA {
        class NodeNotFoundException : public std::exception {
        private:
            std::string message_;
        public:
            explicit NodeNotFoundException(
                    const std::string& nodeId,
                    const std::string& additionalInfo = ""
            ){
                message_ = "OPC UA NodeNotFound Exception: " + nodeId;

                if (additionalInfo.length())
                    message_ += " " + additionalInfo;
            }

            const char* what() const noexcept override {
                return message_.c_str();
            }
        };


        class StatusCodeException : public std::exception {
        private:
            UA_StatusCode code;
            std::string msg_;

        public:
            explicit StatusCodeException(
                    UA_StatusCode code,
                    const std::string& msg = ""
            ) : code(code){
                msg_ = "StatusCode: " + std::string(UA_StatusCode_name(code));

                if (msg.length())
                    msg_ += ". " + msg;
            }

            const char* what() const noexcept override {
                return msg_.c_str();
            }

            UA_StatusCode get_code() const { return code; }

            std::string get_msg() const { return msg_; }
        };

        template<typename PROMISE_TYPE>
        inline std::future<PROMISE_TYPE> setPromiseErrorException(
                std::promise<PROMISE_TYPE>* promise,
                UA_StatusCode code
        ){
            try {
                throw SAMY::OPCUA::StatusCodeException(code);
            } catch (SAMY::OPCUA::StatusCodeException& ex){
                promise->set_exception(std::current_exception());
                return promise->get_future();
            }
        }

        // use recursive mutex to allow multiple locks within the same thread, but not between different threads
        static std::recursive_mutex serverMutex;

        inline UA_StatusCode
        UA_ServerConfig_setUriName(
                UA_ServerConfig* uaServerConfig,
                const char* uri,
                const char* name
        ){
            // delete pre-initialized values
            UA_String_deleteMembers(&uaServerConfig->applicationDescription.applicationUri);
            UA_LocalizedText_deleteMembers(&uaServerConfig->applicationDescription.applicationName);

            std::string opcUaUri(uri);
            std::string opcUaName(name);

            uaServerConfig->applicationDescription.applicationUri = UA_String_fromChars(opcUaUri.c_str());
            uaServerConfig->applicationDescription.applicationName.locale = UA_STRING_NULL;
            uaServerConfig->applicationDescription.applicationName.text = UA_String_fromChars(opcUaName.c_str());

            for (size_t i = 0; i < uaServerConfig->endpointsSize; i++){
                UA_String_deleteMembers(&uaServerConfig->endpoints[i].server.applicationUri);
                UA_LocalizedText_deleteMembers(
                        &uaServerConfig->endpoints[i].server.applicationName);

                UA_String_copy(&uaServerConfig->applicationDescription.applicationUri,
                               &uaServerConfig->endpoints[i].server.applicationUri);

                UA_LocalizedText_copy(&uaServerConfig->applicationDescription.applicationName,
                                      &uaServerConfig->endpoints[i].server.applicationName);
            }

            return UA_STATUSCODE_GOOD;
        }

        inline const std::shared_ptr<UA_NodeId> UA_Server_getObjectChildId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName childName,
                const UA_NodeId reference
        ){
            UA_RelativePathElement rpe;
            UA_RelativePathElement_init(&rpe);
            rpe.referenceTypeId = reference;
            rpe.isInverse = false;
            rpe.includeSubtypes = false;
            rpe.targetName = childName;

            UA_BrowsePath bp;
            UA_BrowsePath_init(&bp);
            bp.startingNode = objectId;
            bp.relativePath.elementsSize = 1;
            bp.relativePath.elements = &rpe;

            UA_StatusCode retval;
            UA_BrowsePathResult bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
            retval = bpr.statusCode;
            if (retval != UA_STATUSCODE_GOOD || bpr.targetsSize < 1){
                UA_BrowsePathResult_deleteMembers(&bpr);
                std::string qualifiedName = "ns=" + std::to_string(childName.namespaceIndex) + ";"
                                            + std::string(reinterpret_cast<char const*>(childName.name.data),
                                                          childName.name.length);
                std::string errorMessage = std::string(UA_StatusCode_name(retval));
                throw SAMY::OPCUA::NodeNotFoundException(qualifiedName, errorMessage);
            }

            UA_NodeId* nodeId = UA_NodeId_new();

            UA_NodeId_copy(&bpr.targets[0].targetId.nodeId, nodeId);

            UA_BrowsePathResult_deleteMembers(&bpr);

            return std::shared_ptr<UA_NodeId>(nodeId, UA_NodeId_delete);
        }

        inline const std::shared_ptr<UA_NodeId> UA_Server_getObjectChildId(
                const std::shared_ptr<OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName childName,
                const UA_NodeId reference
        ){
            LockedServer ls = uaServer->getLocked();
            return UA_Server_getObjectChildId(ls.get(), objectId, childName, reference);

        }

        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ){
            return UA_Server_getObjectChildId(server, objectId, componentName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
        }

        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId(
                const std::shared_ptr<SAMY::OPCUA::OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ){
            return UA_Server_getObjectChildId(uaServer, objectId, componentName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
        }

        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId_or_Null(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ){
            try {
                return UA_Server_getObjectChildId(server, objectId, componentName,
                                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
            } catch (SAMY::OPCUA::NodeNotFoundException& ex){
                return NULL;
            }
        }

        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectComponentId_or_Null(
                const std::shared_ptr<SAMY::OPCUA::OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName componentName
        ){
            try {
                return UA_Server_getObjectChildId(uaServer, objectId, componentName,
                                                  UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
            } catch (SAMY::OPCUA::NodeNotFoundException& ex){
                return NULL;
            }

        }

        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectPropertyId(
                UA_Server* server,
                const UA_NodeId objectId,
                const UA_QualifiedName propertyName
        ){
            return UA_Server_getObjectChildId(server, objectId, propertyName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY));
        }


        inline const std::shared_ptr<UA_NodeId>
        UA_Server_getObjectPropertyId(
                const std::shared_ptr<SAMY::OPCUA::OpcUaServer>& uaServer,
                const UA_NodeId objectId,
                const UA_QualifiedName propertyName
        ){
            return UA_Server_getObjectChildId(uaServer, objectId, propertyName,
                                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY));
        }


        namespace {
            struct UA_Server_nodeIterFindChildOfType_Data {
                UA_Server* server;
                const UA_NodeId* typeToFindId;
                UA_NodeId* foundNodeId;
                bool found;
            };

            UA_StatusCode
            UA_Server_nodeIterFindChildOfType(
                    UA_NodeId childId,
                    UA_Boolean isInverse,
                    UA_NodeId referenceTypeId,
                    void* handle
            ){

                struct UA_Server_nodeIterFindChildOfType_Data* data = (struct UA_Server_nodeIterFindChildOfType_Data*) (handle);
                if (data->found)
                    return UA_STATUSCODE_GOOD;

                /* Verify that we have a reference to the node from the objects folder */
                UA_BrowseDescription bd;
                UA_BrowseDescription_init(&bd);
                bd.nodeId = childId;
                bd.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASTYPEDEFINITION);
                bd.browseDirection = UA_BROWSEDIRECTION_FORWARD;

                UA_BrowseResult br = UA_Server_browse(data->server, 0, &bd);
                if (br.statusCode == UA_STATUSCODE_GOOD && br.referencesSize > 0){
                    for (size_t i = 0; i < br.referencesSize; i++){
                        if (UA_NodeId_equal(&(br.references[i].nodeId.nodeId), data->typeToFindId)){
                            UA_NodeId_copy(&childId, data->foundNodeId);
                            data->found = true;
                            break;
                        }
                    }
                }

                UA_BrowseResult_deleteMembers(&br);
                return UA_STATUSCODE_GOOD;
            }
        }


        inline bool UA_Server_findChildOfType(
                UA_Server* server,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& nodeTypeDefinition,
                UA_NodeId* foundNodeId
        ){


            struct UA_Server_nodeIterFindChildOfType_Data handle = {
                    server,
                    &nodeTypeDefinition,
                    foundNodeId,
                    false
            };

            UA_StatusCode ret = UA_Server_forEachChildNodeCall(server, parent, &UA_Server_nodeIterFindChildOfType, &handle);

            if (ret != UA_STATUSCODE_GOOD)
                return false;

            return handle.found;
        }

        inline bool UA_NodeId_parse(
                const std::string& nodeId,
                UA_NodeId* id
        ){
            UA_NodeId_clear(id);

            std::string idStr = nodeId;
            id->namespaceIndex = 0;
            if (nodeId.rfind("ns=", 0) == 0){
                size_t pos = nodeId.find_first_of(';');
                if (pos <= 0)
                    return false;
                id->namespaceIndex = (UA_UInt16) strtol(nodeId.substr(3, pos - 3).c_str(), NULL, 10);
                idStr = nodeId[pos + 1];
            }

            if (idStr.rfind("i=", 0) == 0){
                id->identifierType = UA_NODEIDTYPE_NUMERIC;
                id->identifier.numeric = (UA_UInt32) strtol(idStr.substr(2).c_str(), NULL, 10);
            } else if (idStr.rfind("s=", 0) == 0){
                id->identifierType = UA_NODEIDTYPE_STRING;
                id->identifier.string = UA_STRING_ALLOC(idStr.substr(2).c_str());
                if (!id->identifier.string.data)
                    return false;
            } else {
                // TODO implement for GUID and ByteString
                throw std::runtime_error("NodeID Parser not implemented for: " + idStr);
            }
            return true;

        }

        inline bool UA_Server_findChildOfType(
                const std::shared_ptr<SAMY::OPCUA::OpcUaServer>& server,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& nodeTypeDefinition,
                UA_NodeId* foundNodeId
        ){
            LockedServer ls = server->getLocked();
            return UA_Server_findChildOfType(ls.get(), logger, parent, nodeTypeDefinition, foundNodeId);
        }

        inline UA_StatusCode UA_Client_getNamespacesMap(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                std::map<std::string, UA_UInt16>& namespaceMap
        ){
            UA_ReadRequest request;
            UA_ReadRequest_init(&request);
            UA_ReadValueId id;
            UA_ReadValueId_init(&id);
            id.attributeId = UA_ATTRIBUTEID_VALUE;
            id.nodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_NAMESPACEARRAY);
            request.nodesToRead = &id;
            request.nodesToReadSize = 1;

            UA_ReadResponse response = UA_Client_Service_read(client, request);

            UA_StatusCode retval = UA_STATUSCODE_GOOD;
            if (response.responseHeader.serviceResult != UA_STATUSCODE_GOOD)
                retval = response.responseHeader.serviceResult;
            else if (response.resultsSize != 1 || !response.results[0].hasValue)
                retval = UA_STATUSCODE_BADNODEATTRIBUTESINVALID;
            else if (response.results[0].value.type != &UA_TYPES[UA_TYPES_STRING])
                retval = UA_STATUSCODE_BADTYPEMISMATCH;

            if (retval != UA_STATUSCODE_GOOD){
                UA_ReadResponse_deleteMembers(&response);
                return retval;
            }

            UA_String* ns = (UA_String*) response.results[0].value.data;
            for (size_t i = 0; i < response.results[0].value.arrayLength; ++i){

                std::string nsStr = std::string((char*) ns[i].data, ns[i].length);
                namespaceMap[nsStr] = (UA_UInt16) i;
            }

            UA_ReadResponse_deleteMembers(&response);
            return retval;

        }

        inline bool UA_Client_findChildOfType(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& nodeTypeDefinition,
                UA_NodeId* foundNodeId
        ){
            UA_NodeId_clear(foundNodeId);

            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parent, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            bool found = false;
            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_NodeId_equal(&ref->typeDefinition.nodeId, &nodeTypeDefinition)){
                            if (!UA_NodeId_isNull(foundNodeId)){
                                found = false;
                                break;
                            }
                            UA_NodeId_copy(&ref->nodeId.nodeId, foundNodeId);
                            found = true;
                        }
                    }
                }
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
            return found;
        }

        inline bool UA_Client_nodeHasInterface(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& interfaceTypeDefinition
        ){
            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parent, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            const UA_NodeId hasInterface = UA_NODEID_NUMERIC(0, UA_NS0ID_HASINTERFACE);

            bool found = false;

            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize && !found; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_NodeId_equal(&ref->referenceTypeId, &hasInterface) &&
                            UA_NodeId_equal(&ref->nodeId.nodeId, &interfaceTypeDefinition)){
                            found = true;
                            break;
                        }
                    }
                }
            }
            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);

            return found;
        }

        inline bool UA_Client_findChildHavingInterface(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& interfaceTypeDefinition,
                UA_NodeId* foundNodeId
        ){
            UA_NodeId_clear(foundNodeId);

            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parent, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            bool found = false;
            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_Client_nodeHasInterface(client, logger, ref->nodeId.nodeId, interfaceTypeDefinition)){
                            if (!UA_NodeId_isNull(foundNodeId)){
                                found = false;
                                break;
                            }
                            UA_NodeId_copy(&ref->nodeId.nodeId, foundNodeId);
                            found = true;
                        }
                    }
                }
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
            return found;
        }

        inline bool UA_Client_findChildrenOfType(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& nodeTypeDefinition,
                UA_NodeId** foundNodeId,
                size_t* foundNodeIdSize
        ){
            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parent, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            std::vector<UA_NodeId*> tmpIds;

            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
                return false;
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_NodeId_equal(&ref->typeDefinition.nodeId, &nodeTypeDefinition)){
                            tmpIds.push_back(&ref->nodeId.nodeId);
                        }
                    }
                }
            }

            *foundNodeId = (UA_NodeId*) UA_Array_new(tmpIds.size(), &UA_TYPES[UA_TYPES_NODEID]);
            *foundNodeIdSize = 0;
            for (UA_NodeId* const& value: tmpIds){
                UA_NodeId_copy(value, &(*foundNodeId)[(*foundNodeIdSize)++]);
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);

            return true;
        }


        inline bool UA_Client_findChildrenImplementingInterfaceRecursively(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId* parentNodes,
                size_t parentNodesSize,
                const UA_NodeId& interfaceTypeId,
                std::vector<std::shared_ptr<UA_NodeId>>& foundIds
        ){
            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = (UA_BrowseDescription*) UA_Array_new(parentNodesSize, &UA_TYPES[UA_TYPES_BROWSEDESCRIPTION]);
            bReq.nodesToBrowseSize = parentNodesSize;
            for (size_t i = 0; i < parentNodesSize; i++){
                UA_NodeId_copy(&parentNodes[i], &(bReq.nodesToBrowse[i].nodeId));
                bReq.nodesToBrowse[i].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            }

            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);


            std::vector<UA_NodeId*> recursiveContinue;

            UA_NodeId organizesId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
            UA_NodeId hasInterfaceId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASINTERFACE);
            UA_NodeId hasComponentId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);

            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
                return false;
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    bool checkChildren = true;
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);
                        if (UA_NodeId_equal(&ref->referenceTypeId, &hasInterfaceId) && UA_NodeId_equal(&ref->nodeId.nodeId, &interfaceTypeId)){
                            UA_NodeId* foundId = UA_NodeId_new();
                            UA_NodeId_copy(&parentNodes[i], foundId);
                            foundIds.push_back(std::shared_ptr<UA_NodeId>(foundId, UA_NodeId_delete));
                            checkChildren = false;
                            break;
                        }
                    }
                    for (size_t j = 0; checkChildren && j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);
                        if (UA_NodeId_equal(&ref->referenceTypeId, &organizesId) || UA_NodeId_equal(&ref->referenceTypeId, &hasComponentId)){
                            recursiveContinue.push_back(&ref->nodeId.nodeId);
                        }
                    }
                }
            }

            UA_NodeId* recursiveParents = (UA_NodeId*) UA_Array_new(recursiveContinue.size(), &UA_TYPES[UA_TYPES_NODEID]);
            size_t recursiveParentsSize = 0;
            for (UA_NodeId* const& value: recursiveContinue){
                UA_NodeId_copy(value, &recursiveParents[recursiveParentsSize++]);
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);


            if (recursiveParentsSize > 0){
                UA_Client_findChildrenImplementingInterfaceRecursively(client, logger, recursiveParents, recursiveParentsSize, interfaceTypeId, foundIds);
            }

            UA_Array_delete(recursiveParents, recursiveContinue.size(), &UA_TYPES[UA_TYPES_NODEID]);

            return foundIds.size() > 0;
        }

        inline void UA_Client_findChildrenWithReferenceType(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId parent,
                const UA_NodeId& referenceTypeDefinition,
                UA_NodeId** foundNodeId,
                size_t* foundNodeIdSize
        ){
            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parent, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            std::vector<UA_NodeId*> tmpIds;

            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_NodeId_equal(&ref->referenceTypeId, &referenceTypeDefinition)){
                            tmpIds.push_back(&ref->nodeId.nodeId);
                        }
                    }
                }
            }

            *foundNodeId = (UA_NodeId*) UA_Array_new(tmpIds.size(), &UA_TYPES[UA_TYPES_NODEID]);
            *foundNodeIdSize = 0;
            for (UA_NodeId* const& value: tmpIds){
                UA_NodeId_copy(value, &(*foundNodeId)[(*foundNodeIdSize)++]);
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
        }

        inline bool UA_Client_findChildWithBrowseName(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId& parentNode,
                const UA_QualifiedName& browseName,
                UA_NodeId* foundNodeId
        ){
            UA_NodeId_clear(foundNodeId);

            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parentNode, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            bool found = false;
            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_QualifiedName_equal(&ref->browseName, &browseName)){
                            if (!UA_NodeId_isNull(foundNodeId)){
                                found = false;
                                break;
                            }
                            UA_NodeId_copy(&ref->nodeId.nodeId, foundNodeId);
                            found = true;
                        }
                    }
                }
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
            return found;
        }

        inline bool UA_Client_findBrowsePath(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId& parentNode,
                std::vector<UA_QualifiedName>& browsePath,
                UA_NodeId* foundNodeId
        ){
            UA_NodeId_clear(foundNodeId);

            UA_BrowsePath browsePathReq;
            UA_BrowsePath_init(&browsePathReq);
            browsePathReq.startingNode = parentNode;
            size_t pathCount = browsePath.size();
            browsePathReq.relativePath.elements = (UA_RelativePathElement*) UA_Array_new(pathCount, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
            browsePathReq.relativePath.elementsSize = pathCount;

            for (size_t i = 0; i < pathCount; i++){
                UA_RelativePathElement* elem = &browsePathReq.relativePath.elements[i];
                elem->referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
                if (const UA_StatusCode ret = UA_QualifiedName_copy(&browsePath.at(i), &elem->targetName) != UA_STATUSCODE_GOOD){
                    logger->error("Error copying: {}", UA_StatusCode_name(ret));
                    return false;
                }
            }

            UA_TranslateBrowsePathsToNodeIdsRequest request;
            UA_TranslateBrowsePathsToNodeIdsRequest_init(&request);
            request.browsePaths = &browsePathReq;
            request.browsePathsSize = 1;

            UA_TranslateBrowsePathsToNodeIdsResponse response = UA_Client_Service_translateBrowsePathsToNodeIds(client, request);
            UA_BrowsePath_deleteMembers(&browsePathReq);

            if (response.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("translateBrowsePathsToNodeIds failed with: {}", UA_StatusCode_name(response.responseHeader.serviceResult));
                UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);
                return false;
            }
            if (response.resultsSize != 1){
                logger->error("translateBrowsePathsToNodeIds did not get any results: {}", UA_StatusCode_name(response.responseHeader.serviceResult));
                UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);
                return false;
            }

            UA_BrowsePathResult* res = &response.results[0];

            if (res->statusCode != UA_STATUSCODE_GOOD){
                logger->error("translateBrowsePathsToNodeIds got statuscode: {}", UA_StatusCode_name(res->statusCode));
                UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);
                return false;
            }

            UA_NodeId_copy(&res->targets[0].targetId.nodeId, foundNodeId);

            UA_TranslateBrowsePathsToNodeIdsResponse_deleteMembers(&response);
            return true;
        }

        inline bool UA_Client_findChildWithName(
                UA_Client* client,
                const std::shared_ptr<spdlog::logger>& logger,
                const UA_NodeId& parentNode,
                const UA_String& name,
                UA_NodeId* foundNodeId
        ){
            UA_NodeId_clear(foundNodeId);

            UA_BrowseRequest bReq;
            UA_BrowseRequest_init(&bReq);
            bReq.requestedMaxReferencesPerNode = 0;
            bReq.nodesToBrowse = UA_BrowseDescription_new();
            bReq.nodesToBrowseSize = 1;
            UA_NodeId_copy(&parentNode, &(bReq.nodesToBrowse[0].nodeId));
            bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
            UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

            bool found = false;
            if (bResp.responseHeader.serviceResult != UA_STATUSCODE_GOOD){
                logger->error("Can not browse server for children. Error {}",
                              UA_StatusCode_name(bResp.responseHeader.serviceResult));
            } else {
                for (size_t i = 0; i < bResp.resultsSize; ++i){
                    for (size_t j = 0; j < bResp.results[i].referencesSize; ++j){
                        UA_ReferenceDescription* ref = &(bResp.results[i].references[j]);

                        if (UA_String_equal(&ref->browseName.name, &name)){
                            if (!UA_NodeId_isNull(foundNodeId)){
                                found = false;
                                break;
                            }
                            UA_NodeId_copy(&ref->nodeId.nodeId, foundNodeId);
                            found = true;
                        }
                    }
                }
            }

            UA_BrowseRequest_clear(&bReq);
            UA_BrowseResponse_clear(&bResp);
            return found;
        }

        inline UA_UInt16 UA_Server_getNamespaceIdByName(
                UA_Server* uaServer,
                const char* nsid
        ){
            size_t nsIdTmp = 0;
            UA_String nsUri = UA_String_fromChars(nsid);
            UA_StatusCode retval = UA_Server_getNamespaceByName(uaServer, nsUri, &nsIdTmp);
            UA_String_clear(&nsUri);
            if (retval != UA_STATUSCODE_GOOD){
                throw std::runtime_error("Could not find server namespace: " + std::string(nsid));
            }
            return (UA_UInt16) nsIdTmp;
        }

        inline UA_UInt16 UA_Server_getNamespaceIdByName(
                const std::shared_ptr<SAMY::OPCUA::OpcUaServer>& uaServer,
                const char* nsid
        ){
            LockedServer ls = uaServer->getLocked();
            return UA_Server_getNamespaceIdByName(ls.get(), nsid);
        }

        /*
         * Get the endpoint from the server, where we can call RegisterServer2 (or RegisterServer).
         * This is normally the endpoint with highest supported encryption mode.
         *
         * @param discoveryServerUrl The discovery url from the remote server
         * @return The endpoint description (which needs to be freed) or NULL
         */
        inline
        UA_EndpointDescription* UA_Helper_getRegisterEndpointFromServer(
                const char* discoveryServerUrl,
                const std::shared_ptr<spdlog::logger>& logger,
                bool supportEncryption = true
        ){
            UA_Client* client = UA_Client_new();
            UA_ClientConfig* clientConfig = UA_Client_getConfig(client);
            clientConfig->logger.log = SAMY::Logging::opcua::UA_Log_Spdlog_log;
            clientConfig->logger.context = logger.get();
            clientConfig->logger.clear = SAMY::Logging::opcua::UA_Log_Spdlog_clear;
            UA_ClientConfig_setDefault(clientConfig);
            UA_EndpointDescription* endpointArray = NULL;
            size_t endpointArraySize = 0;
            UA_StatusCode retval = UA_Client_getEndpoints(client, discoveryServerUrl,
                                                          &endpointArraySize, &endpointArray);
            if (retval != UA_STATUSCODE_GOOD){
                UA_Array_delete(endpointArray, endpointArraySize,
                                &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
                logger->error("GetEndpoints failed with {}", UA_StatusCode_name(retval));
                UA_Client_delete(client);
                return NULL;
            }

            const UA_ByteString UA_SECURITY_POLICY_BASIC128_URI =
                    {56, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15")};
            const UA_ByteString UA_SECURITY_POLICY_BASIC256_URI =
                    {51, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic256")};
            const UA_ByteString UA_SECURITY_POLICY_BASIC256_SHA256_URI =
                    {57, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256")};

            UA_EndpointDescription* foundEndpoint = NULL;
            unsigned short foundPolicyPriority = 0;
            unsigned short foundSecurityModePriority = 0;
            for (size_t i = 0; i < endpointArraySize; i++){

                unsigned short policyPriority = 0;
                unsigned short securityModePriority = 0;

                policyPriority = UA_String_equal(&endpointArray[i].securityPolicyUri, &UA_SECURITY_POLICY_NONE_URI) ? 10 : policyPriority;

                securityModePriority = endpointArray[i].securityMode == UA_MESSAGESECURITYMODE_NONE ? 10 : securityModePriority;

                if (supportEncryption){
                    policyPriority = UA_String_equal(&endpointArray[i].securityPolicyUri, &UA_SECURITY_POLICY_BASIC128_URI) ? 20 : policyPriority;
                    policyPriority = UA_String_equal(&endpointArray[i].securityPolicyUri, &UA_SECURITY_POLICY_BASIC256_URI) ? 30 : policyPriority;
                    policyPriority = UA_String_equal(&endpointArray[i].securityPolicyUri, &UA_SECURITY_POLICY_BASIC256_SHA256_URI) ? 40 : policyPriority;

                    securityModePriority = endpointArray[i].securityMode == UA_MESSAGESECURITYMODE_SIGN ? 20 : securityModePriority;
                    securityModePriority = endpointArray[i].securityMode == UA_MESSAGESECURITYMODE_SIGNANDENCRYPT ? 30 : securityModePriority;
                }


                // find the endpoint with highest supported security mode
                if ((foundEndpoint == NULL) ||
                    (policyPriority > foundPolicyPriority) ||
                    (securityModePriority > foundSecurityModePriority)){
                    foundEndpoint = &endpointArray[i];
                    foundPolicyPriority = policyPriority;
                }
            }
            UA_EndpointDescription* returnEndpoint = NULL;
            if (foundEndpoint != NULL){
                returnEndpoint = UA_EndpointDescription_new();
                UA_EndpointDescription_copy(foundEndpoint, returnEndpoint);
            }
            UA_Array_delete(endpointArray, endpointArraySize,
                            &UA_TYPES[UA_TYPES_ENDPOINTDESCRIPTION]);
            UA_Client_delete(client);
            return returnEndpoint;
        }


        inline bool fileExists(const std::string& path){
            struct stat buffer;
            return (stat(path.c_str(), &buffer) == 0);
        }

        /* loadFile parses the certificate file.
         *
         * @param  path               specifies the file name given in argv[]
         * @return Returns the file content after parsing */
        inline UA_ByteString
        loadBinaryFile(const std::string& path){

            if (!fileExists(path)){
                throw std::runtime_error("File not found: " + path);
            }

            UA_ByteString fileContents = UA_STRING_NULL;

            /* Open the file */
            FILE* fp = fopen(path.c_str(), "rb");
            if (!fp){
                errno = 0; /* We read errno also from the tcp layer... */
                return fileContents;
            }

            /* Get the file length, allocate the data and read */
            fseek(fp, 0, SEEK_END);
            fileContents.length = (size_t) ftell(fp);
            fileContents.data = (UA_Byte*) UA_malloc(fileContents.length * sizeof(UA_Byte));
            if (fileContents.data){
                fseek(fp, 0, SEEK_SET);
                size_t read = fread(fileContents.data, sizeof(UA_Byte), fileContents.length, fp);
                if (read != fileContents.length)
                    UA_ByteString_clear(&fileContents);
            } else {
                fileContents.length = 0;
            }
            fclose(fp);

            return fileContents;
        }

        inline UA_StatusCode
        initServerConfig(
                const std::shared_ptr<spdlog::logger>& logger,
                UA_ServerConfig* config,
                const std::string& appUri,
                const std::string& appName,
                UA_UInt16 serverPort,
                bool enableEncryption,
                bool allowAnonymous,
                const std::string& certFiles,
                UA_UInt32 sendBufferSize = 0,
                UA_UInt32 recvBufferSize = 0
        ){

            memset(config, 0, sizeof(UA_ServerConfig));

            config->logger.log = SAMY::Logging::opcua::UA_Log_Spdlog_log;
            config->logger.context = logger.get();
            config->logger.clear = SAMY::Logging::opcua::UA_Log_Spdlog_clear;

            UA_StatusCode retval = UA_ServerConfig_setBasics(config);
            if (retval != UA_STATUSCODE_GOOD){
                logger->error("Can not set server configuration. Basics. {}", UA_StatusCode_name(retval));
                return retval;
            }

            if (retval != UA_STATUSCODE_GOOD){
                logger->error("Cannot initilaize nodestore for server config. {}", UA_StatusCode_name(retval));
            }
            retval = UA_ServerConfig_addNetworkLayerTCP(config, serverPort, sendBufferSize, recvBufferSize);

            if (retval != UA_STATUSCODE_GOOD){
                logger->error("Can not set server configuration. AddNetworkLayer. {}", UA_StatusCode_name(retval));
                return retval;
            }

            // Encryption disabled
            if (enableEncryption){
#ifdef UA_ENABLE_ENCRYPTION
                std::string certFile = certFiles + "_cert.der";
                std::string keyFile = certFiles + "_key.der";

                // Load certificate and private key
                UA_ByteString certificate = SAMY::OPCUA::loadBinaryFile(certFile);
                UA_ByteString privateKey = SAMY::OPCUA::loadBinaryFile(keyFile);

                // Load the trustlist
                // TODO for now we do not use trustlists
                size_t trustListSize = 0;
                UA_ByteString* trustList = NULL;
                //for(size_t i = 0; i < trustListSize; i++)
                //    trustList[i] = loadFile(argv[i+3]);


                // Loading of a issuer list, not used in this application
                size_t issuerListSize = 0;
                UA_ByteString* issuerList = NULL;

                // Loading of a revocation list currently unsupported
                UA_ByteString* revocationList = NULL;
                size_t revocationListSize = 0;

                retval = UA_CertificateVerification_Trustlist(&config->certificateVerification,
                                                              trustList, trustListSize,
                                                              issuerList, issuerListSize,
                                                              revocationList, revocationListSize);
                if (retval != UA_STATUSCODE_GOOD){
                    logger->error("Can not set server configuration. TrustList. {}", UA_StatusCode_name(retval));
                    return retval;
                }

                // None is required for browsing the endpoints
                retval = UA_ServerConfig_addSecurityPolicyNone(config, &certificate);
                if (retval != UA_STATUSCODE_GOOD){
                    logger->error("Can not set server configuration. AddSecurityPolicyNone. {}", UA_StatusCode_name(retval));
                    return retval;
                }

                retval = UA_ServerConfig_addSecurityPolicyBasic256(config, &certificate, &privateKey);
                if (retval != UA_STATUSCODE_GOOD){
                    logger->error("Can not set server configuration. SecurityPolicyBasic256. {}", UA_StatusCode_name(retval));
                    return retval;
                }
                retval = UA_ServerConfig_addSecurityPolicyBasic256Sha256(config, &certificate, &privateKey);
                if (retval != UA_STATUSCODE_GOOD){
                    logger->error("Can not set server configuration. SecurityPolicyBasic256Sha256. {}", UA_StatusCode_name(retval));
                    return retval;
                }

                UA_ByteString_clear(&certificate);
                UA_ByteString_clear(&privateKey);
#else
                logger->error("Can not set server configuration with encryption. UA_ENABLE_ENCRYPTION is false");
                return UA_STATUSCODE_BADNOTSUPPORTED;
#endif

            } else {
                /* Allocate the SecurityPolicies */
                retval = UA_ServerConfig_addSecurityPolicyNone(config, NULL);
                if (retval != UA_STATUSCODE_GOOD){
                    logger->error("Can not set server configuration. AddSecurityPolicyNone. {}", UA_StatusCode_name(retval));
                    return retval;
                }
      //      }

            //TODO for now we use a static username and password. On the long run we could use LDAP or similar.

            UA_String username = UA_STRING_ALLOC("demo");
            UA_String password = UA_STRING_ALLOC("demo#PWD");
            static const size_t usernamePasswordsSize = 1;
            static UA_UsernamePasswordLogin usernamePasswords[1] = {
                    {.username = username,
                            .password = password}};

            /* Initialize the Access Control plugin */
            retval = UA_AccessControl_default(config, allowAnonymous,
                                              &config->securityPolicies[config->securityPoliciesSize - 1].policyUri,
                                              usernamePasswordsSize, usernamePasswords);
            UA_String_clear(&username);
            UA_String_clear(&password);
            if (retval != UA_STATUSCODE_GOOD){
                logger->error("Can not set server configuration. AccessControl. {}", UA_StatusCode_name(retval));
                return retval;
            }

            retval = UA_ServerConfig_addAllEndpoints(config);
            if (retval != UA_STATUSCODE_GOOD){
                logger->error("Can not set server configuration. AddEndpoint. {}", UA_StatusCode_name(retval));
                return retval;
            }

            SAMY::OPCUA::UA_ServerConfig_setUriName(config, appUri.c_str(),
                                                       appName.c_str());

            return UA_STATUSCODE_GOOD;
        }

        static const UA_ByteString UA_SECURITY_POLICY_BASIC128_URI =
                {56, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15")};
        const UA_ByteString UA_SECURITY_POLICY_BASIC256_URI =
                {51, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic256")};
        const UA_ByteString UA_SECURITY_POLICY_BASIC256_SHA256_URI =
                {57, (UA_Byte*) const_cast<char*>("http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256")};

    }
}
}


#endif //ROBOTICS_COMMON_OPCUA_HELPER_H
