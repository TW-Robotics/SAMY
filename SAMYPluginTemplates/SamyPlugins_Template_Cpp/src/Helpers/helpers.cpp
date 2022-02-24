#include <helpers.h>

namespace SAMY {
namespace HelperFunctions {

UA_StatusCode getNodeByBrowseName(UA_Client* client, UA_NodeId* nodeId,
                                  UA_NodeId* returnNodeId, std::string name){
    UA_String ua_name;
    UA_String_init(&ua_name);
    ua_name.length = strlen(name.c_str());
    ua_name.data = (UA_Byte*)name.c_str();

    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();
    bReq.nodesToBrowseSize = 1;
    bReq.nodesToBrowse[0].nodeId = UA_NODEID_NUMERIC(nodeId->namespaceIndex, nodeId->identifier.numeric);
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */
    UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);
    for(size_t i = 0; i < bResp.resultsSize; ++i) {
        for(size_t j = 0; j < bResp.results[i].referencesSize; ++j) {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
           if (UA_String_equal(&ref->browseName.name, &ua_name)){
               returnNodeId->identifier.numeric = ref->nodeId.nodeId.identifier.numeric;
               returnNodeId->namespaceIndex = ref->nodeId.nodeId.namespaceIndex;
               returnNodeId->identifierType = ref->nodeId.nodeId.identifierType;
               return UA_STATUSCODE_GOOD;
           }
        }
    }
    printf("No node with browse name %s\n", name.c_str());
    return EXIT_FAILURE;
}


UA_SimpleAttributeOperand * setupSelectClauses() {
    UA_SimpleAttributeOperand *selectClauses = (UA_SimpleAttributeOperand*)
        UA_Array_new(nSelectClauses, &UA_TYPES[UA_TYPES_SIMPLEATTRIBUTEOPERAND]);
    if(!selectClauses)
        return NULL;

    for(size_t i =0; i<nSelectClauses; ++i) {
        UA_SimpleAttributeOperand_init(&selectClauses[i]);
    }

    selectClauses[0].typeDefinitionId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE);
    selectClauses[0].browsePathSize = 1;
    selectClauses[0].browsePath = (UA_QualifiedName*)
        UA_Array_new(selectClauses[0].browsePathSize, &UA_TYPES[UA_TYPES_QUALIFIEDNAME]);
    if(!selectClauses[0].browsePath) {
        UA_SimpleAttributeOperand_delete(selectClauses);
        return NULL;
    }
    selectClauses[0].attributeId = UA_ATTRIBUTEID_VALUE;
    selectClauses[0].browsePath[0] = UA_QUALIFIEDNAME_ALLOC(0, "Message");

    selectClauses[1].typeDefinitionId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE);
    selectClauses[1].browsePathSize = 1;
    selectClauses[1].browsePath = (UA_QualifiedName*)
        UA_Array_new(selectClauses[1].browsePathSize, &UA_TYPES[UA_TYPES_QUALIFIEDNAME]);
    if(!selectClauses[1].browsePath) {
        UA_SimpleAttributeOperand_delete(selectClauses);
        return NULL;
    }
    selectClauses[1].attributeId = UA_ATTRIBUTEID_VALUE;
    selectClauses[1].browsePath[0] = UA_QUALIFIEDNAME_ALLOC(0, "Severity");

    return selectClauses;
}

UA_StatusCode configureSamyRobot(SAMYRobot* samyRobot, UA_UInt16 id, char* robotName){
    samyRobot->id = id; /* IT MUST BE A UINT16 number, otherwise it changes the number when compiling due to overflow!!! Compile with pedantic?*/
    samyRobot->name = UA_STRING(robotName);
    samyRobot->SAMYRobotVariableNodeId = UA_NODEID_STRING(1, "Robot");
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    return  retVal;
}

