#include <helpers.h>

namespace SAMY {

UA_NodeId AdderParameterNodesToSkillType::findSkillType( const char* skillName ){

    UA_Int16 nsSkills = UA_Server_addNamespace( server, "http://SAMY.org/SAMYSkills" );

    UA_UInt32 length = 1;
    char *paths[length] = { const_cast<char*>( skillName ) };
    UA_UInt32 ids[length] = {UA_NS0ID_HASSUBTYPE};

    UA_BrowsePath browsePath;
    UA_BrowsePath_init(&browsePath);
    browsePath.startingNode = UA_NODEID_NUMERIC(nsSkills, CRCLSKILLS_NODE_ID); /* CRCLSkillsNode */
    browsePath.relativePath.elements = (UA_RelativePathElement*)UA_Array_new(length, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
    browsePath.relativePath.elementsSize = length;

    for(size_t i = 0; i < length; i++) {
        UA_RelativePathElement *elem = &browsePath.relativePath.elements[i];
        elem->referenceTypeId = UA_NODEID_NUMERIC(0, ids[i]);
        elem->targetName = UA_QUALIFIEDNAME_ALLOC(nsSkills, paths[i]);
    }

    UA_BrowsePathResult res = UA_Server_translateBrowsePathToNodeIds(server, &browsePath);
    if(res.statusCode != UA_STATUSCODE_GOOD || res.targetsSize < 1)
        throw "PARAMETER VARIABLE TYPE COULD NOT BE FOUND CRCLCOMMANDPARAMETERS TYPES: THE REQUIRED TYPE IS NOT IN THE BROWSEPATH";

    UA_NodeId typeNodeId = res.targets->targetId.nodeId;

    UA_BrowsePathResult_deleteMembers(&res);
    UA_BrowsePath_deleteMembers(&browsePath);

    return typeNodeId;
}

UA_NodeId AdderParameterNodesToSkillType::findSkillParameterSetObject( const char *skillName ){

    UA_NodeId initNode = findSkillType( skillName );
    UA_Int16 diNS = UA_Server_addNamespace( server, "http://opcfoundation.org/UA/DI/");
    return std::move( getComponentNodeByBrowseName( server, initNode, "ParameterSet", diNS ) );
}

UA_NodeId AdderParameterNodesToSkillType::findSkillParameterSetRealTimeObject( const char *skillName ){
    return std::move( getComponentNodeByBrowseName( server, skillTypeNode, "ParameterSetRealTime", skillsNS ) );
}

UA_StatusCode AdderParameterNodesToSkillType::addParameterNodesToServer(
                                                const std::string& parameterTypeName ){
    UA_Int16 crclNS = UA_Server_addNamespace( server, "https://crcl.org" );
    std::string name = std::to_string(numberOfCommandInSkill) + "_" + parameterTypeName;
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", (char*)name.c_str()  );
    vattr.displayName = UA_LOCALIZEDTEXT("", (char*)name.c_str() );
    UA_NodeId_init( &vattr.dataType );
    auto it = crclParameterName_DataTypeNodeId_Map.find( parameterTypeName );
    if( it != crclParameterName_DataTypeNodeId_Map.end()){
        UA_NodeId aux = it->second;
        vattr.dataType =  it->second;
    }else{
        throw "PARAMETER FOR SKILL COMMAND NOT FOUND";
    }

    UA_NodeId paramNodeId = UA_NODEID_NULL;

    retVal |= UA_Server_addVariableNode( server,
                                         UA_NODEID_NUMERIC(skillsNS, 0),
                                         skillParametersSetNode,
                                         UA_NODEID_NUMERIC(0, UA_NS0ID_HASORDEREDCOMPONENT ),
                                         UA_QUALIFIEDNAME( skillsNS, const_cast<char*>( name.data() ) ),
                                         UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                         vattr, NULL, &paramNodeId
                                         );

    retVal |= UA_Server_addReference( server, paramNodeId,
            UA_NODEID_NUMERIC(0, 37LU), UA_EXPANDEDNODEID_NUMERIC(0, 78LU), true);

    name = name + "_RealTime";

    UA_VariableAttributes vattr2 = UA_VariableAttributes_default;
    vattr2.valueRank = UA_VALUERANK_SCALAR;
    vattr2.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_LocalizedText_init( &vattr2.description );
    UA_LocalizedText_init( &vattr2.displayName );
    vattr2.description = UA_LOCALIZEDTEXT("", (char*)name.c_str()  );
    vattr2.displayName = UA_LOCALIZEDTEXT("", (char*)name.c_str() );
    UA_NodeId_init( &vattr2.dataType );
    vattr2.dataType =  it->second;

    UA_NodeId paramNodeIdRT = UA_NODEID_NULL;

    retVal |= UA_Server_addVariableNode( server,
                                         UA_NODEID_NUMERIC(skillsNS, 0),
                                         skillRealTimeParametersSetNode,
                                         UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                         UA_QUALIFIEDNAME( skillsNS, const_cast<char*>( name.c_str() ) ),
                                         UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                         vattr2, NULL, &paramNodeIdRT
                                         );
    retVal |= UA_Server_addReference( server, paramNodeIdRT,
            UA_NODEID_NUMERIC(0, 37LU), UA_EXPANDEDNODEID_NUMERIC(0, 78LU), true);

    return retVal;
}




void printCRCLSkill( const UA_CRCLSkillDataType* skill){
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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
            UA_String_deleteMembers(&str2);
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


UA_NodeId findCommandParameterType( UA_Server* server, char* parameterTypeName )
{
    UA_Int16 crclNS = UA_Server_addNamespace( server, "https://crcl.org" );

    UA_UInt32 length = 2;
    char *paths[length] = { "CRCLCommandParameters", parameterTypeName };
    UA_UInt32 ids[length] = {UA_NS0ID_HASSUBTYPE, UA_NS0ID_HASSUBTYPE};

    UA_BrowsePath browsePath;
    UA_BrowsePath_init(&browsePath);
    browsePath.startingNode = UA_NODEID_NUMERIC(0, 63); /* BaseDataVariableType node */
    browsePath.relativePath.elements = (UA_RelativePathElement*)UA_Array_new(length, &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]);
    browsePath.relativePath.elementsSize = length;

    for(size_t i = 0; i < length; i++) {
        UA_RelativePathElement *elem = &browsePath.relativePath.elements[i];
        elem->referenceTypeId = UA_NODEID_NUMERIC(0, ids[i]);
        elem->targetName = UA_QUALIFIEDNAME_ALLOC(crclNS, paths[i]);
    }

    UA_BrowsePathResult res = UA_Server_translateBrowsePathToNodeIds(server, &browsePath);
    if(res.statusCode != UA_STATUSCODE_GOOD || res.targetsSize < 1)
        throw "PARAMETER VARIABLE TYPE COULD NOT BE FOUND CRCLCOMMANDPARAMETERS TYPES: THE REQUIRED TYPE IS NOT IN THE BROWSEPATH";

    UA_NodeId typeNodeId = res.targets->targetId.nodeId;

    UA_BrowsePathResult_deleteMembers(&res);
    UA_BrowsePath_deleteMembers(&browsePath);

    return typeNodeId;
}

}
