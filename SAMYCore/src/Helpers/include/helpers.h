#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <variant>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>

//#include <crcl_nodeids.h>
#include <namespace_crcl_generated.h>
#include <types_crcl_generated_handling.h>
#include <ProgramState.h>
#include <ProgramTransition.h>

#define CRCLSKILLS_NODE_ID 9999

namespace SAMY {

template <typename T>
class FiniteDeque{
    public:
        FiniteDeque(const int size): maxSize(size){}
        const std::deque<T>& getDeque(){return deque;}
        const std::int32_t getMaxSize(){return maxSize;}
        std::int32_t getSize(){return deque.size();}
        void addElement(const T& elem){
            if( deque.size() == 100 ){
                deque.pop_front();
                deque.push_back(elem);
            }else{
                deque.push_back(elem);
            }
        }
    private:
        std::deque<T> deque;
        std::int32_t maxSize = 100;
};

inline std::vector< std::pair< std::string, UA_NodeId> > UA_Server_getNodeComponents( UA_Server* server,
                                                                                    const UA_NodeId& parentNode ){
    std::vector< std::pair< std::string, UA_NodeId> > retVal;

    UA_BrowseDescription bDes;
    UA_BrowseDescription_init(&bDes);
    bDes.nodeId = parentNode;
    bDes.resultMask = UA_BROWSERESULTMASK_ALL;
    UA_BrowseResult bRes = UA_Server_browse(server, 0, &bDes);

    for( int i = 0; i < bRes.referencesSize; i++ ){
        /* Sometimes the array of data contains after the relevant data non-zero characters that produce a weird behaviour.
           Using pointers and the actual size we can initialize correctly the corresponding string */
        std::string aux{ bRes.references[i].browseName.name.data,
                         bRes.references[i].browseName.name.data + bRes.references[i].browseName.name.length };

        if( (bRes.references[i].referenceTypeId.identifier.numeric == UA_NS0ID_HASCOMPONENT
                || bRes.references[i].referenceTypeId.identifier.numeric == UA_NS0ID_HASORDEREDCOMPONENT) &&
            bRes.references[i].referenceTypeId.namespaceIndex == 0 )
        {
            retVal.emplace_back( std::pair<std::string, UA_NodeId>( aux, bRes.references[i].nodeId.nodeId ) );
        }
    }
    UA_BrowseResult_deleteMembers(&bRes);
    return retVal;
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
    if (retval != UA_STATUSCODE_GOOD || bpr.targetsSize < 1) {
        UA_BrowsePathResult_deleteMembers(&bpr);
        std::string qualifiedName = "ns=" + std::to_string(childName.namespaceIndex) + ";"
                                    + std::string(reinterpret_cast<char const*>(childName.name.data),
                                                  childName.name.length);
        std::string errorMessage = std::string(UA_StatusCode_name(retval));
        throw "NODE NOT FOUND ";
    }

    UA_NodeId* nodeId = UA_NodeId_new();

    UA_NodeId_copy(&bpr.targets[0].targetId.nodeId, nodeId);

    UA_BrowsePathResult_deleteMembers(&bpr);

    return std::shared_ptr<UA_NodeId>(nodeId, UA_NodeId_delete);
}

inline const std::shared_ptr<UA_NodeId>
UA_Server_getObjectComponentId(
        UA_Server* server,
        const UA_NodeId& objectId,
        const UA_QualifiedName& componentName
){
    return UA_Server_getObjectChildId(server, objectId, componentName,
                                      UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT));
}

inline UA_NodeId getChildNodeByBrowseName( UA_Server *server, const UA_NodeId& parentNode, char *browseName,
                                           const UA_UInt16 nameSpace, int referenceType )
{
    UA_UInt32 length = 1;
    char *paths[length] = { browseName };
    UA_UInt32 ids[length] = { referenceType };
    UA_UInt16 ns[length] = { nameSpace };

    UA_QualifiedName aux;
    UA_QualifiedName_init( &aux );
    UA_Server_readBrowseName( server, parentNode, &aux );

    UA_BrowsePath browsePath;
    UA_BrowsePath_init(&browsePath);
    browsePath.startingNode = parentNode;
    browsePath.relativePath.elements = (UA_RelativePathElement*)UA_Array_new(length, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
    browsePath.relativePath.elementsSize = length;

    for(size_t i = 0; i < length; i++) {
        UA_RelativePathElement *elem = &browsePath.relativePath.elements[i];
        elem->referenceTypeId = UA_NODEID_NUMERIC(0, ids[i]);
        elem->targetName = UA_QUALIFIEDNAME_ALLOC(ns[i], paths[i]);
    }

    UA_BrowsePathResult res = UA_Server_translateBrowsePathToNodeIds(server, &browsePath);
    if(res.statusCode != UA_STATUSCODE_GOOD || res.targetsSize < 1)
        throw std::runtime_error("COMPONENT NODE COULD NOT BE FOUND IN BROWSEPATH");

    return res.targets->targetId.nodeId;

    UA_BrowsePath_clear( &browsePath );
}

inline UA_NodeId getComponentNodeByBrowseName( UA_Server *server, const UA_NodeId& parentNode, char *browseName, const UA_UInt16 nameSpace ){
    return std::move( getChildNodeByBrowseName( server, parentNode, browseName, nameSpace, UA_NS0ID_HASCOMPONENT ) );
}

inline UA_NodeId getSubtypeNodeByBrowseName( UA_Server *server, const UA_NodeId& parentNode, char *browseName, const UA_UInt16 nameSpace ){
    return std::move( getChildNodeByBrowseName( server, parentNode, browseName, nameSpace, UA_NS0ID_HASSUBTYPE ) );
}

static const std::vector<ProgramTransition>
generateTransitions( UA_Server* server) {
    getComponentNodeByBrowseName( server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE), "HaltedToReady", 0 );

    return {ProgramTransition(ProgramTransitionNumber::HALTED_TO_READY,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "HaltedToReady", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Halted to Ready")),
                              ProgramStateNumber::HALTED, ProgramStateNumber::READY),
            ProgramTransition(ProgramTransitionNumber::READY_TO_RUNNING,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "ReadyToRunning", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready to Running")),
                              ProgramStateNumber::READY, ProgramStateNumber::RUNNING),
            ProgramTransition(ProgramTransitionNumber::RUNNING_TO_HALTED,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "RunningToHalted", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running to Halted")),
                              ProgramStateNumber::RUNNING, ProgramStateNumber::HALTED),
            ProgramTransition(ProgramTransitionNumber::RUNNING_TO_READY,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                              "RunningToReady", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running to Ready")),
                              ProgramStateNumber::RUNNING, ProgramStateNumber::READY),
            ProgramTransition(ProgramTransitionNumber::RUNNING_TO_SUSPENDED,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                             "RunningToSuspended", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                               const_cast<char*>("Running to Suspended")),
                              ProgramStateNumber::RUNNING, ProgramStateNumber::SUSPENDED),
            ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_RUNNING,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "SuspendedToRunning", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                               const_cast<char*>("Suspended to Running")),
                              ProgramStateNumber::SUSPENDED, ProgramStateNumber::RUNNING),
            ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_HALTED,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "SuspendedToHalted", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"),
                                               const_cast<char*>("Suspended to Halted")),
                              ProgramStateNumber::SUSPENDED, ProgramStateNumber::HALTED),
            ProgramTransition(ProgramTransitionNumber::SUSPENDED_TO_READY,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "SuspendedToReady", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Suspended to Ready")),
                              ProgramStateNumber::SUSPENDED, ProgramStateNumber::READY),
            ProgramTransition(ProgramTransitionNumber::READY_TO_HALTED,
                              std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                          server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                            "ReadyToHalted", 0 )),
                              UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready to Halted")),
                              ProgramStateNumber::READY, ProgramStateNumber::HALTED)};
}
static const std::vector<ProgramState> generateStates( UA_Server* server) {
    return {ProgramState(ProgramStateNumber::HALTED,
                         std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                     server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                        "Halted", 0)),
                         UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Halted"))),
            ProgramState(ProgramStateNumber::READY,
                         std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                     server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                         "Ready", 0)),
                         UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Ready"))),
            ProgramState(ProgramStateNumber::RUNNING,
                         std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                     server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                         "Running", 0)),
                         UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Running"))),
            ProgramState(ProgramStateNumber::SUSPENDED,
                         std::make_unique<UA_NodeId>(SAMY::getComponentNodeByBrowseName(
                                                     server, UA_NODEID_NUMERIC(0, UA_NS0ID_PROGRAMSTATEMACHINETYPE),
                                                         "Suspended", 0)),
                         UA_LOCALIZEDTEXT(const_cast<char*>("en-US"), const_cast<char*>("Suspended")))};
}


