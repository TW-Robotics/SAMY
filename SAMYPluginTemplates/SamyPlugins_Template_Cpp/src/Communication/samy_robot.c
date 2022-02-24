#include "samy_robot.h"

#if pubsub
void configureSAMYRobotPublisherUADP(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount){
    robot->publisher.switchField = 1;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configurePublisherUADP(&(robot->publisher.publishers.publisherUADP), robot->id, robot->name,
                                publishingInterval, keyFrameCount, networkAddressUrl, robot->SAMYRobotVariableNodeId);
}

#ifdef UA_ENABLE_JSON_ENCODING

void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                                UA_Boolean JSONEncoding)
{
    robot->publisher.switchField = 2;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configurePublisherMQTT_WithoutLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                            publishingInterval, keyFrameCount, networkAddressUrl,
                                                robot->SAMYRobotVariableNodeId, JSONEncoding);
}
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                         UA_Boolean JSONEncoding, MQTT_LoginData login)
{
    robot->publisher.switchField = 2;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configurePublisherMQTT_WithLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                      publishingInterval, keyFrameCount, networkAddressUrl,
                                        robot->SAMYRobotVariableNodeId, JSONEncoding, login);
}
#else
void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount)
{
    robot->publisher.switchField = 2;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configurePublisherMQTT_WithoutLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                            publishingInterval, keyFrameCount, networkAddressUrl,
                                                robot->SAMYRobotVariableNodeId);
}
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                            MQTT_LoginData login)
{
    robot->publisher.switchField = 2;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Status};
    configurePublisherMQTT_WithLogin(&(robot->publisher.publishers.publisherMQTT), robot->id, robot->name,
                                      publishingInterval, keyFrameCount, networkAddressUrl,
                                        robot->SAMYRobotVariableNodeId, login);
}
#endif

UA_StatusCode addSAMYRobotPublisherToServer(UA_Server* server, SAMYRobot* robot){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    if(robot->publisher.switchField == 1){
        retval |= addPublisherUADP_ToServer(server, &(robot->publisher.publishers.publisherUADP));
    }else{
        retval |= addPublisherMQTT_ToServer(server, &(robot->publisher.publishers.publisherMQTT));
    }
    return retval;
}

void configureSAMYRobotSubscriberUADP(SAMYRobot* robot){
    robot->subscriber.switchField = 1;
    UA_NetworkAddressUrlDataType networkAddressUrl = {UA_STRING_NULL , robot->ipAddresses.iPAddress_Skill};
    configureSubscriberUADP(&(robot->subscriber.subscribers.subscriberUADP), robot->id, robot->name, networkAddressUrl);
}
UA_StatusCode addSAMYRobotSubscriberToServer(UA_Server* server, SAMYRobot* robot){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    if(robot->subscriber.switchField == 1){
        retval |= addSubscriberUADP_ToServer(server, &(robot->subscriber.subscribers.subscriberUADP));
    }else{
        printf("MQTT SUBSCRIBER Not implemented yet!!");
    }
    return retval;
}

void translateCRCLCommand( const UA_CRCLCommandsUnionDataType* const command ){
    switch( command->switchField ){
        case 0:
            printf("Not valid command!!");
        case 1:
            translateInitCanon(&(command->fields.initCanonCommand));
        case 2:
            translateMoveToCommand(&(command->fields.moveToCommand));
        case 3:
            translateCloseToolChangerCommand(&(command->fields.closeToolChangerCommand));
        case 4:
            translateDwellCommand(&(command->fields.dwellCommand));
        case 5:
            translateGetStatusCommand(&(command->fields.getStatusCommand));
        case 6:
            translateMessageCommand(&(command->fields.messageCommand));
        case 7:
            translateEndCanonCommand(&(command->fields.endCanonCommand));
     }
}

void executeSkill( const UA_CRCLSkillDataType* const commands )
{
    for(size_t i = 0; i<commands->cRCLCommandsSize; i++){
        executeCRCLCommand(&(commands->cRCLCommands[i]));
    }
}

#endif

