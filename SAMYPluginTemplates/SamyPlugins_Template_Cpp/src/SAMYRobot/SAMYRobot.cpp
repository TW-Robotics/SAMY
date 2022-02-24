#include "SAMYRobot.h"

namespace SAMY {

SAMYRobot::SAMYRobot( std::shared_ptr<spdlog::logger> logger_ ):
    logger( logger_ )
{}

UA_StatusCode SAMYRobot::readSkillCurrentStateId(
        UA_Server* server,
        const UA_NodeId* sessionId,
        void* sessionContext,
        const UA_NodeId* nodeId,
        void* nodeContext,
        UA_Boolean sourceTimeStamp,
        const UA_NumericRange* range,
        UA_DataValue* dataValue
){
    if (!nodeContext)
        return UA_STATUSCODE_BADINTERNALERROR;
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    for( int i = 0; i < robot->robotSkills.size(); i++ )
    {
        if( robot->robotSkills[i].getSkillCurrentStateNodeId().identifier.numeric == nodeId->identifier.numeric )
        {
            const UA_NodeId* stateId = robot->robotSkills[i].getSkillCurrentState()->getId();
            retVal |= UA_Variant_setScalarCopy(&dataValue->value, stateId, &UA_TYPES[UA_TYPES_NODEID]);
            dataValue->hasValue = true;
            return retVal;
        }
    }
    return UA_STATUSCODE_BADINTERNALERROR;
}

UA_StatusCode SAMYRobot::readSkillCurrentState(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    for( int i = 0; i < robot->robotSkills.size(); i++ )
    {
        if( robot->robotSkills[i].getSkillCurrentStateNodeId().identifier.numeric == nodeId->identifier.numeric )
        {
            auto stateName = robot->robotSkills[i].getSkillCurrentState()->getName();
            retVal |= UA_Variant_setScalarCopy(&dataValue->value, &stateName, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
            dataValue->hasValue = true;
            return retVal;
        }
    }
    return UA_STATUSCODE_BADINTERNALERROR;
}

UA_StatusCode SAMYRobot::readSkillLastTransition(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    for( int i = 0; i < robot->robotSkills.size(); i++ )
    {
        if( robot->robotSkills[i].getSkillLastTransitionNodeId().identifier.numeric == nodeId->identifier.numeric )
        {
            auto transitionName = robot->robotSkills[i].getSkillLastTransition()->getName();
            retVal |= UA_Variant_setScalarCopy(&dataValue->value, &transitionName, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
            dataValue->hasValue = true;
            return retVal;
        }
    }
    return UA_STATUSCODE_BADINTERNALERROR;
}

UA_StatusCode SAMYRobot::readSkillLastTransitionId(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    for( int i = 0; i < robot->robotSkills.size(); i++ )
    {
        if( robot->robotSkills[i].getSkillLastTransitionNodeId().identifier.numeric == nodeId->identifier.numeric ){
            const UA_NodeId* transitionId = robot->robotSkills[i].getSkillLastTransition()->getId();
            retVal |= UA_Variant_setScalarCopy(&dataValue->value, transitionId, &UA_TYPES[UA_TYPES_NODEID]);
            dataValue->hasValue = true;
            return retVal;
        }
    }
    return UA_STATUSCODE_BADINTERNALERROR;
}





UA_StatusCode SAMYRobot::readRobotCurrentState(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    auto stateName = robot->currentState->getName();
    retVal |= UA_Variant_setScalarCopy(&dataValue->value, &stateName, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
    dataValue->hasValue = true;
    return retVal;
}
UA_StatusCode SAMYRobot::readRobotCurrentStateId(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    const UA_NodeId* stateId = robot->currentState->getId();
    retVal |= UA_Variant_setScalarCopy(&dataValue->value, stateId, &UA_TYPES[UA_TYPES_NODEID]);
    dataValue->hasValue = true;
    return retVal;
}
UA_StatusCode SAMYRobot::readRobotLastTransition(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    auto lastTrans = robot->lastTransition->getName();
    retVal |= UA_Variant_setScalarCopy(&dataValue->value, &lastTrans, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
    dataValue->hasValue = true;
    return retVal;
}
UA_StatusCode SAMYRobot::readRobotLastTransitionId(
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
    auto* robot = static_cast<SAMYRobot*>(nodeContext);
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    const UA_NodeId* transitionId = robot->lastTransition->getId();
    retVal |= UA_Variant_setScalarCopy(&dataValue->value, transitionId, &UA_TYPES[UA_TYPES_NODEID]);
    dataValue->hasValue = true;
    return retVal;
}

UA_StatusCode SAMYRobot::initializeRobotSkills( UA_Server* server ){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    for( auto& skill : robotSkills ){
        skill.initializeSkill( server );
        retval |= addSkillDataSources( server, skill.getSkillNodeID() );
        if (retval != UA_STATUSCODE_GOOD) {
            throw std::runtime_error("Failed to add data sources with error: "
                                     + std::string(UA_StatusCode_name(retval)));
        }
    }
}

UA_StatusCode SAMYRobot::addRobotDataSources( UA_Server* server )
{
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_DataSource dataSource{};
    dataSource.write = nullptr;

    dataSource.read = &SAMYRobot::readRobotCurrentState;
    retval |= UA_Server_setNodeContext(server, this->currentStateNodeId, this);
    retval |= UA_Server_setVariableNode_dataSource(server, this->currentStateNodeId, dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

    /*
    dataSource.read = SAMYRobot::readRobotCurrentStateId;
    std::shared_ptr<UA_NodeId> currentStateIdNodeId =
            OPCUA::UA_Server_getObjectPropertyId(server, this->currentStateNodeId,
                                          UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
    UA_Server_setNodeContext(server, *currentStateIdNodeId, this);
    retval |=  UA_Server_setVariableNode_dataSource(server, *currentStateIdNodeId, dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }
*/
    dataSource.read = SAMYRobot::readRobotLastTransition;
    UA_Server_setNodeContext(server, this->lastTransitionNodeId, this);
    retval |=  UA_Server_setVariableNode_dataSource(server, this->lastTransitionNodeId, dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }
    /*
    dataSource.read = SAMYRobot::readRobotLastTransitionId;
    std::shared_ptr<UA_NodeId> lastTransitionIdNodeId =
            OPCUA::UA_Server_getObjectPropertyId(server, this->lastTransitionNodeId,
                                          UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
    UA_Server_setNodeContext(server, *lastTransitionIdNodeId, this);
    retval |=  UA_Server_setVariableNode_dataSource(server, *lastTransitionIdNodeId,
                                                  dataSource);
                                                  */
    return retval;
}

UA_StatusCode SAMYRobot::initializeRobot( UA_Server* server ){
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;

    transitions = generateTransitions( server );
    states = generateStates( server );

    if (states.empty()) {
        throw std::runtime_error("Got empty state array");
    }

    if (transitions.empty()) {
        throw std::runtime_error("Got empty transitions array");
    }

    // default initialization
    currentState = &states[0];
    // default value to avoid segfaults due to being null
    lastTransition = &transitions[0];

    retVal |= initializeRobotSkills(server);
    retVal |= addRobotDataSources(server);
}

UA_StatusCode SAMYRobot::addSkillDataSources( UA_Server* server, const UA_NodeId& skillNodeID )
{
    UA_StatusCode retval = UA_STATUSCODE_GOOD;

    UA_DataSource dataSource{};
    dataSource.write = nullptr;
    dataSource.read = &SAMYRobot::readSkillCurrentState;
    std::shared_ptr<UA_NodeId> currentStateNodeId =
            UA_Server_getObjectComponentId(server, skillNodeID,
                                           UA_QUALIFIEDNAME(0, const_cast<char*>("CurrentState")));
    UA_Server_setNodeContext(server, *currentStateNodeId, this);
    retval = UA_Server_setVariableNode_dataSource(server, *currentStateNodeId, dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

    dataSource.read = SAMYRobot::readSkillCurrentStateId;
    std::shared_ptr<UA_NodeId> currentStateIdNodeId =
            OPCUA::UA_Server_getObjectPropertyId(server, *currentStateNodeId,
                                          UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
    UA_Server_setNodeContext(server, *currentStateIdNodeId, this);
    retval = UA_Server_setVariableNode_dataSource(server,
                                                  *currentStateIdNodeId,
                                                  dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

    // LastTransition is optional for FiniteStateMachines
    std::shared_ptr<UA_NodeId> lastTransitionNodeId =
            OPCUA::UA_Server_getObjectComponentId_or_Null(server, skillNodeID,
                                                   UA_QUALIFIEDNAME(0, const_cast<char*>("LastTransition")));

    if (!lastTransitionNodeId) {
        return UA_STATUSCODE_GOOD;
    }
    dataSource.read = SAMYRobot::readSkillLastTransition;
    UA_Server_setNodeContext(server, *lastTransitionNodeId, this);
    retval = UA_Server_setVariableNode_dataSource(server, *lastTransitionNodeId,
                                                  dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }

    dataSource.read = SAMYRobot::readSkillLastTransitionId;
    std::shared_ptr<UA_NodeId> lastTransitionIdNodeId =
            OPCUA::UA_Server_getObjectPropertyId(server, *lastTransitionNodeId,
                                          UA_QUALIFIEDNAME(0, const_cast<char*>("Id")));
    UA_Server_setNodeContext(server, *lastTransitionIdNodeId, this);
    retval = UA_Server_setVariableNode_dataSource(server, *lastTransitionIdNodeId,
                                                  dataSource);
    if (retval != UA_STATUSCODE_GOOD) {
        return retval;
    }
    return retval;
}

}
#if pubsub
void configureSAMYRobotPublisherUADP(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount){
    robot->publisher.switchField = PublisherTypeSwitch_PUBLISHER_UADP;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configurePublisherUADP(&(robot->publisher.publishers.publisherUADP), robot->id, robot->name,
                                publishingInterval, keyFrameCount, networkAddressUrl, robot->SAMYRobotVariableNodeId);
}

#ifdef UA_ENABLE_JSON_ENCODING

void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                                UA_Boolean JSONEncoding)
{
    robot->publisher.switchField = PublisherTypeSwitch_PUBLISHER_MQTT;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configurePublisherMQTT_WithoutLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                            publishingInterval, keyFrameCount, networkAddressUrl,
                                                robot->SAMYRobotVariableNodeId, JSONEncoding);
}
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                         UA_Boolean JSONEncoding, MQTT_LoginData login)
{
    robot->publisher.switchField = PublisherTypeSwitch_PUBLISHER_MQTT;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configurePublisherMQTT_WithLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                      publishingInterval, keyFrameCount, networkAddressUrl,
                                        robot->SAMYRobotVariableNodeId, JSONEncoding, login);
}
#else
void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount)
{
    robot->publisher.switchField = PublisherTypeSwitch_PUBLISHER_MQTT;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configurePublisherMQTT_WithoutLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                            publishingInterval, keyFrameCount, networkAddressUrl,
                                                robot->SAMYRobotVariableNodeId);
}
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                            MQTT_LoginData login)
{
    robot->publisher.switchField = PublisherTypeSwitch_PUBLISHER_MQTT;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configurePublisherMQTT_WithLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                      publishingInterval, keyFrameCount, networkAddressUrl,
                                        robot->SAMYRobotVariableNodeId, login);
}
#endif

UA_StatusCode addSAMYRobotPublisherToServer(UA_Server* server, SAMYRobot* robot){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    if(robot->publisher.switchField == PublisherTypeSwitch_PUBLISHER_UADP){
        retval |= addPublisherUADP_ToServer(server, &(robot->publisher.publishers.publisherUADP));
    }else{
        retval |= addPublisherMQTT_ToServer(server, &(robot->publisher.publishers.publisherMQTT));
    }
    return retval;
}

void configureSAMYRobotSubscriberUADP(SAMYRobot* robot){
    robot->subscriber.switchField = SubscriberTypeSwitch_SUBSCRIBER_UADP;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configureSubscriberUADP(&(robot->subscriber.subscribers.subscriberUADP), robot->id, robot->name, networkAddressUrl);
}

UA_StatusCode addSAMYRobotSubscriberToServer(UA_Server* server, SAMYRobot* robot){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    if(robot->subscriber.switchField == SubscriberTypeSwitch_SUBSCRIBER_UADP){
        retval |= addSubscriberUADP_ToServer(server, &(robot->subscriber.subscribers.subscriberUADP));
    }else{
        printf("MQTT SUBSCRIBER Not implemented yet!!");
    }
    return retval;
}
#endif