/* Visitor for given a SkillType, adding two matching nodes ("static" and "real time") to the server */
struct AdderParameterNodesToSkillType{
private:
   /* Once this structure is created, the server and the skill remain fixed (hence, this
    * structure only allows adding the parameter nodes to a particular skill type)*/
   std::string nameOfSkill;
   UA_Server* server;
   int skillsNS;
   int crclNS;
   UA_NodeId skillParametersSetNode;
   UA_NodeId skillRealTimeParametersSetNode;
   UA_NodeId skillTypeNode;

   UA_NodeId findSkillType( const char *skillName );
   UA_NodeId findSkillParameterSetObject( const char *skillName );
   UA_NodeId findSkillParameterSetRealTimeObject( const char *skillName );
   UA_StatusCode addParameterNodesToServer(const std::string &parameterTypeName);

public:
   int numberOfCommandInSkill;

   AdderParameterNodesToSkillType(std::string nameOfSkill_, int numberOfCommandInSkill_, UA_Server* server_):
       nameOfSkill(nameOfSkill_),
       numberOfCommandInSkill(numberOfCommandInSkill_),
       server(server_),
       crclNS( UA_Server_addNamespace( server, "https://crcl.org" ) ),
       skillsNS( UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" ) ),
       skillTypeNode( findSkillType( nameOfSkill_.c_str() ) )
       {
           skillParametersSetNode = findSkillParameterSetObject( nameOfSkill_.c_str() );
           skillRealTimeParametersSetNode = findSkillParameterSetRealTimeObject( nameOfSkill_.c_str() ) ;
       }

   UA_StatusCode operator()(const std::monostate& param)const{
       UA_StatusCode retVal = UA_STATUSCODE_BADNOTSUPPORTED;
       std::cout<< "NODES FOR THE PARAMETERS OF THE COMMAND COULD NOT BE ADDED:" << std::endl <<
                   "SkillTypes Namespace: " << skillsNS << std::endl <<
                   "skillParameterSetNodeID: " << skillParametersSetNode.identifier.numeric << std::endl <<
                   "numberOfCommandInSkill: " << numberOfCommandInSkill << std::endl << std::endl;
       return retVal;
   }
   UA_StatusCode operator()(const UA_InitCanonParametersSetDataType& param){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "InitCanonParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_EndCanonParametersSetDataType& param){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "EndCanonParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_MessageParametersSetDataType& param){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "MessageParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_MoveToParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "MoveToParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_MoveScrewParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "MoveScrewParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_MoveThroughToParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "MoveThroughToParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_DwellParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "DwellParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_ActuateJointsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "ActuateJointsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_ConfigureJointReportsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "ConfigureJointReportsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetDefaultJointPositionsTolerancesParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetDefaultJointPositionsTolerancesParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_GetStatusParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       // UA_NodeId parameterTypeId = findCommandParameterType( server, "GetStatusParameters" );
       retVal |= addParameterNodesToServer( "GetStatusParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_CloseToolChangerParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "CloseToolChangerParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_OpenToolChangerParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "OpenToolChangerParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetRobotParametersParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetRobotParametersParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetEndeffectorParametersParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetEndeffectorParametersParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetEndeffectorParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetEndeffectorParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetTransAccelParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetTransAccelParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetTransSpeedParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetTransSpeedParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetRotAccelParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetRotAccelParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetRotSpeedParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetRotSpeedParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetAngleUnitsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetAngleUnitsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetEndPoseToleranceParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetEndPoseToleranceParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetForceUnitsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetForceUnitsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetIntermediatePoseToleranceParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetIntermediatePoseToleranceParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetLengthUnitsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetLengthUnitsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetMotionCoordinationParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetMotionCoordinationParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_SetTorqueUnitsParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "SetTorqueUnitsParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_StopMotionParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "StopMotionParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_ConfigureStatusReportParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "ConfigureStatusReportParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_EnableSensorParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "EnableSensorParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_DisableSensorParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "DisableSensorParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_EnableGripperParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "EnableGripperParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_DisableGripperParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "DisableGripperParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_EnableRobotParameterStatusParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "EnableRobotParameterStatusParameters" );
       return retVal;
   }
   UA_StatusCode operator()(const UA_DisableRobotParameterStatusParametersSetDataType& params){
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= addParameterNodesToServer( "DisableRobotParameterStatusParameters" );
       return retVal;
   }
};


/* Visitor for the CRCLCommandParametersVariant instantiating a specific UA_CRCLCommandsUnionDataType
* for a skill command given the corresponding parameter. It reads the corresponding parameter in the server
* and generates the UA_CRCLCommandsUnionDataType with the read values. */
/* TODO: DEAL WITH COMMAND IDS AND NAMES!!!*/
struct InstantiateCRCLCommandFromServerParameters{
   InstantiateCRCLCommandFromServerParameters( UA_Server* server_,
                                                       const UA_NodeId& normalNode,
                                                           const UA_NodeId& realTimeNode ):
       server( server_ ),
       normalParameterNodeId( normalNode ),
       realTimeParameterNodeId( realTimeNode ){}
public:
   UA_NodeId realTimeParameterNodeId;
   UA_NodeId normalParameterNodeId;

