#include "plugin.h"

std::vector<struct skill> Plugin::skillList;

Plugin::Plugin(std::string samyCoreAddress_, std::string samyCorePort_, Signals* signals_):
    signals(signals_),
    samyCoreAddress(samyCoreAddress_),
    samyCorePort(samyCorePort_),
    m_worker(boost::asio::make_work_guard(m_service))
{
    robot_node_id = UA_NodeId_new();
    robot_controller_node_id = UA_NodeId_new();
}

Plugin::~Plugin()
{
    UA_NodeId_delete(robot_node_id);
    UA_NodeId_delete(robot_controller_node_id);
    //UA_Client_delete(samy_core_client);
    //UA_Client_delete(samy_core_client_read);
}

UA_StatusCode Plugin::InitPlugin(std::string robotName){

    UA_StatusCode retval;

    retval = ConnectToCore();
    sleep(1);     // give the client time to connect
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Connecting to SAMY Core failed");
        return retval;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Connected to SAMY Core.");

    retval = GetRobotNodeId(robotName);
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Getting Robot Node Id failed" );
        return retval;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Got Robot Node Id.");

    retval = SubscribeToRobot();
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Subscribing to Robot failed" );
        return retval;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Subscribed to NextSkillNodeId.");

    retval = GetListOfSkills();
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Getting List of Skills failed." );
        return retval;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Got List of all skills.");

    retval = ResetAllSkills();
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Resetting all skills failed" );
    } else UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "All Skills reseted");

    retval = GetInformationSources();
    if (retval != UA_STATUSCODE_GOOD){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Getting the information sources failed" );
        return retval;
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Got information sources");

    ConnectSignals();
    return retval;
}

bool Plugin::StartReadThread() {
    if (m_started)
      return true;
    m_started = true;

    // start reader thread
    m_thread = boost::thread(boost::bind(&Plugin::RunService, this));
    return m_started;
}

void Plugin::RunService(){
    // Create opcua client in thread
    samy_core_client_read = UA_Client_new();
    std::string endpoint = "opc.tcp://"+ samyCoreAddress + ":" + samyCorePort;
    UA_DataTypeArray customDataTypesCRCL{NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_ClientConfig *cc = UA_Client_getConfig( samy_core_client_read );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypesCRCL;

    UA_StatusCode retval = UA_Client_connect( samy_core_client_read, endpoint.c_str() );

    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(samy_core_client_read);
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Connectiong to server faild: read client");
    }
    m_service.run();
    UA_Client_delete(samy_core_client_read);
}

UA_StatusCode Plugin::RunClient(int timeout){
    UA_StatusCode retval;
    while (*running){
        retval = UA_Client_run_iterate(samy_core_client, timeout);
    }
    HaltAllSkills();
    return retval;
}

UA_StatusCode Plugin::ConnectToCore(){

    samy_core_client = UA_Client_new();
    std::string endpoint = "opc.tcp://"+ samyCoreAddress + ":" + samyCorePort;
    UA_DataTypeArray customDataTypes{NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_ClientConfig *cc = UA_Client_getConfig( samy_core_client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;

    UA_StatusCode retval = UA_Client_connect( samy_core_client, endpoint.c_str() );

    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(samy_core_client);
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Connecting to server faild");
        return retval;
    }
    StartReadThread();

    return retval;
}

UA_StatusCode Plugin::SubscribeToRobot(){

    UA_StatusCode retval;

    UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
    UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(samy_core_client, request,
                                                                                NULL, NULL, NULL);
    if(response.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
        UA_Client_disconnect(samy_core_client);
        UA_Client_delete(samy_core_client);
        return EXIT_FAILURE;
    }


    UA_UInt32 subId = response.subscriptionId;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Create subscription succeeded, id %u", subId);

    // Add a MonitoredItem
    UA_MonitoredItemCreateRequest item;
    UA_MonitoredItemCreateRequest_init(&item);
    item.itemToMonitor.nodeId = *robot_node_id;
    item.itemToMonitor.attributeId = UA_ATTRIBUTEID_EVENTNOTIFIER;
    item.monitoringMode = UA_MONITORINGMODE_REPORTING;

    UA_EventFilter filter;
    UA_EventFilter_init(&filter);
    filter.selectClauses = SAMY::HelperFunctions::setupSelectClauses();
    filter.selectClausesSize = SAMY::HelperFunctions::nSelectClauses;

    item.requestedParameters.filter.encoding = UA_EXTENSIONOBJECT_DECODED;
    item.requestedParameters.filter.content.decoded.data = &filter;
    item.requestedParameters.filter.content.decoded.type = &UA_TYPES[UA_TYPES_EVENTFILTER];

//    UA_UInt32 monId = 0;
    UA_MonitoredItemCreateResult result =
        UA_Client_MonitoredItems_createEvent(samy_core_client, subId,
                                             UA_TIMESTAMPSTORETURN_BOTH, item,
                                             (void*)(this), this->HandlerEvents, NULL);

    if(result.statusCode != UA_STATUSCODE_GOOD) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Could not add the MonitoredItem with %s", UA_StatusCode_name(result.statusCode));
    } else {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                    "Monitoring Robot, id %u", response.subscriptionId);
    }

    // TODO Not needed?
