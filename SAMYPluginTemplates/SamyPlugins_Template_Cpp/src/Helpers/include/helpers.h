#ifndef HELPERS_H
#define HELPERS_H

#include "namespace_crcl_generated.h"
#include <types_crcl_generated_handling.h>
#include "samy_robot.h"
#include <iostream>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

namespace SAMY{
namespace HelperFunctions {

    UA_StatusCode getNodeByBrowseName(UA_Client* client, UA_NodeId* nodeId,
                                      UA_NodeId* returnNodeId, std::string name);
    const size_t nSelectClauses = 2;
    UA_SimpleAttributeOperand * setupSelectClauses();
    void printCRCLSkill( const UA_CRCLSkillDataType* skill);
    UA_StatusCode configureSamyRobot(SAMYRobot* samyRobot, UA_UInt16 id, char* robotName);
    UA_StatusCode addRobotToServer(UA_Server* server, SAMYRobot* samyRobot);
    void configureSAMYPluginServer(UA_Server* server, UA_UInt32 port);
    UA_StatusCode addLastSkill_succeeded_VariableNode(UA_Server* server);
}
}

#endif