   UA_CRCLCommandsUnionDataType operator()(const std::monostate& param)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_NONE;
       return command;
   }
   UA_CRCLCommandsUnionDataType operator()(const UA_InitCanonParametersSetDataType& param)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND;
       command.fields.initCanonCommand.realTimeCommand = UA_FALSE;
       command.fields.initCanonCommand.realTimeParameterNode = UA_NODEID_NULL;
       command.fields.initCanonCommand.commandID = 0;
       command.fields.initCanonCommand.guard = NULL;
       command.fields.initCanonCommand.guardSize = 0;
       command.fields.initCanonCommand.id = 12345;
       UA_String aux = UA_STRING( "InitCommand" );
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= UA_String_copy( &aux, &command.fields.initCanonCommand.name);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()(const UA_EndCanonParametersSetDataType& param)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND;
       command.fields.endCanonCommand.realTimeCommand = UA_FALSE;
       command.fields.endCanonCommand.realTimeParameterNode = UA_NODEID_NULL;
       command.fields.endCanonCommand.commandID = 0;
       command.fields.endCanonCommand.guard = NULL;
       command.fields.endCanonCommand.guardSize = 0;
       command.fields.endCanonCommand.id = 12345;
       UA_String aux = UA_STRING( "EndCommand" );
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= UA_String_copy( &aux, &command.fields.endCanonCommand.name);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_MessageParametersSetDataType& params2)const{
       UA_Variant var;
       UA_Variant_init(&var);

       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_MessageParametersSetDataType* params = (UA_MessageParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND;
       command.fields.messageCommand.realTimeCommand = UA_FALSE;
       command.fields.messageCommand.realTimeParameterNode = UA_NODEID_NULL;
       command.fields.messageCommand.commandID = 0;
       command.fields.messageCommand.guard = NULL;
       command.fields.messageCommand.guardSize = 0;
       command.fields.messageCommand.id = 12345;
       UA_String aux = UA_STRING( "MessageCommand" );
       retVal |= UA_String_copy( &aux, &command.fields.messageCommand.name);

       retVal |= UA_String_copy( &params->message, &(command.fields.messageCommand.message) );
       command.fields.messageCommand.realTimeCommand = params->realTimeParameter;
       command.fields.messageCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_MoveToParametersSetDataType& paramType )const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_MoveToParametersSetDataType* params = (UA_MoveToParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND;
       command.fields.moveToCommand.commandID = 0;
       command.fields.moveToCommand.id = 0;
       UA_String aux = UA_STRING( "MoveToCommand" );
       retVal |= UA_String_copy( &aux, &command.fields.moveToCommand.name);
       command.fields.moveToCommand.guard = NULL;
       command.fields.moveToCommand.guardSize = 0;

       command.fields.moveToCommand.moveStraight = params->moveStraight;
       command.fields.moveToCommand.endPosition = std::move( params->endPosition );
       command.fields.moveToCommand.realTimeCommand = params->realTimeParameter;
       command.fields.moveToCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_MoveScrewParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_MoveScrewParametersSetDataType* params = (UA_MoveScrewParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND;
       command.fields.moveScrewCommand.commandID = 0;
       command.fields.moveScrewCommand.id = 0;
       UA_String aux = UA_STRING( "MoveScrewCommand" );
       retVal |= UA_String_copy( &aux, &command.fields.moveScrewCommand.name);
       command.fields.moveScrewCommand.guard = NULL;
       command.fields.moveScrewCommand.guardSize = 0;

       command.fields.moveScrewCommand.axialDistanceFree = params->axialDistanceFree;
       command.fields.moveScrewCommand.axialDistanceScrew = params->axialDistanceScrew;
       command.fields.moveScrewCommand.axisPoint = std::move( params->axisPoint );
       command.fields.moveScrewCommand.startPosition = std::move( params->startPosition );
       command.fields.moveScrewCommand.turn = params->turn;

       command.fields.moveScrewCommand.realTimeCommand = params->realTimeParameter;
       command.fields.moveScrewCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_MoveThroughToParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_MoveThroughToParametersSetDataType* params = (UA_MoveThroughToParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND;
       command.fields.moveThroughToCommand.commandID = 0;
       command.fields.moveThroughToCommand.id = 0;
       UA_String aux = UA_STRING( " " );
       retVal |= UA_String_copy( &aux, &command.fields.moveThroughToCommand.name);
       command.fields.moveThroughToCommand.guard = NULL;
       command.fields.moveThroughToCommand.guardSize = 0;

       command.fields.moveThroughToCommand.moveStraight = params->moveStraight;
       command.fields.moveThroughToCommand.numPositions = params->numPositions;
       command.fields.moveThroughToCommand.waypointSize = params->waypointSize;
       command.fields.moveThroughToCommand.waypoint = std::move( params->waypoint );

       command.fields.moveThroughToCommand.realTimeCommand = params->realTimeParameter;
       command.fields.moveThroughToCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_DwellParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_DwellParametersSetDataType* params = (UA_DwellParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND;
       command.fields.dwellCommand.commandID = 0;
       command.fields.dwellCommand.id = 0;
       UA_String aux = UA_STRING( " " );
       retVal |= UA_String_copy( &aux, &command.fields.dwellCommand.name);
       command.fields.dwellCommand.guard = NULL;
       command.fields.dwellCommand.guardSize = 0;

       command.fields.dwellCommand.dwellTime = params->dwellTime;

       command.fields.dwellCommand.realTimeCommand = params->realTimeParameter;
       command.fields.dwellCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_ActuateJointsParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_ActuateJointsParametersSetDataType* params = (UA_ActuateJointsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND;
       command.fields.actuateJointsCommand.commandID = 0;
       command.fields.actuateJointsCommand.id = 0;
       UA_String aux = UA_STRING( "ActuateJointsCommand" );
       retVal |= UA_String_copy( &aux, &command.fields.actuateJointsCommand.name);
       command.fields.actuateJointsCommand.guard = NULL;
       command.fields.actuateJointsCommand.guardSize = 0;

       retVal |= UA_Array_copy( params->actuateJoint, params->actuateJointSize,
                                (void**)&(command.fields.actuateJointsCommand.actuateJoint),
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_ACTUATEJOINTDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );
       command.fields.actuateJointsCommand.actuateJointSize = params->actuateJointSize;

       UA_CRCL_JointPositionsTolerancesDataType_copy( &params->jointTolerances,
                                                      &(command.fields.actuateJointsCommand.jointTolerances) );

       command.fields.actuateJointsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.actuateJointsCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_ConfigureJointReportsParametersSetDataType& paramType)const{
        UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_ConfigureJointReportsParametersSetDataType* params = (UA_ConfigureJointReportsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND;

       command.fields.configureJointReportsCommand.commandID = 0;
       command.fields.configureJointReportsCommand.id = 0;
       UA_String aux = UA_STRING( "ConfigureJointReportsCommand" );
       retVal |= UA_String_copy( &aux, &command.fields.configureJointReportsCommand.name);
       command.fields.configureJointReportsCommand.guard = NULL;
       command.fields.configureJointReportsCommand.guardSize = 0;

       command.fields.configureJointReportsCommand.configureJointReportSize = params->configureJointReportSize;

       command.fields.configureJointReportsCommand.resetAll = params->resetAll;
       retVal |= UA_Array_copy( params->configureJointReport, params->configureJointReportSize,
                                (void**)&(command.fields.configureJointReportsCommand.configureJointReport),
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_CONFIGUREJOINTREPORTDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.configureJointReportsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.configureJointReportsCommand.realTimeParameterNode = realTimeParameterNodeId;


       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetDefaultJointPositionsTolerancesParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetDefaultJointPositionsTolerancesParametersSetDataType* params =
                                                                (UA_SetDefaultJointPositionsTolerancesParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND;
       command.fields.setDefaultJointPositionsTolerancesCommand.commandID = 0;
       command.fields.setDefaultJointPositionsTolerancesCommand.id = 0;
       UA_String aux = UA_STRING( "SetDefaultJointPositionsTolerances" );
       retVal |= UA_String_copy( &aux, &command.fields.setDefaultJointPositionsTolerancesCommand.name);
       command.fields.setDefaultJointPositionsTolerancesCommand.guard = NULL;
       command.fields.setDefaultJointPositionsTolerancesCommand.guardSize = 0;

       UA_CRCL_JointPositionsTolerancesDataType_copy( &params->jointTolerances,
                                                      &command.fields.setDefaultJointPositionsTolerancesCommand.jointTolerances );

       command.fields.setDefaultJointPositionsTolerancesCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setDefaultJointPositionsTolerancesCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_GetStatusParametersSetDataType& paramType)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND;
       command.fields.getStatusCommand.commandID = 0;
       command.fields.getStatusCommand.id = 0;
       command.fields.getStatusCommand.guard = NULL;
       command.fields.getStatusCommand.guardSize = 0;
       UA_String aux = UA_STRING( "GetStatus" );
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= UA_String_copy( &aux, &command.fields.getStatusCommand.name);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.getStatusCommand.realTimeCommand = UA_FALSE;
       command.fields.getStatusCommand.realTimeParameterNode = UA_NODEID_NULL;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_CloseToolChangerParametersSetDataType& paramType)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND;
       command.fields.closeToolChangerCommand.commandID = 0;
       command.fields.closeToolChangerCommand.id = 0;
       command.fields.closeToolChangerCommand.guard = NULL;
       command.fields.closeToolChangerCommand.guardSize = 0;
       UA_String aux = UA_STRING( "CloseToolChanger" );
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= UA_String_copy( &aux, &command.fields.closeToolChangerCommand.name);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.closeToolChangerCommand.realTimeCommand = UA_FALSE;
       command.fields.closeToolChangerCommand.realTimeParameterNode = UA_NODEID_NULL;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_OpenToolChangerParametersSetDataType& paramType)const{
       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND;
       command.fields.openToolChangerCommand.commandID = 0;
       command.fields.openToolChangerCommand.id = 0;
       command.fields.openToolChangerCommand.guard = NULL;
       command.fields.openToolChangerCommand.guardSize = 0;
       UA_String aux = UA_STRING( "OpenToolChanger" );
       UA_StatusCode retVal = UA_STATUSCODE_GOOD;
       retVal |= UA_String_copy( &aux, &command.fields.openToolChangerCommand.name);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.openToolChangerCommand.realTimeCommand = UA_FALSE;
       command.fields.openToolChangerCommand.realTimeParameterNode = UA_NODEID_NULL;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetRobotParametersParametersSetDataType& paramType )const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetRobotParametersParametersSetDataType* params = (UA_SetRobotParametersParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND;
       command.fields.setRobotParametersCommand.commandID = 0;
       command.fields.setRobotParametersCommand.id = 0;
       UA_String aux = UA_STRING( "SetRobotParameters" );
       retVal |= UA_String_copy( &aux, &command.fields.setRobotParametersCommand.name);
       command.fields.setRobotParametersCommand.guard = NULL;
       command.fields.setRobotParametersCommand.guardSize = 0;

       command.fields.setRobotParametersCommand.parameterSettingSize = params->parameterSettingSize;
       retVal |= UA_Array_copy( params->parameterSetting,  params->parameterSettingSize,
                                (void**)&(command.fields.setRobotParametersCommand.parameterSetting),
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.setRobotParametersCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setRobotParametersCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }

   UA_CRCLCommandsUnionDataType operator()( UA_SetEndeffectorParametersParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetEndeffectorParametersParametersSetDataType* params = (UA_SetEndeffectorParametersParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND;
       command.fields.setEndeffectorParametersCommand.commandID = 0;
       command.fields.setEndeffectorParametersCommand.id = 0;
       UA_String aux = UA_STRING( "SetEndeffectorParameters" );
       retVal |= UA_String_copy( &aux, &command.fields.setEndeffectorParametersCommand.name);
       command.fields.setEndeffectorParametersCommand.guard = NULL;
       command.fields.setEndeffectorParametersCommand.guardSize = 0;

       command.fields.setEndeffectorParametersCommand.parameterSettingSize = params->parameterSettingSize;
       retVal |= UA_Array_copy( params->parameterSetting,  params->parameterSettingSize,
                                (void**)&(command.fields.setEndeffectorParametersCommand.parameterSetting),
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.setEndeffectorParametersCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setEndeffectorParametersCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }

   UA_CRCLCommandsUnionDataType operator()( UA_SetEndeffectorParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetEndeffectorParametersSetDataType* params = (UA_SetEndeffectorParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND;
       command.fields.setEndeffectorCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetEndeffector" );
       retVal |= UA_String_copy( &aux, &command.fields.setEndeffectorCommand.name);
       command.fields.setEndeffectorCommand.commandID = 0;
       command.fields.setEndeffectorCommand.id = 0;
       command.fields.setEndeffectorCommand.guard = NULL;
       command.fields.setEndeffectorCommand.guardSize = 0;

       command.fields.setEndeffectorCommand.setting = params->setting;

       command.fields.setEndeffectorCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setEndeffectorCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetTransAccelParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetTransAccelParametersSetDataType* params = (UA_SetTransAccelParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND;
       command.fields.setTransAccelCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetTransAccel" );
       retVal |= UA_String_copy( &aux, &command.fields.setTransAccelCommand.name);
       command.fields.setTransAccelCommand.commandID = 0;
       command.fields.setTransAccelCommand.id = 0;
       command.fields.setTransAccelCommand.guard = NULL;
       command.fields.setTransAccelCommand.guardSize = 0;

       command.fields.setTransAccelCommand.transAccel = params->transAccel;

       command.fields.setTransAccelCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setTransAccelCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetTransSpeedParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetTransSpeedParametersSetDataType* params = (UA_SetTransSpeedParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND;
       command.fields.setTransSpeedCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetTransSpeed" );
       retVal |= UA_String_copy( &aux, &command.fields.setTransSpeedCommand.name);
       command.fields.setTransSpeedCommand.commandID = 0;
       command.fields.setTransSpeedCommand.id = 0;
       command.fields.setTransSpeedCommand.guard = NULL;
       command.fields.setTransSpeedCommand.guardSize = 0;

       command.fields.setTransSpeedCommand.transSpeed = params->transSpeed;

       command.fields.setTransSpeedCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setTransSpeedCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetRotAccelParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetRotAccelParametersSetDataType* params = (UA_SetRotAccelParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND;
       command.fields.setTransSpeedCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetRotAccel" );
       retVal |= UA_String_copy( &aux, &command.fields.setRotAccelCommand.name);
       command.fields.setRotAccelCommand.commandID = 0;
       command.fields.setRotAccelCommand.id = 0;
       command.fields.setRotAccelCommand.guard = NULL;
       command.fields.setRotAccelCommand.guardSize = 0;

       command.fields.setRotAccelCommand.rotAccel = params->rotAccel;

       command.fields.setRotAccelCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setRotAccelCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetRotSpeedParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetRotSpeedParametersSetDataType* params = (UA_SetRotSpeedParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND;
       command.fields.setRotSpeedCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetRotSpeed" );
       retVal |= UA_String_copy( &aux, &command.fields.setRotSpeedCommand.name);
       command.fields.setRotSpeedCommand.commandID = 0;
       command.fields.setRotSpeedCommand.id = 0;
       command.fields.setRotSpeedCommand.guard = NULL;
       command.fields.setRotSpeedCommand.guardSize = 0;

       command.fields.setRotSpeedCommand.rotSpeed = params->rotSpeed;

       command.fields.setRotSpeedCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setRotSpeedCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetAngleUnitsParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetAngleUnitsParametersSetDataType* params = (UA_SetAngleUnitsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND;
       command.fields.setAngleUnitsCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetAngleUnit" );
       retVal |= UA_String_copy( &aux, &command.fields.setAngleUnitsCommand.name);
       command.fields.setAngleUnitsCommand.commandID = 0;
       command.fields.setAngleUnitsCommand.id = 0;
       command.fields.setAngleUnitsCommand.guard = NULL;
       command.fields.setAngleUnitsCommand.guardSize = 0;

       command.fields.setAngleUnitsCommand.unitName = params->unitName;

       command.fields.setAngleUnitsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setAngleUnitsCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetEndPoseToleranceParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetEndPoseToleranceParametersSetDataType* params = (UA_SetEndPoseToleranceParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND;
       command.fields.setEndPoseToleranceCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetEndPoseTolerance" );
       retVal |= UA_String_copy( &aux, &command.fields.setEndPoseToleranceCommand.name);
       command.fields.setEndPoseToleranceCommand.commandID = 0;
       command.fields.setEndPoseToleranceCommand.id = 0;
       command.fields.setEndPoseToleranceCommand.guard = NULL;
       command.fields.setEndPoseToleranceCommand.guardSize = 0;

       command.fields.setEndPoseToleranceCommand.tolerance = params->tolerance;

       command.fields.setEndPoseToleranceCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setEndPoseToleranceCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetForceUnitsParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetForceUnitsParametersSetDataType* params = (UA_SetForceUnitsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND;
       command.fields.setForceUnitsCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetForceUnits" );
       retVal |= UA_String_copy( &aux, &command.fields.setForceUnitsCommand.name);
       command.fields.setForceUnitsCommand.commandID = 0;
       command.fields.setForceUnitsCommand.id = 0;
       command.fields.setForceUnitsCommand.guard = NULL;
       command.fields.setForceUnitsCommand.guardSize = 0;

       command.fields.setForceUnitsCommand.unitName = params->unitName;

       command.fields.setForceUnitsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setForceUnitsCommand.realTimeParameterNode = realTimeParameterNodeId;
       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetIntermediatePoseToleranceParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       UA_SetIntermediatePoseToleranceParametersSetDataType* params = (UA_SetIntermediatePoseToleranceParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND;
       command.fields.setIntermediatePoseToleranceCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetIntermediatePoseTolerance" );
       retVal |= UA_String_copy( &aux, &command.fields.setIntermediatePoseToleranceCommand.name);
       command.fields.setIntermediatePoseToleranceCommand.commandID = 0;
       command.fields.setIntermediatePoseToleranceCommand.id = 0;
       command.fields.setIntermediatePoseToleranceCommand.guard = NULL;
       command.fields.setIntermediatePoseToleranceCommand.guardSize = 0;

       command.fields.setIntermediatePoseToleranceCommand.tolerance = params->tolerance;

       command.fields.setIntermediatePoseToleranceCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setIntermediatePoseToleranceCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetLengthUnitsParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetLengthUnitsParametersSetDataType* params = (UA_SetLengthUnitsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND;
       command.fields.setLengthUnitsCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetLengthUnits" );
       retVal |= UA_String_copy( &aux, &command.fields.setLengthUnitsCommand.name);
       command.fields.setLengthUnitsCommand.commandID = 0;
       command.fields.setLengthUnitsCommand.id = 0;
       command.fields.setLengthUnitsCommand.guard = NULL;
       command.fields.setLengthUnitsCommand.guardSize = 0;

       command.fields.setLengthUnitsCommand.unitName = params->unitName;

       command.fields.setLengthUnitsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setLengthUnitsCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetMotionCoordinationParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetMotionCoordinationParametersSetDataType* params = (UA_SetMotionCoordinationParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND;
       command.fields.setMotionCoordinationCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetMotionCoordination" );
       retVal |= UA_String_copy( &aux, &command.fields.setMotionCoordinationCommand.name);
       command.fields.setMotionCoordinationCommand.commandID = 0;
       command.fields.setMotionCoordinationCommand.id = 0;
       command.fields.setMotionCoordinationCommand.guard = NULL;
       command.fields.setMotionCoordinationCommand.guardSize = 0;

       command.fields.setMotionCoordinationCommand.coordinated = params->coordinated;

       command.fields.setMotionCoordinationCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setMotionCoordinationCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_SetTorqueUnitsParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_SetTorqueUnitsParametersSetDataType* params = (UA_SetTorqueUnitsParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND;
       command.fields.setTorqueUnitsCommand.commandID = 0;
       UA_String aux = UA_STRING( "SetTorqueUnits" );
       retVal |= UA_String_copy( &aux, &command.fields.setTorqueUnitsCommand.name);
       command.fields.setTorqueUnitsCommand.commandID = 0;
       command.fields.setTorqueUnitsCommand.id = 0;
       command.fields.setTorqueUnitsCommand.guard = NULL;
       command.fields.setTorqueUnitsCommand.guardSize = 0;

       command.fields.setTorqueUnitsCommand.unitName = params->unitName;

       command.fields.setTorqueUnitsCommand.realTimeCommand = params->realTimeParameter;
       command.fields.setTorqueUnitsCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_StopMotionParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_StopMotionParametersSetDataType* params = (UA_StopMotionParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND;
       command.fields.stopMotionCommand.commandID = 0;
       UA_String aux = UA_STRING( "StopMotion" );
       retVal |= UA_String_copy( &aux, &command.fields.stopMotionCommand.name);
       command.fields.stopMotionCommand.commandID = 0;
       command.fields.stopMotionCommand.id = 0;
       command.fields.stopMotionCommand.guard = NULL;
       command.fields.stopMotionCommand.guardSize = 0;

       command.fields.stopMotionCommand.stopCondition = params->stopCondition;

       command.fields.stopMotionCommand.realTimeCommand = params->realTimeParameter;
       command.fields.stopMotionCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_ConfigureStatusReportParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_ConfigureStatusReportParametersSetDataType* params = (UA_ConfigureStatusReportParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND;
       command.fields.configureStatusReportCommand.commandID = 0;
       UA_String aux = UA_STRING( "ConfigureStatusReport" );
       retVal |= UA_String_copy( &aux, &command.fields.configureStatusReportCommand.name);
       command.fields.configureStatusReportCommand.commandID = 0;
       command.fields.configureStatusReportCommand.id = 0;
       command.fields.configureStatusReportCommand.guard = NULL;
       command.fields.configureStatusReportCommand.guardSize = 0;

       command.fields.configureStatusReportCommand.reportGripperStatus = params->reportGripperStatus;
       command.fields.configureStatusReportCommand.reportGuardsStatus = params->reportGuardsStatus;
       command.fields.configureStatusReportCommand.reportJointStatuses = params->reportJointStatuses;
       command.fields.configureStatusReportCommand.reportPoseStatus = params->reportPoseStatus;
       command.fields.configureStatusReportCommand.reportSensorsStatus = params->reportSensorsStatus;
       command.fields.configureStatusReportCommand.reportSettingsStatus = params->reportSettingsStatus;

       command.fields.configureStatusReportCommand.realTimeCommand = params->realTimeParameter;
       command.fields.configureStatusReportCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_EnableSensorParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_EnableSensorParametersSetDataType* params = (UA_EnableSensorParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;

       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND;
       command.fields.enableSensorCommand.commandID = 0;
       UA_String aux = UA_STRING( "EnableSensor" );
       retVal |= retVal |= UA_String_copy( &aux, &command.fields.enableSensorCommand.name);
       command.fields.enableSensorCommand.commandID = 0;
       command.fields.enableSensorCommand.id = 0;
       command.fields.enableSensorCommand.guard = NULL;
       command.fields.enableSensorCommand.guardSize = 0;

       retVal |= UA_String_copy( &params->sensorID, &command.fields.enableSensorCommand.sensorID );
       command.fields.enableSensorCommand.sensorOptionSize = params->sensorOptionSize;
       retVal |= UA_Array_copy( params->sensorOption,  params->sensorOptionSize,
                                (void**)&(command.fields.enableSensorCommand.sensorOption),
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.enableSensorCommand.realTimeCommand = params->realTimeParameter;
       command.fields.enableSensorCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_DisableSensorParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_DisableSensorParametersSetDataType* params = (UA_DisableSensorParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND;
       command.fields.disableSensorCommand.commandID = 0;
       UA_String aux = UA_STRING( "DisableSensor" );
       retVal |= UA_String_copy( &aux, &command.fields.configureStatusReportCommand.name);
       command.fields.disableSensorCommand.commandID = 0;
       command.fields.disableSensorCommand.id = 0;
       command.fields.disableSensorCommand.guard = NULL;
       command.fields.disableSensorCommand.guardSize = 0;

       retVal |= UA_String_copy( &params->sensorID, &command.fields.disableSensorCommand.sensorID  );

       command.fields.disableSensorCommand.realTimeCommand = params->realTimeParameter;
       command.fields.disableSensorCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_EnableGripperParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_EnableGripperParametersSetDataType* params = (UA_EnableGripperParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND;
       command.fields.enableGripperCommand.commandID = 0;
       UA_String aux = UA_STRING( "EnableGripper" );
       retVal |= UA_String_copy( &aux, &command.fields.enableGripperCommand.name);
       command.fields.enableGripperCommand.commandID = 0;
       command.fields.enableGripperCommand.id = 0;
       command.fields.enableGripperCommand.guard = NULL;
       command.fields.enableGripperCommand.guardSize = 0;

       retVal |= UA_String_copy( &params->gripperName, &command.fields.enableGripperCommand.gripperName);
       command.fields.enableGripperCommand.gripperOptionSize= params->gripperOptionSize;
       retVal |= UA_Array_copy( params->gripperOption,  params->gripperOptionSize,
                                (void**)&command.fields.enableGripperCommand.gripperOption,
                                &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE COPIED" );

       command.fields.enableGripperCommand.realTimeCommand = params->realTimeParameter;
       command.fields.enableGripperCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_DisableGripperParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_DisableGripperParametersSetDataType* params = (UA_DisableGripperParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND;
       command.fields.disableGripperCommand.commandID = 0;
       UA_String aux = UA_STRING( "DisableGripper" );
       retVal |= UA_String_copy( &aux, &command.fields.disableGripperCommand.name);
       command.fields.disableGripperCommand.commandID = 0;
       command.fields.disableGripperCommand.id = 0;
       command.fields.disableGripperCommand.guard = NULL;
       command.fields.disableGripperCommand.guardSize = 0;

      retVal |= UA_String_copy( &params->gripperName, &command.fields.disableGripperCommand.gripperName );

       command.fields.disableGripperCommand.realTimeCommand = params->realTimeParameter;
       command.fields.disableGripperCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_EnableRobotParameterStatusParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_EnableRobotParameterStatusParametersSetDataType* params = (UA_EnableRobotParameterStatusParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND;
       command.fields.enableRobotParameterStatusCommand.commandID = 0;
       UA_String aux = UA_STRING( "EnableRobotParameterStatus" );
       retVal |= UA_String_copy( &aux, &command.fields.enableRobotParameterStatusCommand.name);
       command.fields.enableRobotParameterStatusCommand.commandID = 0;
       command.fields.enableRobotParameterStatusCommand.id = 0;
       command.fields.enableRobotParameterStatusCommand.guard = NULL;
       command.fields.enableRobotParameterStatusCommand.guardSize = 0;

       retVal |= UA_String_copy( &params->robotParameterName, &command.fields.enableRobotParameterStatusCommand.robotParameterName );

       command.fields.enableRobotParameterStatusCommand.realTimeCommand = params->realTimeParameter;
       command.fields.enableRobotParameterStatusCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }
   UA_CRCLCommandsUnionDataType operator()( UA_DisableRobotParameterStatusParametersSetDataType& paramType)const{
       UA_Variant var;
       UA_Variant_init(&var);
       UA_StatusCode retVal = UA_Server_readValue( server, normalParameterNodeId, &var );
       if( retVal != UA_STATUSCODE_GOOD )
           throw std::runtime_error( "SKILL PARAMETER COULD NOT BE READ" );

       UA_DisableRobotParameterStatusParametersSetDataType* params = (UA_DisableRobotParameterStatusParametersSetDataType*)(var.data);

       UA_CRCLCommandsUnionDataType command;
       command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND;
       command.fields.disableRobotParameterStatusCommand.commandID = 0;
       UA_String aux = UA_STRING( "DisableRobotParameterStatus" );
       retVal |= UA_String_copy( &aux, &command.fields.disableRobotParameterStatusCommand.name);
       command.fields.disableRobotParameterStatusCommand.commandID = 0;
       command.fields.disableRobotParameterStatusCommand.id = 0;
       command.fields.disableRobotParameterStatusCommand.guard = NULL;
       command.fields.disableRobotParameterStatusCommand.guardSize = 0;

       retVal |= UA_String_copy( &params->robotParameterName , &command.fields.disableRobotParameterStatusCommand.robotParameterName );

       command.fields.disableRobotParameterStatusCommand.realTimeCommand = params->realTimeParameter;
       command.fields.disableRobotParameterStatusCommand.realTimeParameterNode = realTimeParameterNodeId;

       return command;
   }

private:
   UA_Server* server;
};

/* Variant for dealing with the polymorphy of the parameters required by the (polymorphic) CRCL commands.
* Since polymorphy "cannot be sent over the wire" in OPC UA, I use a union of CRCL commands for that purpose.
* Due to this I use a similar approach with the parameters required by the commands, to keep symmetry between
* SAMYCore code and open62541 code. Hence, I do not use inheritance or alike constructs, but
* the pattern I use for polymorphism is a c++17 variant equipped with different visitors.*/
using CRCLCommandsParametersVariant = std::variant<std::monostate,
                                           UA_InitCanonParametersSetDataType,
                                           UA_EndCanonParametersSetDataType,
                                           UA_MessageParametersSetDataType,
                                           UA_MoveToParametersSetDataType,
                                           UA_MoveScrewParametersSetDataType,
                                           UA_MoveThroughToParametersSetDataType,
                                           UA_DwellParametersSetDataType,
                                           UA_ActuateJointsParametersSetDataType,
                                           UA_ConfigureJointReportsParametersSetDataType,
                                           UA_SetDefaultJointPositionsTolerancesParametersSetDataType,
                                           UA_GetStatusParametersSetDataType,
                                           UA_CloseToolChangerParametersSetDataType,
                                           UA_OpenToolChangerParametersSetDataType,
                                           UA_SetRobotParametersParametersSetDataType,
                                           UA_SetEndeffectorParametersParametersSetDataType,
                                           UA_SetEndeffectorParametersSetDataType,
                                           UA_SetTransAccelParametersSetDataType,
                                           UA_SetTransSpeedParametersSetDataType,
                                           UA_SetRotAccelParametersSetDataType,
                                           UA_SetRotSpeedParametersSetDataType,
                                           UA_SetAngleUnitsParametersSetDataType,
                                           UA_SetEndPoseToleranceParametersSetDataType,
                                           UA_SetForceUnitsParametersSetDataType,
                                           UA_SetIntermediatePoseToleranceParametersSetDataType,
                                           UA_SetLengthUnitsParametersSetDataType,
                                           UA_SetMotionCoordinationParametersSetDataType,
                                           UA_SetTorqueUnitsParametersSetDataType,
                                           UA_StopMotionParametersSetDataType,
                                           UA_ConfigureStatusReportParametersSetDataType,
                                           UA_EnableSensorParametersSetDataType,
                                           UA_DisableSensorParametersSetDataType,
                                           UA_EnableGripperParametersSetDataType,
                                           UA_DisableGripperParametersSetDataType,
                                           UA_EnableRobotParameterStatusParametersSetDataType,
                                           UA_DisableRobotParameterStatusParametersSetDataType
                                           >;

/* This map connects the numbering in the union of the Server and the Parameters of the SAMYCore, so we can
* modify the (XML) OPC UA CRCL Information Model without problem, since automatically matches CRCLCommandsUnion
*  numbering and parameters types, so we do not have to hardcode anything. */
static const std::map<int, CRCLCommandsParametersVariant> crclCommandSwitchfield_ParameterType_Map = {
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND , CRCLCommandsParametersVariant( UA_InitCanonParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND , CRCLCommandsParametersVariant( UA_EndCanonParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND , CRCLCommandsParametersVariant( UA_MessageParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND , CRCLCommandsParametersVariant( UA_MoveToParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND , CRCLCommandsParametersVariant( UA_MoveScrewParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND , CRCLCommandsParametersVariant( UA_MoveThroughToParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND , CRCLCommandsParametersVariant( UA_DwellParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND , CRCLCommandsParametersVariant( UA_ActuateJointsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND ,
                           CRCLCommandsParametersVariant( UA_ConfigureJointReportsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND ,
                           CRCLCommandsParametersVariant( UA_SetDefaultJointPositionsTolerancesParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND , CRCLCommandsParametersVariant( UA_GetStatusParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND , CRCLCommandsParametersVariant( UA_CloseToolChangerParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND , CRCLCommandsParametersVariant( UA_OpenToolChangerParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND , CRCLCommandsParametersVariant( UA_SetRobotParametersParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND ,
                           CRCLCommandsParametersVariant( UA_SetEndeffectorParametersParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND , CRCLCommandsParametersVariant( UA_SetEndeffectorParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND , CRCLCommandsParametersVariant( UA_SetTransAccelParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND , CRCLCommandsParametersVariant( UA_SetTransSpeedParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND , CRCLCommandsParametersVariant( UA_SetRotAccelParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND , CRCLCommandsParametersVariant( UA_SetRotSpeedParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND , CRCLCommandsParametersVariant( UA_SetAngleUnitsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND ,
                           CRCLCommandsParametersVariant( UA_SetEndPoseToleranceParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND , CRCLCommandsParametersVariant( UA_SetForceUnitsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND ,
                           CRCLCommandsParametersVariant( UA_SetIntermediatePoseToleranceParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND , CRCLCommandsParametersVariant( UA_SetLengthUnitsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND ,
                           CRCLCommandsParametersVariant( UA_SetMotionCoordinationParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND , CRCLCommandsParametersVariant( UA_SetTorqueUnitsParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND , CRCLCommandsParametersVariant( UA_StopMotionParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND ,
                           CRCLCommandsParametersVariant( UA_ConfigureStatusReportParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND , CRCLCommandsParametersVariant( UA_EnableSensorParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND , CRCLCommandsParametersVariant( UA_DisableSensorParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND , CRCLCommandsParametersVariant( UA_EnableGripperParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND , CRCLCommandsParametersVariant( UA_DisableGripperParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND ,
                           CRCLCommandsParametersVariant( UA_EnableRobotParameterStatusParametersSetDataType() )},
   { UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND,
                           CRCLCommandsParametersVariant( UA_DisableRobotParameterStatusParametersSetDataType() )}
};


static const std::map<std::string, UA_NodeId> crclParameterName_DataTypeNodeId_Map = {
    { "InitCanonParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONPARAMETERSSETDATATYPE].typeId },
    { "EndCanonParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONPARAMETERSSETDATATYPE].typeId },
    { "MessageParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEPARAMETERSSETDATATYPE].typeId },
    { "MoveToParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETOPARAMETERSSETDATATYPE].typeId },
    { "MoveScrewParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWPARAMETERSSETDATATYPE].typeId },
    { "MoveThroughToParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTOPARAMETERSSETDATATYPE].typeId },
    { "DwellParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLPARAMETERSSETDATATYPE].typeId },
    { "ActuateJointsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSPARAMETERSSETDATATYPE].typeId },
    { "ConfigureJointReportsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSPARAMETERSSETDATATYPE].typeId },
    { "SetDefaultJointPositionsTolerancesParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESPARAMETERSSETDATATYPE].typeId },
    { "GetStatusParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSPARAMETERSSETDATATYPE].typeId },
    { "CloseToolChangerParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERPARAMETERSSETDATATYPE].typeId },
    { "OpenToolChangerParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERPARAMETERSSETDATATYPE].typeId },
    { "SetRobotParametersParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSPARAMETERSSETDATATYPE].typeId },
    { "SetEndeffectorParametersParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSPARAMETERSSETDATATYPE].typeId },
    { "SetEndeffectorParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSSETDATATYPE].typeId },
    { "SetTransAccelParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELPARAMETERSSETDATATYPE].typeId },
    { "SetTransSpeedParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDPARAMETERSSETDATATYPE].typeId },
    { "SetRotAccelParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELPARAMETERSSETDATATYPE].typeId },
    { "SetRotSpeedParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDPARAMETERSSETDATATYPE].typeId },
    { "SetAngleUnitsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSPARAMETERSSETDATATYPE].typeId },
    { "SetEndPoseToleranceParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEPARAMETERSSETDATATYPE].typeId },
    { "SetForceUnitsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSPARAMETERSSETDATATYPE].typeId },
    { "SetIntermediatePoseToleranceParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEPARAMETERSSETDATATYPE].typeId },
    { "SetLengthUnitsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSPARAMETERSSETDATATYPE].typeId },
    { "SetMotionCoordinationParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONPARAMETERSSETDATATYPE].typeId },
    { "SetTorqueUnitsParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSPARAMETERSSETDATATYPE].typeId },
    { "StopMotionParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONPARAMETERSSETDATATYPE].typeId },
    { "ConfigureStatusReportParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTPARAMETERSSETDATATYPE].typeId },
    { "EnableSensorParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORPARAMETERSSETDATATYPE].typeId },
    { "DisableSensorParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORPARAMETERSSETDATATYPE].typeId },
    { "EnableGripperParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERPARAMETERSSETDATATYPE].typeId },
    { "DisableGripperParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERPARAMETERSSETDATATYPE].typeId },
    { "EnableRobotParameterStatusParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE].typeId },
    { "DisableRobotParameterStatusParameters" , UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE].typeId }
};

void printCRCLSkill( const UA_CRCLSkillDataType* skill);
UA_NodeId findCommandParameterType( UA_Server* server, char* parameterTypeName );

}
#endif
