#ifndef SAMYROBOT_H
#define SAMYROBOT_H

#include "namespace_crcl_generated.h"

#if pubsub
#include <Publisher.h>
#include <Subscriber.h>
#else
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#endif


typedef struct {
    /*The same fields than the SAMYRobot modelled in OPC UA (UA_SAMYRobot)*/
    UA_UInt16 id;
    UA_String name;
    UA_CRCLSkillDataType requested_skill;
    UA_CRCLStatusDataType robot_status;
    /*The same fields than the SAMYRobot modelled in OPC UA (UA_SAMYRobot)*/
    UA_NodeId SAMYRobotVariableNodeId;
    UA_Server* server;
} SAMYRobot;


#if pubsub
typedef struct {
    /*The same fields than the SAMYRobot modelled in OPC UA (UA_SAMYRobot)*/
    UA_UInt32 id;
    UA_String name;
    UA_CRCLSkillDataType requested_skill;
    UA_Boolean requested_Skill_success;
    UA_Boolean active;
    UA_Boolean online;
    UA_CRCLStatusDataType robot_status;
    UA_PubSubIPAddresses ipAddresses;
    /*The same fields than the SAMYRobot modelled in OPC UA (UA_SAMYRobot)*/
    UA_NodeId SAMYRobotVariableNodeId;
    Publisher publisher; /*Publisher is a Union of Publisher_UADP and Publisher_MQTT*/
    Subscriber subscriber;
} SAMYRobot;


void configureSAMYRobotPublisherUADP(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount);
#ifdef UA_ENABLE_JSON_ENCODING
void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                                UA_Boolean JSONEncoding);
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                            UA_Boolean JSONEncoding, MQTT_LoginData login);
#else
void configureSAMYRobotPublisherMQTT_WithoutLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount);
void configureSAMYRobotPublisherMQTT_WithLogin(SAMYRobot* robot, UA_UInt16 publishingInterval, UA_UInt32 keyFrameCount,
                                            MQTT_LoginData login);
#endif

UA_StatusCode addSAMYRobotPublisherToServer(UA_Server *server, SAMYRobot* robot);

void configureSAMYRobotSubscriberUADP(SAMYRobot* robot);
UA_StatusCode addSAMYRobotSubscriberToServer(UA_Server *server, SAMYRobot* robot);

#endif


#endif /* SAMYROBOT_H */
