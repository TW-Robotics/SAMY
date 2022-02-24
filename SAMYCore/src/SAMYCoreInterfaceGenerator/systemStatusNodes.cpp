#include <samycoreInterfaceGenerator.h>

namespace SAMY {
/*
 * We add the system status variables as source nodes, so when we read or write this nodes, we modify the underlying variable node.
 * With this approach we cannot use subscription to automatically notice when a variable node was modified
UA_StatusCode SAMYCoreInterfaceGenerator::readStatusVariableCallback(
        UA_Server* server,
        const UA_NodeId* sessionId,
        void* sessionContext,
        const UA_NodeId* nodeId,
        void* nodeContext,
        UA_Boolean sourceTimeStamp,
        const UA_NumericRange* range,
        UA_DataValue* dataValue
) {
    if (!nodeContext)
        return UA_STATUSCODE_BADINTERNALERROR;

    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    auto* sourceNodeId = static_cast<UA_NodeId*>(nodeContext);
    retval |= UA_Server_readValue( server, *sourceNodeId, &dataValue->value );
    if( retval != UA_STATUSCODE_GOOD )
        return UA_STATUSCODE_BADINTERNALERROR;

    dataValue->hasValue = true;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode SAMYCoreInterfaceGenerator::writeStatusVariableCallback(
        UA_Server *server,
        const UA_NodeId *sessionId,
        void *sessionContext,
        const UA_NodeId *nodeId,
        void *nodeContext,
        const UA_NumericRange *range,
        const UA_DataValue *dataValue
) {
    if (!nodeContext)
        return UA_STATUSCODE_BADINTERNALERROR;

    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    auto* sourceNodeId = static_cast<UA_NodeId*>(nodeContext);

    retval |= UA_Server_writeValue( server, *sourceNodeId, dataValue->value  );

    if( retval != UA_STATUSCODE_GOOD )
        return UA_STATUSCODE_BADINTERNALERROR;

    return UA_STATUSCODE_GOOD;
}


UA_StatusCode SAMYCoreInterfaceGenerator::addDataSourcesToSystemStatusVariable( UA_Server *server,
                                                                                std::pair<UA_NodeId, std::string>& nodeAndName ){
    UA_Int16 systemStatusNS = UA_Server_addNamespace( server, "http://SAMY.org/SystemStatus");
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( nodeAndName.second.c_str() ) );
    vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( nodeAndName.second.c_str() ) );
    retval |= UA_Server_readDataType( server, nodeAndName.first, &vattr.dataType );
    if( retval != UA_STATUSCODE_GOOD )
        return UA_STATUSCODE_BADINTERNALERROR;

    UA_QualifiedName browseName = UA_QUALIFIEDNAME(systemStatusNS, const_cast<char*>( nodeAndName.second.c_str() ) );
    UA_NodeId parentNodeId = systemStatusObjectNodeId;
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC( 0, UA_NS0ID_HASCOMPONENT );
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_PROPERTYTYPE);
    UA_NodeId variableNodeId = UA_NODEID_NULL;

    UA_DataSource dataSource{};
    dataSource.write = &SAMYCoreInterfaceGenerator::writeStatusVariableCallback;
    dataSource.read = &SAMYCoreInterfaceGenerator::readStatusVariableCallback;
    retval |= UA_Server_addVariableNode(server,
                                        UA_NODEID_NUMERIC(systemStatusNS, 0),
                                        parentNodeId,
                                        parentReferenceNodeId,
                                        browseName,
                                        variableTypeNodeId,
                                        vattr,
                                        NULL,
                                        &variableNodeId
                                        );

        retval |= UA_Server_setNodeContext(server, variableNodeId, reinterpret_cast<void*>( &nodeAndName.first ) );
    if (retval != UA_STATUSCODE_GOOD)
        return retval;
    retval = UA_Server_setVariableNode_dataSource(server, variableNodeId, dataSource);
    if (retval != UA_STATUSCODE_GOOD)
        return retval;

    return retval;
}
*/

UA_StatusCode SAMYCoreInterfaceGenerator::addSystemStatusObject(UA_Server *server){

    UA_Int16 systemStatusNS = UA_Server_addNamespace( server, "http://SAMY.org/SystemStatus");
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;

    UA_NodeId systemStatusNodeId = UA_NODEID_NULL;
    UA_ObjectAttributes attr = UA_ObjectAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>("SystemStatus") );
    attr.description = UA_LOCALIZEDTEXT("", const_cast<char*>("This object contain all the information "
                                                              "required for describing in real time the status of the system.") );
    retVal |= UA_Server_addNode_begin( server, UA_NODECLASS_OBJECT,
    UA_NODEID_NUMERIC(systemStatusNS, 0),
    UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER),
    UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
    UA_QUALIFIEDNAME(systemStatusNS, const_cast<char*>( "SystemStatus" ) ),
    UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
    (const UA_NodeAttributes*)&attr, &UA_TYPES[UA_TYPES_OBJECTATTRIBUTES], NULL, &systemStatusNodeId);

    retVal |= UA_Server_addNode_finish( server, systemStatusNodeId );

    if (retVal != UA_STATUSCODE_GOOD)
        return retVal;

    systemStatusObjectNodeId = systemStatusNodeId;
    logger->info("SystemStatus node succesfully added: ns={} i={}", systemStatusNodeId.namespaceIndex, systemStatusNodeId.identifier.numeric);
    return retVal;
}