UA_StatusCode addRobotToServer(UA_Server* server, SAMYRobot* samyRobot){
    UA_SAMYRobotDataType robotOPCUA;

    robotOPCUA.id = samyRobot->id;
    robotOPCUA.name = samyRobot->name;

    UA_PubSubIPAddresses pubSubAddresses;
    pubSubAddresses.iPAddress_Skill = UA_STRING("None");
    pubSubAddresses.iPAddress_Status = UA_STRING("None");
    robotOPCUA.iPAddresses = pubSubAddresses;

    robotOPCUA.requested_Skill.cRCLCommands = NULL;
    robotOPCUA.requested_Skill.cRCLCommandsSize = 0;
    robotOPCUA.requested_Skill.id = 10;
    robotOPCUA.requested_Skill.name = UA_STRING("skill");

    UA_VariableAttributes vattr = UA_VariableAttributes_default;

    vattr.description = UA_LOCALIZEDTEXT("locale", (char*)samyRobot->name.data);
    vattr.valueRank = UA_VALUERANK_ANY;
    vattr.displayName = UA_LOCALIZEDTEXT("locale", (char*)samyRobot->name.data);
    vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE].typeId;
    UA_UInt32 myArrayDimensions[1] = {1};
    vattr.value.arrayDimensions = myArrayDimensions;
    vattr.value.arrayDimensionsSize = 1;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_Variant_setScalar(&vattr.value, &robotOPCUA, &UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE]);

    UA_StatusCode retVal = UA_Server_addVariableNode(server, samyRobot->SAMYRobotVariableNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(1, (char*)samyRobot->name.data),
                                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vattr, NULL, NULL);

    if(retVal == UA_STATUSCODE_GOOD){
        printf("ROBOT CORRECTLY ADDED TO PLUGIN SERVER\n");

    }else{
        printf("ERRORR ADDING ROBOT TO PLUGIN SERVER\n");
    }
    return retVal;
}

void configureSAMYPluginServer(UA_Server* server, UA_UInt32 port){
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, port, NULL);
}

UA_StatusCode addLastSkill_succeeded_VariableNode(UA_Server* server){
    UA_Boolean skillFinished = true;

    UA_VariableAttributes vattr = UA_VariableAttributes_default;

    vattr.description = UA_LOCALIZEDTEXT("locale", "lastSkill_succeeded Boolean");
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.displayName = UA_LOCALIZEDTEXT("locale", "lastSkill_succeeded Boolean");
    vattr.dataType = UA_TYPES[UA_TYPES_BOOLEAN].typeId;
    UA_UInt32 myArrayDimensions[1] = {1};
    vattr.value.arrayDimensions = myArrayDimensions;
    vattr.value.arrayDimensionsSize = 1;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_Variant_setScalar(&vattr.value, &skillFinished, &UA_TYPES[UA_TYPES_BOOLEAN]);

    UA_StatusCode retVal = UA_Server_addVariableNode(server, UA_NODEID_STRING(1, "lastSkill_succeeded"), UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT), UA_QUALIFIEDNAME(1, "lastSkill_succeeded"),
                                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), vattr, NULL, NULL);

    if(retVal == UA_STATUSCODE_GOOD){
        printf("lastSkill_succeeded BOOLEAN VARIABLE CORRECTLY ADDED TO PLUGIN SERVER\n");

    }else{
        printf("ERRORR ADDING lastSkill_succeeded VARIABLE TO PLUGIN SERVER\n");
    }
    return retVal;
}

