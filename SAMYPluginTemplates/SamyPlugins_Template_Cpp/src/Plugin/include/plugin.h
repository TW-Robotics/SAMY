#ifndef PLUGIN_H
#define PLUGIN_H

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>
#include <namespace_crcl_generated.h>
#include <types_crcl_generated_handling.h>
#include <helpers.h>

#include <boost/thread.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/signals2.hpp>
#include <boost/exception/all.hpp>
#include <functional>
#include <signals.h>
#include <vector>
#include <unordered_map>
#include <thread>

struct skill
{
    UA_NodeId skillNodeId;
    std::string name;
};

const int COMMAND_ERROR = -1;
const int COMMAND_SUCCESS = 1;

class Plugin
{
public:
    Plugin(std::string samyCoreAddress_, std::string samyCorePort_, Signals* signals_);
    ~Plugin();
    UA_StatusCode InitPlugin(std::string robotName);
    UA_StatusCode RunClient(int timeout);
    UA_NodeId GetInformationSourceNodeId(const std::string name);
    bool *running;
    UA_Client* samy_core_client_read;

private:
    bool StartReadThread();
    void RunService();
    UA_StatusCode ConnectToCore();
    UA_StatusCode SubscribeToRobot();
    UA_StatusCode GetRobotNodeId(std::string robotName);
    UA_StatusCode GetSkillNodeId(std::string skillName, UA_NodeId* skillNodeId);
    UA_StatusCode GetListOfSkills();
    UA_StatusCode GetInformationSources();
    UA_StatusCode CreateSignalsForInformationSources();
    void ConnectSignals();
// ################ Methode Handling  ########################
    UA_StatusCode CallMethod(UA_NodeId *methodNode, UA_NodeId *objectNode);
    UA_StatusCode GetSkillMethods(UA_NodeId* skillNode, std::unordered_map<std::string, UA_NodeId> *methods);
    UA_StatusCode ResetSkill(UA_NodeId* skillNode);
    UA_StatusCode HaltSkill(UA_NodeId* skillNode);
    UA_StatusCode ResetAllSkills();
    UA_StatusCode HaltAllSkills();
    UA_StatusCode HaltCurrentSkill();
    UA_StatusCode ResetCurrentSkill();
    UA_StatusCode ResumeCurrentSkill();
    UA_StatusCode SuspendCurrentSkill();
// ################ Methode Handling  ########################
    static void HandlerEvents(UA_Client *client, UA_UInt32 subId, void *subContext,
                                UA_UInt32 monId, void *monContext,
                                size_t nEventFields, UA_Variant *eventFields);
    void ExecuteSkill(UA_NodeId* skillNode);

    std::string samyCoreAddress;
    std::string samyCorePort;
    UA_Client* samy_core_client;
    UA_NodeId* robot_node_id;
    UA_NodeId* robot_controller_node_id;
    UA_NodeId currentSkill;
    static std::vector<struct skill> skillList;
    Signals* signals;
    std::unordered_map<std::string, UA_NodeId> infoSources;

    // Variables for reading values from server in seperate thread
    bool m_started = false;
    boost::asio::io_service m_service;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_worker;
    boost::thread m_thread;
};

template <typename T>
bool WriteInfoSource(T* data, const UA_DataType* type, UA_NodeId id, UA_Client* client){
    UA_StatusCode retval;
    UA_Variant myVariant;
    UA_Variant_init(&myVariant);
    UA_Variant_setScalar(&myVariant, data, type);
    retval = UA_Client_writeValueAttribute(client, id, &myVariant);
    if (retval == UA_STATUSCODE_GOOD){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Writing to Node %d was succesfull", id.identifier.numeric);
        return true;
    } else {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Writing to Node %d was UNsuccesfull | Error: %s",id.identifier.numeric, UA_StatusCode_name(retval));
        return false;
    }
}

#endif // PLUGIN_H