UA_StatusCode SAMYCoreInterfaceGenerator::addSystemStatusNodesToServer( UA_Server *server ){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    retval |= addSystemStatusObject( server );
    UA_Int16 systemStatusNS = UA_Server_addNamespace( server, "http://SAMY.org/SystemStatus");

    for( auto& nodeAndName : systemStatusNodesAndNames ){
         std::stringstream msg2;
         msg2 <<"NSIndex: " << nodeAndName.first.namespaceIndex << "   "
              << nodeAndName.first.identifier.numeric << "   " << nodeAndName.second;

         logger->debug(msg2.str());

         UA_VariableAttributes vattr = UA_VariableAttributes_default;
         vattr.valueRank = UA_VALUERANK_SCALAR;
         vattr.accessLevel = UA_ACCESSLEVELMASK_READ;
         UA_LocalizedText_init( &vattr.description );
         UA_LocalizedText_init( &vattr.displayName );
         vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( nodeAndName.second.c_str() ) );
         vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( nodeAndName.second.c_str() ) );
         vattr.dataType = UA_TYPES[UA_TYPES_NODEID].typeId;
         UA_Variant_setScalar(  &vattr.value, &nodeAndName.first, &UA_TYPES[UA_TYPES_NODEID]);

         if( retval != UA_STATUSCODE_GOOD )
             return UA_STATUSCODE_BADINTERNALERROR;

         UA_QualifiedName browseName = UA_QUALIFIEDNAME(systemStatusNS, const_cast<char*>( nodeAndName.second.c_str() ) );
         UA_NodeId parentNodeId = systemStatusObjectNodeId;
         UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC( 0, UA_NS0ID_HASCOMPONENT );
         UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_PROPERTYTYPE);
         UA_NodeId variableNodeId = UA_NODEID_NULL;

         retval |= UA_Server_addVariableNode(server,
                                             UA_NODEID_NUMERIC(systemStatusNS, 0),
                                             parentNodeId,
                                             parentReferenceNodeId,
                                             browseName,
                                             variableTypeNodeId,
                                             vattr,
                                             NULL,
                                             &variableNodeId
                                             );

         if (retval != UA_STATUSCODE_GOOD)
             throw std::runtime_error("COULD NOT ADD A NODE TO THE SYSTEM STATUS OBJECT. ABORTING...");
     }
    return retval;
}

}

