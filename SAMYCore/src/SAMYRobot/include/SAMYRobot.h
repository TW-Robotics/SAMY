#ifndef SAMYROBOT_H
#define SAMYROBOT_H

#include <algorithm>
#include <mutex>
#include <memory>
#include <helpers.h>

#ifndef PubSub
#include <vector>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>
#include <types_crcl_generated_handling.h>
#include <thread>
#else
#include <Publisher.h>
#include <Subscriber.h>
#endif

//#include "crcl_nodeids.h"
#include <namespace_crcl_generated.h>
#include "samyskill.h"

namespace SAMY {
    struct SAMYSkill;
}
#ifndef PubSub
namespace SAMY{

    struct SAMYRobot{

            UA_UInt16 id = 0;
            UA_String name = UA_STRING_NULL;
            std::vector<SAMY::SAMYSkill> robotSkills;
            UA_NodeId requested_skill;
            UA_CRCLStatusDataType robot_status;
            UA_PubSubIPAddresses ipAddresses;
            std::string address;
        //    std::queue<UA_CRCLSkillDataType> planToExecute;
        //    std::vector<UA_CRCLSkillDataType> robotPlan;
            UA_NodeId robotNodeIdInSAMYCore = UA_NODEID_NULL;
            UA_NodeId robotControllerNodeIdInSAMYCore = UA_NODEID_NULL;
            UA_NodeId robotNextSkillNodeId = UA_NODEID_NULL;
            int lastRequestedSkill = 0;
            std::shared_ptr<spdlog::logger> logger;


            UA_NodeId currentStateNodeId = UA_NODEID_NULL;
            UA_NodeId lastTransitionNodeId = UA_NODEID_NULL;
            UA_NodeId executedSkillsNodeId = UA_NODEID_NULL;
            FiniteDeque<UA_NodeId> executedSkills = FiniteDeque<UA_NodeId>{100};
            ProgramState const * currentState = nullptr;
            ProgramTransition const * lastTransition = nullptr;
            std::vector<ProgramState> states;
            std::vector<ProgramTransition> transitions;

            UA_StatusCode initializeRobotSkills( UA_Server* server );
            UA_StatusCode initializeRobot( UA_Server* server );

            SAMYRobot( std::shared_ptr<spdlog::logger> logger_ );

    private:
            UA_StatusCode addSkillDataSources( UA_Server* server, const UA_NodeId& skillNodeID );
            UA_StatusCode addRobotDataSources( UA_Server* server );

            static UA_StatusCode readSkillCurrentStateId(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readSkillCurrentState(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readSkillLastTransition(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readSkillLastTransitionId(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );


            static UA_StatusCode readRobotCurrentState(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readRobotCurrentStateId(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readRobotLastTransition(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );
            static UA_StatusCode readRobotLastTransitionId(
                    UA_Server* server,
                    const UA_NodeId* sessionId,
                    void* sessionContext,
                    const UA_NodeId* nodeId,
                    void* nodeContext,
                    UA_Boolean sourceTimeStamp,
                    const UA_NumericRange* range,
                    UA_DataValue* dataValue
            );

      //      std::shared_ptr<spdlog::logger> logger;
      //      std::mutex planMutex;
        };
}
    #else
namespace SAMY{

    typedef struct {
        /*The same fields than the SAMYRobot modelled in OPC UA (UA_SAMYRobot)*/
        UA_UInt16 id;
        UA_String name;
        std::vector<SAMYSkill> robotSkills;
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
}
    #endif

#endif /* SAMYROBOT_H */