void printCRCLSkill( const UA_CRCLSkillDataType* skill){
    std::cout << "Printing CRCL command\n";
    std::cout << "Number of commands in Skill: " << skill->cRCLCommandsSize << std::endl;
    std::cout << "Commands: { " << std::endl;

    for(int i=0; i < skill->cRCLCommandsSize; i++){
        std::cout << "\tCommand " << i << ":{" << std::endl;

        int type = skill->cRCLCommands[i].switchField;
        std::cout<< "\t\tCRCLCommandsUnion  type: ";

        switch (type) {
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND:
        {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_InitCanonDataType command = skill->cRCLCommands[i].fields.initCanonCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
        }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_EndCanonDataType command = skill->cRCLCommands[i].fields.endCanonCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_MessageDataType command = skill->cRCLCommands[i].fields.messageCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_MoveToDataType command = skill->cRCLCommands[i].fields.moveToCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_MoveScrewDataType command = skill->cRCLCommands[i].fields.moveScrewCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_MoveThroughToDataType command = skill->cRCLCommands[i].fields.moveThroughToCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_DwellDataType command = skill->cRCLCommands[i].fields.dwellCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_ActuateJointsDataType command = skill->cRCLCommands[i].fields.actuateJointsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_ConfigureJointReportsDataType command = skill->cRCLCommands[i].fields.configureJointReportsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetDefaultJointPositionsTolerancesDataType command = skill->cRCLCommands[i].fields.setDefaultJointPositionsTolerancesCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_GetStatusDataType command = skill->cRCLCommands[i].fields.getStatusCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_CloseToolChangerDataType command = skill->cRCLCommands[i].fields.closeToolChangerCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_OpenToolChangerDataType command = skill->cRCLCommands[i].fields.openToolChangerCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetRobotParametersDataType command = skill->cRCLCommands[i].fields.setRobotParametersCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetEndeffectorParametersDataType command = skill->cRCLCommands[i].fields.setEndeffectorParametersCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetEndeffectorDataType command = skill->cRCLCommands[i].fields.setEndeffectorCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetTransAccelDataType command = skill->cRCLCommands[i].fields.setTransAccelCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetTransSpeedDataType command = skill->cRCLCommands[i].fields.setTransSpeedCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetRotAccelDataType command = skill->cRCLCommands[i].fields.setRotAccelCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetRotSpeedDataType command = skill->cRCLCommands[i].fields.setRotSpeedCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetAngleUnitsDataType command = skill->cRCLCommands[i].fields.setAngleUnitsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetEndPoseToleranceDataType command = skill->cRCLCommands[i].fields.setEndPoseToleranceCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetForceUnitsDataType command = skill->cRCLCommands[i].fields.setForceUnitsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetIntermediatePoseToleranceDataType command = skill->cRCLCommands[i].fields.setIntermediatePoseToleranceCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetLengthUnitsDataType command = skill->cRCLCommands[i].fields.setLengthUnitsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetMotionCoordinationDataType command = skill->cRCLCommands[i].fields.setMotionCoordinationCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_SetTorqueUnitsDataType command = skill->cRCLCommands[i].fields.setTorqueUnitsCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_StopMotionDataType command = skill->cRCLCommands[i].fields.stopMotionCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_ConfigureStatusReportDataType command = skill->cRCLCommands[i].fields.configureStatusReportCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_EnableSensorDataType command = skill->cRCLCommands[i].fields.enableSensorCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_DisableSensorDataType command = skill->cRCLCommands[i].fields.disableSensorCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_EnableGripperDataType command = skill->cRCLCommands[i].fields.enableGripperCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_DisableGripperDataType command = skill->cRCLCommands[i].fields.disableGripperCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_EnableRobotParameterStatusDataType command = skill->cRCLCommands[i].fields.enableRobotParameterStatusCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        case UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND:
            {
            std::cout<< "UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND "<< skill->cRCLCommands[i].switchField << std::endl;

            UA_DisableRobotParameterStatusDataType command = skill->cRCLCommands[i].fields.disableRobotParameterStatusCommand;
            UA_String str2;
            UA_String_init( &str2 );
            UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE], &str2 );
            std::cout<< str2.data << std::endl;
            break;
            }
        default:
            std::cout<< "ERROR: CRCLCOMMANDSUNION WITH SWITCHFIELD " << type << " COULD NOT BE PRINTED" << std::endl;
            break;
        }
        std::cout<< "\t\t}" << std::endl ;
    }
    std::cout<< "\t}" << std::endl;
}

} /* namespace HelperFunctions */
} /* namespace SAMY */