//    monId = result.monitoredItemId;

    return result.statusCode;
}

UA_StatusCode Plugin::GetRobotNodeId(std::string robotName){
    UA_NodeId tmp_node_id;
    UA_NodeId object_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, &object_node_id,
                                               &tmp_node_id, "DeviceSet");
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, &tmp_node_id,
                                               robot_node_id, robotName);
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, robot_node_id,
                                               &tmp_node_id, "Controllers");
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, &tmp_node_id,
                                               robot_controller_node_id, robotName);
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode Plugin::GetSkillNodeId(std::string skillName, UA_NodeId* skillNodeId){
    UA_NodeId tmp_node_id;
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, robot_controller_node_id,
                                               &tmp_node_id, "Skills");
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, &tmp_node_id,
                                               skillNodeId, skillName);
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode Plugin::GetListOfSkills(){
    UA_NodeId skillsNodeId;
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, robot_controller_node_id,
                                               &skillsNodeId, "Skills");
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = skillsNodeId;
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(samy_core_client, bReq);
    for(size_t i = 0; i < bResp.resultsSize; ++i) {
        for(size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if (ref->nodeClass == UA_NODECLASS_OBJECT){
                struct skill skill;
                std::string name((const char*)ref->browseName.name.data);
                skill.skillNodeId = ref->nodeId.nodeId;
                skill.name = name;
                skillList.push_back(skill);
            }
        }
    }
    UA_BrowseRequest_clear(&bReq);
    UA_BrowseResponse_clear(&bResp);

    // Remove Mandatory Node
    skillList.erase(skillList.begin());

//    for (int i = 0; i < skillList.size(); i++){
//        printf("Skill Name %d: %s\n", i, skillList[i].name.c_str());
//    }
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode Plugin::GetInformationSources(){
    UA_StatusCode retval = UA_STATUSCODE_GOOD;
    int cnt = 0;
    UA_NodeId infoSourcesNode;
    UA_NodeId object_node_id = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client, &object_node_id,
                                               &infoSourcesNode, "InformationSources");
    //Browse information sources node and generate unorderd map with all sources names and node ids
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = infoSourcesNode;
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(samy_core_client_read, bReq);
    for(size_t i = 0; i < bResp.resultsSize; ++i) {
        for(size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if (ref->nodeClass == UA_NODECLASS_OBJECT){
                UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found information Variable Object");
                UA_BrowseRequest bReq2;
                UA_BrowseRequest_init(&bReq2);
                bReq2.requestedMaxReferencesPerNode = 0;
                bReq2.nodesToBrowse = UA_BrowseDescription_new();
                bReq2.nodesToBrowseSize = 1;
                bReq2.nodesToBrowse[0].nodeId = ref->nodeId.nodeId;
                bReq2.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
                UA_BrowseResponse bResp2 = UA_Client_Service_browse(samy_core_client_read, bReq2);
                for(size_t i = 0; i < bResp2.resultsSize; ++i) {
                    for(size_t j = 0; j < bResp2.results[i].referencesSize; ++j) {
                        UA_ReferenceDescription *ref = &(bResp2.results[i].references[j]);
                        if (ref->nodeClass == UA_NODECLASS_VARIABLE){
                            UA_LOG_DEBUG(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found information Variable Node");
                            std::pair<std::string, UA_NodeId> infoSource ((const char*)ref->browseName.name.data,
                                                                      ref->nodeId.nodeId);
                            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "InfoSource Name '%.*s'",
                                                  (int)ref->browseName.name.length, (const char*)ref->browseName.name.data);
                            infoSources.insert(infoSource);
                            cnt++;
                        }
                    }
                }
            }
        }
    }
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found %d information sources", cnt);
    return retval;
}

UA_NodeId Plugin::GetInformationSourceNodeId(const std::string name){
    UA_NodeId id;
    try {
        id = infoSources.at(name);
    } catch (const std::out_of_range){
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "No InformationSource with name %s", name.c_str());
        return UA_NODEID_NULL;
    }
    return id;
}

void Plugin::ConnectSignals(){
    signals->Halt.connect(boost::bind(&Plugin::HaltCurrentSkill, this));
    signals->Reset.connect(boost::bind(&Plugin::ResetCurrentSkill, this));
    signals->Resume.connect(boost::bind(&Plugin::ResumeCurrentSkill, this));
    signals->Suspend.connect(boost::bind(&Plugin::SuspendCurrentSkill, this));
}

// ################ Methode Handling START ########################

UA_StatusCode Plugin::CallMethod(UA_NodeId* methodNode, UA_NodeId* objectNode){
 /* Call a remote method */
    UA_StatusCode retval;
    UA_Variant input;
    UA_String argString = UA_STRING("Hello Server");
    UA_Variant_init(&input);
    UA_Variant_setScalarCopy(&input, &argString, &UA_TYPES[UA_TYPES_STRING]);
    size_t outputSize;
    UA_Variant *output;
    retval = UA_Client_call(samy_core_client_read, *objectNode,
                            *methodNode, 0, NULL, &outputSize, &output);
    if(retval == UA_STATUSCODE_GOOD) {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method call was successful, and %lu returned values available.",
                    (unsigned long)outputSize);
        UA_Array_delete(output, outputSize, &UA_TYPES[UA_TYPES_VARIANT]);
    } else {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Method call was unsuccessful, and %x returned values available.",
                    retval);
    }
    UA_Variant_clear(&input);
    return retval;
}

UA_StatusCode Plugin::GetSkillMethods(UA_NodeId* skillNode,
                                      std::unordered_map<std::string, UA_NodeId>* methods){
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = *skillNode;
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(samy_core_client_read, bReq);
    for(size_t i = 0; i < bResp.resultsSize; ++i) {
        for(size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if (ref->nodeClass == UA_NODECLASS_METHOD){
                //std::cout << (const char*)ref->browseName.name.data << std::endl;
                std::pair<std::string, UA_NodeId> method ((const char*)ref->browseName.name.data,
                                                          ref->nodeId.nodeId);
                methods->insert(method);
            }
        }
    }
    UA_BrowseRequest_clear(&bReq);
    UA_BrowseResponse_clear(&bResp);
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode Plugin::ResetSkill(UA_NodeId* skillNode){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(skillNode, &methods);
    retval = CallMethod(&methods.at("Reset"), skillNode);
    return retval;
}

UA_StatusCode Plugin::ResetCurrentSkill(){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(&currentSkill, &methods);
    retval = CallMethod(&methods.at("Reset"), &currentSkill);
    return retval;
}

UA_StatusCode Plugin::HaltSkill(UA_NodeId* skillNode){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(skillNode, &methods);
    retval = CallMethod(&methods.at("Halt"), skillNode);
    return retval;
}

UA_StatusCode Plugin::HaltCurrentSkill(){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(&currentSkill, &methods);
    retval = CallMethod(&methods.at("Halt"), &currentSkill);
    return retval;
}

UA_StatusCode Plugin::ResetAllSkills(){
    UA_StatusCode retval;
    for (int i = 0; i < skillList.size(); i++){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Reseting skill with name '%.*s'",
                    (int)skillList[i].name.length(), skillList[i].name.c_str());
        retval = ResetSkill(&skillList[i].skillNodeId);
    }
    return retval;
}

UA_StatusCode Plugin::HaltAllSkills(){
    UA_StatusCode retval;
    for (int i = 0; i < skillList.size(); i++){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Halting skill with name '%.*s'",
                    (int)skillList[i].name.length(), skillList[i].name.c_str());
        HaltSkill(&skillList[i].skillNodeId);
    }
    return retval;
}

UA_StatusCode Plugin::ResumeCurrentSkill(){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(&currentSkill, &methods);
    retval = CallMethod(&methods.at("Resume"), &currentSkill);
    return retval;
}

UA_StatusCode Plugin::SuspendCurrentSkill(){
    UA_StatusCode retval;
    std::unordered_map<std::string, UA_NodeId> methods;
    GetSkillMethods(&currentSkill, &methods);
    retval = CallMethod(&methods.at("Suspend"), &currentSkill);
    return retval;
}

// ################ Methode Handling END ########################


void Plugin::HandlerEvents(UA_Client *client, UA_UInt32 subId, void *subContext,
                            UA_UInt32 monId, void *monContext,
                            size_t nEventFields, UA_Variant *eventFields) {
    Plugin* plugin;
    plugin = (Plugin*)monContext;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Handler got en Event");

    for (size_t i = 0; i < nEventFields; i++){
        if (UA_Variant_hasScalarType(&eventFields[i], &UA_TYPES[UA_TYPES_LOCALIZEDTEXT])) {
            UA_LocalizedText *lt = (UA_LocalizedText *)eventFields[i].data;
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                        "Message: '%.*s'", (int)lt->text.length, lt->text.data);
            // Check if text includes a skill name from the skill list.
            std::string text((const char*)lt->text.data);
            for (int i = 0; i < skillList.size(); i++){
                if(text.find(skillList[i].name) != std::string::npos &&
                        text.find("Ready to Running") != std::string::npos){

                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found Skill with NodeId %d to execute",
                                skillList[i].skillNodeId.identifier.numeric);
                    plugin->currentSkill = skillList[i].skillNodeId;
                    plugin->m_service.post(boost::bind(&Plugin::ExecuteSkill, plugin, &skillList[i].skillNodeId));
                }
            }
        }
        else if (UA_Variant_hasScalarType(&eventFields[i], &UA_TYPES[UA_TYPES_NODEID])){
            UA_NodeId nextSkillNodeId = *(UA_NodeId *)eventFields[i].data;
            UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "NodeID: %d", nextSkillNodeId.identifier.numeric);
        }
        else if (UA_Variant_hasScalarType(&eventFields[i], &UA_TYPES[UA_TYPES_UINT16])){
            UA_UInt16 severity = *(UA_UInt16 *)eventFields[i].data;
        }
        else {
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                                "Don't know how to handle type: '%s'", eventFields[i].type->typeName);
        }
    }
}

void Plugin::ExecuteSkill(UA_NodeId* skillNode){

    bool error = false;
    UA_StatusCode retval;
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Starting to Execute Skill");
    UA_NodeId paramter_node_id;
    SAMY::HelperFunctions::getNodeByBrowseName(samy_core_client_read, skillNode,
                                               &paramter_node_id, "ParameterSet");

    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = paramter_node_id;
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(samy_core_client_read, bReq);

    for(size_t i = 0; i < bResp.resultsSize; i++) {
        for(size_t j = 0; j < bResp.results[i].referencesSize; j++) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if(ref->nodeClass == UA_NODECLASS_VARIABLE) {
                UA_Variant value;
                UA_Variant_init(&value);

                retval = UA_Client_readValueAttribute(samy_core_client_read, ref->nodeId.nodeId, &value);

                //UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Response reding Attribute %s", UA_StatusCode_name(retval));

                if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found InitCanon Type");
                    UA_InitCanonParametersSetDataType* InitCanon = (UA_InitCanonParametersSetDataType*) value.data;
                    if (*signals->InitCanon(InitCanon) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing InitCanon");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found EndCanon Type");
                    UA_EndCanonParametersSetDataType* EndCanon = (UA_EndCanonParametersSetDataType*) value.data;
                    if (*signals->EndCanon(EndCanon) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing EndCanon");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found Message Type");
                    UA_MessageParametersSetDataType* Message = (UA_MessageParametersSetDataType*) value.data;
                    if (*signals->Message(Message) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing Message");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETOPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found MoveTo Type");
                    UA_MoveToParametersSetDataType* moveto = (UA_MoveToParametersSetDataType*) value.data;
                    if (*signals->MoveTo(moveto) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing MoveTo");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found MoveScrew Type");
                    UA_MoveScrewParametersSetDataType* MoveScrew = (UA_MoveScrewParametersSetDataType*) value.data;
                    if (*signals->MoveScrew(MoveScrew) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing MoveScrew");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTOPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found MoveThroughTo Type");
                    UA_MoveThroughToParametersSetDataType* MoveThroughTo = (UA_MoveThroughToParametersSetDataType*) value.data;
                    if (*signals->MoveThroughTo(MoveThroughTo) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing MoveThroughTo");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found Dewll Type");
                    UA_DwellParametersSetDataType* Dwell = (UA_DwellParametersSetDataType*) value.data;
                    if (*signals->Dwell(Dwell) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing Dwell");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found ActuateJoints Type");
                    UA_ActuateJointsParametersSetDataType* ActuateJoints = (UA_ActuateJointsParametersSetDataType*) value.data;
                    if (*signals->ActuateJoints(ActuateJoints) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing ActuateJoints");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found ConfigureJointReports Type");
                    UA_ConfigureJointReportsParametersSetDataType* ConfigureJointReports = (UA_ConfigureJointReportsParametersSetDataType*) value.data;
                    if (*signals->ConfigureJointReports(ConfigureJointReports) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing ConfigureJointReports");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetDefaultJointPositionsTolerances Type");
                    UA_SetDefaultJointPositionsTolerancesParametersSetDataType* SetDefaultJointPositionsTolerances = (UA_SetDefaultJointPositionsTolerancesParametersSetDataType*) value.data;
                    if (*signals->SetDefaultJointPositionsTolerances(SetDefaultJointPositionsTolerances) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetDefaultJointPositionsTolerances");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found GetStatus Type");
                    UA_GetStatusParametersSetDataType* GetStatus = (UA_GetStatusParametersSetDataType*) value.data;
                    if (*signals->GetStatus(GetStatus) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing GetStatus");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found CloseToolChanger Type");
                    UA_CloseToolChangerParametersSetDataType* CloseToolChanger = (UA_CloseToolChangerParametersSetDataType*) value.data;
                    if (*signals->CloseToolChanger(CloseToolChanger) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing CloseToolChanger");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found OpenToolChanger Type");
                    UA_OpenToolChangerParametersSetDataType* OpenToolChanger = (UA_OpenToolChangerParametersSetDataType*) value.data;
                    if (*signals->OpenToolChanger(OpenToolChanger) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing OpenToolChanger");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetRobotParameters Type");
                    UA_SetRobotParametersParametersSetDataType* SetRobotParameters = (UA_SetRobotParametersParametersSetDataType*) value.data;
                    if (*signals->SetRobotParameters(SetRobotParameters) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetRobotParameters");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetEndeffectorParameters Type");
                    UA_SetEndeffectorParametersParametersSetDataType* SetEndeffectorParameters = (UA_SetEndeffectorParametersParametersSetDataType*) value.data;
                    if (*signals->SetEndeffectorParameters(SetEndeffectorParameters) < 0){
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetEndeffector Type");
                    UA_SetEndeffectorParametersSetDataType* SetEndeffector = (UA_SetEndeffectorParametersSetDataType*) value.data;
                    if (*signals->SetEndeffector(SetEndeffector) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetEndeffector");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetTransAccel Type");
                    UA_SetTransAccelParametersSetDataType* SetTransAccel = (UA_SetTransAccelParametersSetDataType*) value.data;
                    if (*signals->SetTransAccel(SetTransAccel) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetTransAccel");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetTransSpeed Type");
                    UA_SetTransSpeedParametersSetDataType* SetTransSpeed = (UA_SetTransSpeedParametersSetDataType*) value.data;
                    if (*signals->SetTransSpeed(SetTransSpeed) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetTransSpeed");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetRotAccel Type");
                    UA_SetRotAccelParametersSetDataType* SetRotAccel = (UA_SetRotAccelParametersSetDataType*) value.data;
                    if (*signals->SetRotAccel(SetRotAccel) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetRotAccel");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetRotSpeed Type");
                    UA_SetRotSpeedParametersSetDataType* SetRotSpeed = (UA_SetRotSpeedParametersSetDataType*) value.data;
                    if (*signals->SetRotSpeed(SetRotSpeed) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetRotSpeed");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetAngleUnits Type");
                    UA_SetAngleUnitsParametersSetDataType* SetAngleUnits = (UA_SetAngleUnitsParametersSetDataType*) value.data;
                    if (*signals->SetAngleUnits(SetAngleUnits) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetAngleUnits");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetEndPoseTolerance Type");
                    UA_SetEndPoseToleranceParametersSetDataType* SetEndPoseTolerance = (UA_SetEndPoseToleranceParametersSetDataType*) value.data;
                    if (*signals->SetEndPoseTolerance(SetEndPoseTolerance) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetEndPoseTolerance");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetForceUnits Type");
                    UA_SetForceUnitsParametersSetDataType* SetForceUnits = (UA_SetForceUnitsParametersSetDataType*) value.data;
                    if (*signals->SetForceUnits(SetForceUnits) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetForceUnits");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetIntermediatePoseTolerance Type");
                    UA_SetIntermediatePoseToleranceParametersSetDataType* SetIntermediatePoseTolerance = (UA_SetIntermediatePoseToleranceParametersSetDataType*) value.data;
                    if (*signals->SetIntermediatePoseTolerance(SetIntermediatePoseTolerance) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetIntermediatePoseTolerance");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetLengthUnits Type");
                    UA_SetLengthUnitsParametersSetDataType* SetLengthUnits = (UA_SetLengthUnitsParametersSetDataType*) value.data;
                    if (*signals->SetLengthUnits(SetLengthUnits) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetLengthUnits");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetMotionCoordination Type");
                    UA_SetMotionCoordinationParametersSetDataType* SetMotionCoordination = (UA_SetMotionCoordinationParametersSetDataType*) value.data;
                    if (*signals->SetMotionCoordination(SetMotionCoordination) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetMotionCoordination");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found SetTorqueUnits Type");
                    UA_SetTorqueUnitsParametersSetDataType* SetTorqueUnits = (UA_SetTorqueUnitsParametersSetDataType*) value.data;
                    if (*signals->SetTorqueUnits(SetTorqueUnits) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing SetTorqueUnits");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found StopMotion Type");
                    UA_StopMotionParametersSetDataType* StopMotion = (UA_StopMotionParametersSetDataType*) value.data;
                    if (*signals->StopMotion(StopMotion) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing StopMotion");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found ConfigureStatusReport Type");
                    UA_ConfigureStatusReportParametersSetDataType* ConfigureStatusReport = (UA_ConfigureStatusReportParametersSetDataType*) value.data;
                    if (*signals->ConfigureStatusReport(ConfigureStatusReport) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing ConfigureStatusReport");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found EnableSensor Type");
                    UA_EnableSensorParametersSetDataType* EnableSensor = (UA_EnableSensorParametersSetDataType*) value.data;
                    if (*signals->EnableSensor(EnableSensor) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing EnableSensor");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found DisableSensor Type");
                    UA_DisableSensorParametersSetDataType* DisableSensor = (UA_DisableSensorParametersSetDataType*) value.data;
                    if (*signals->DisableSensor(DisableSensor) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing DisableSensor");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found EnableGripper Type");
                    UA_EnableGripperParametersSetDataType* EnableGripper = (UA_EnableGripperParametersSetDataType*) value.data;
                    if (*signals->EnableGripper(EnableGripper) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing EnableGripper");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found DisableGripper Type");
                    UA_DisableGripperParametersSetDataType* DisableGripper = (UA_DisableGripperParametersSetDataType*) value.data;
                    if (*signals->DisableGripper(DisableGripper) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing DisableGripper");

                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found EnableRobotParameterStatus Type");
                    UA_EnableRobotParameterStatusParametersSetDataType* EnableRobotParameterStatus = (UA_EnableRobotParameterStatusParametersSetDataType*) value.data;
                    if (*signals->EnableRobotParameterStatus(EnableRobotParameterStatus) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing EnableRobotParameterStatus");
                        error = true;
                        break;
                    }
                }
                else if (value.type->typeId.identifier.numeric == UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE].typeId.identifier.numeric){
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Found DisableRobotParameterStatus Type");
                    UA_DisableRobotParameterStatusParametersSetDataType* DisableRobotParameterStatus = (UA_DisableRobotParameterStatusParametersSetDataType*) value.data;
                    if (*signals->DisableRobotParameterStatus(DisableRobotParameterStatus) < 0){
                        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Error while executing DisableRobotParameterStatus");
                        error = true;
                        break;
                    }
                }
                else {
                    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Unknown command");
                    error = true;
                }
            }
        }
        if (error) break;
    }

    if (!error){
        UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Skill finished without error");
        ResetSkill(skillNode);
    }
    UA_BrowseRequest_clear(&bReq);
    UA_BrowseResponse_clear(&bResp);
}



