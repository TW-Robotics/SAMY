#include <yaml_parsers.h>

namespace SAMY {
namespace Parsers {

static bool noCaseSensStringComparison(std::string & str1, const std::string &strExt)
{
    std::string str2 = strExt;
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(),
            [](char & c1, char & c2){return (c1 == c2 || std::toupper(c1) == std::toupper(c2));}));
}

UA_CRCLCommandsUnionDataType stringToCRCLCommandUnion(const std::string &strEx) {
    std::string str = strEx;
    if( noCaseSensStringComparison( str, "InitCanon" ) ){
        UA_CRCLCommandsUnionDataType command;
        UA_InitCanonDataType initCanon;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND;
        command.fields.initCanonCommand = initCanon;
        return command;
    }else if( noCaseSensStringComparison( str, "EndCanon" ) ){
        UA_CRCLCommandsUnionDataType command;
        UA_EndCanonDataType endCanon;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND;
        command.fields.endCanonCommand = endCanon;
        return command;
    }else if( noCaseSensStringComparison( str, "Message" )){
        UA_CRCLCommandsUnionDataType command;
        UA_MessageDataType message;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND;
        command.fields.messageCommand = message;
        return command;
    }else if( noCaseSensStringComparison( str, "MoveTo" )){
        UA_CRCLCommandsUnionDataType command;
        UA_MoveToDataType moveTo;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND;
        command.fields.moveToCommand = moveTo;
        return command;
    }else if(noCaseSensStringComparison( str, "MoveScrew" )){
        UA_CRCLCommandsUnionDataType command;
        UA_MoveScrewDataType moveScrew;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND;
        command.fields.moveScrewCommand = moveScrew;
        return command;
    }else if(noCaseSensStringComparison( str, "MoveThroughTo" )){
        UA_CRCLCommandsUnionDataType command;
        UA_MoveThroughToDataType moveThroughTo;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND;
        command.fields.moveThroughToCommand = moveThroughTo;
        return command;
    }else if(noCaseSensStringComparison( str, "Dwell" )){
        UA_CRCLCommandsUnionDataType command;
        UA_DwellDataType dwell;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND;
        command.fields.dwellCommand = dwell;
        return command;
    }else if(noCaseSensStringComparison( str, "ActuateJoints" )){
        UA_CRCLCommandsUnionDataType command;
        UA_ActuateJointsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND;
        command.fields.actuateJointsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "ConfigureJointReports" )){
        UA_CRCLCommandsUnionDataType command;
        UA_ConfigureJointReportsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND;
        command.fields.configureJointReportsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetDefaultJointPositionsTolerances" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetDefaultJointPositionsTolerancesDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND;
        command.fields.setDefaultJointPositionsTolerancesCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "GetStatus" )){
        UA_CRCLCommandsUnionDataType command;
        UA_GetStatusDataType getStatus;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND;
        command.fields.getStatusCommand = getStatus;
        return command;
    }else if(noCaseSensStringComparison( str, "CloseToolChanger" )){
        UA_CRCLCommandsUnionDataType command;
        UA_CloseToolChangerDataType closeTool;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND;
        command.fields.closeToolChangerCommand = closeTool;
        return command;
    }else if(noCaseSensStringComparison( str, "OpenToolChanger" )){
        UA_CRCLCommandsUnionDataType command;
        UA_OpenToolChangerDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND;
        command.fields.openToolChangerCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetRobotParameters" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetRobotParametersDataType setRobotParams;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND;
        command.fields.setRobotParametersCommand = setRobotParams;
        return command;
    }else if(noCaseSensStringComparison( str, "SetEndeffectorParameters" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetEndeffectorParametersDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND;
        command.fields.setEndeffectorParametersCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetEndeffector" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetEndeffectorDataType setEndeffector;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND;
        command.fields.setEndeffectorCommand = setEndeffector;
        return command;
    }else if(noCaseSensStringComparison( str, "SetTransAccel" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetTransAccelDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND;
        command.fields.setTransAccelCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetTransSpeed" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetTransSpeedDataType setTransSpeed;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND;
        command.fields.setTransSpeedCommand = setTransSpeed;
        return command;
    }else if(noCaseSensStringComparison( str, "SetRotAccel" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetRotAccelDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND;
        command.fields.setRotAccelCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetRotSpeed" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetRotSpeedDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND;
        command.fields.setRotSpeedCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetAngleUnits" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetAngleUnitsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND;
        command.fields.setAngleUnitsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetEndPoseTolerance" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetEndPoseToleranceDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND;
        command.fields.setEndPoseToleranceCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetForceUnits" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetForceUnitsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND;
        command.fields.setForceUnitsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetIntermediatePoseTolerance" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetIntermediatePoseToleranceDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND;
        command.fields.setIntermediatePoseToleranceCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetLengthUnits" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetLengthUnitsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND;
        command.fields.setLengthUnitsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetMotionCoordination" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetMotionCoordinationDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND;
        command.fields.setMotionCoordinationCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "SetTorqueUnits" )){
        UA_CRCLCommandsUnionDataType command;
        UA_SetTorqueUnitsDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND;
        command.fields.setTorqueUnitsCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "StopMotion" )){
        UA_CRCLCommandsUnionDataType command;
        UA_StopMotionDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND;
        command.fields.stopMotionCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "ConfigureStatusReport" )){
        UA_CRCLCommandsUnionDataType command;
        UA_ConfigureStatusReportDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND;
        command.fields.configureStatusReportCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "EnableSensor" )){
        UA_CRCLCommandsUnionDataType command;
        UA_EnableSensorDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND;
        command.fields.enableSensorCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "DisableSensor" )){
        UA_CRCLCommandsUnionDataType command;
        UA_DisableSensorDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND;
        command.fields.disableSensorCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "EnableGripper" )){
        UA_CRCLCommandsUnionDataType command;
        UA_EnableGripperDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND;
        command.fields.enableGripperCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "DisableGripper" )){
        UA_CRCLCommandsUnionDataType command;
        UA_DisableGripperDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND;
        command.fields.disableGripperCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "EnableRobotParameterStatus" )){
        UA_CRCLCommandsUnionDataType command;
        UA_EnableRobotParameterStatusDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND;
        command.fields.enableRobotParameterStatusCommand = aux;
        return command;
    }else if(noCaseSensStringComparison( str, "DisableRobotParameterStatus" )){
        UA_CRCLCommandsUnionDataType command;
        UA_DisableRobotParameterStatusDataType aux;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND;
        command.fields.disableRobotParameterStatusCommand = aux;
        return command;
    }else{
        UA_CRCLCommandsUnionDataType command;
        std::cout << "ERROR!!! THE COMMAND OR SKILL GIVEN IN THE SKILL DEFINITION DOES NOT EXIST!" << std::endl;
        std::cout << str << std::endl;
        command.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_NONE;
        return command;
    }
}

bool nameIsCRCLCommand(const std::string& name){
    std::vector<std::string> crclCommandsNames{
        "InitCanon",
        "EndCanon",
        "Message",
        "MoveTo",
        "MoveScrew",
        "MoveThroughTo",
        "Dwell",
        "ActuateJoints",
        "ConfigureJointReports",
        "ConfigureJointReport",
        "SetDefaultJointPositionsTolerances",
        "GetStatus",
        "CloseToolChanger",
        "OpenToolChanger",
        "SetRobotParameters",
        "SetEndeffectorParameters",
        "SetEndeffector",
        "SetTransAccel",
        "SetTransSpeed",
        "SetRotAccel",
        "SetRotSpeed",
        "SetAngleUnits",
        "SetEndPoseTolerance",
        "SetForceUnits",
        "SetIntermediatePoseTolerance",
        "SetLengthUnits",
        "SetMotionCoordination",
        "SetTorqueUnit",
        "StopMotion",
        "ConfigureStatusReport",
        "EnableSensor",
        "DisableSensor",
        "EnableGripper",
        "DisableGripper",
        "EnableRobotParameterStatus",
        "DisableRobotParameterStatus"
    };

    auto foundSkill = std::find_if(crclCommandsNames.begin(), crclCommandsNames.end(),
                                   [&](std::string& it)->bool{
                                              std::string aux = name;
                                              return noCaseSensStringComparison(aux, it);
                                      });

    return ( foundSkill != crclCommandsNames.end() ) ? true : false;
}

static bool stringIsInStringsVector(std::string& name, std::vector<std::string>& existing ){
    auto found = std::find_if(existing.begin(), existing.end(),
                                   [&](std::string& it)->bool{
                                              std::string aux = name;
                                              return noCaseSensStringComparison(aux, it);
                                      });

    return ( found != existing.end() ) ? true : false;
}

bool SkillsParser::parseSkills( const std::string& filepath, std::vector<SAMYSkill>& parsedSkills){

    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    std::vector<std::string> alreadyParsedSkillsNames;

    YAML::Node data = YAML::Load(strStream.str());

    if(!data["FundamentalSkills"])
        return false;

    // ParseFundamentalSkills
    auto fundamentalSkillsNodes = data["FundamentalSkills"];

    /* Used for generating the NodeId number that will be used when adding the corresponding
     * skill type to the information model */
    UA_Int16 skillsCounter = 10000;

    if( fundamentalSkillsNodes )
    {
        for(auto fundamentalSkillNode : fundamentalSkillsNodes )
        {
            auto skillNode = fundamentalSkillNode["FundamentalSkill"];
            std::vector<UA_CRCLCommandsUnionDataType> commands;
            std::string skillName;
            if(skillNode)
            {
                skillName = skillNode["SkillName"].as<std::string>();

                if( nameIsCRCLCommand(skillName)  || stringIsInStringsVector(skillName, alreadyParsedSkillsNames) ){
                    parsedSkills.clear();
                    std::string message = "ERROR! THE SKILL NAME IS THE SAME THAN A CRCL COMMAND; THIS IS NOT ALLOWED!\n"
                                          "SKILL NAME:  " + skillName;
                    throw std::runtime_error( message );

                    return false;
                }else{
                    auto commandsNode = skillNode["CRCLCommands"];
                        for(auto commandString : commandsNode){
                            std::string auxStr = commandString.as<std::string>();
                            UA_CRCLCommandsUnionDataType commandTemp = stringToCRCLCommandUnion(auxStr);
                            if( commandTemp.switchField != UA_CRCLCOMMANDSUNIONDATATYPESWITCH_NONE ){
                                commands.emplace_back(commandTemp);
                            }else{
                                parsedSkills.clear();
                                return false;
                            }
                        }

                    SAMY::SAMYSkill aux( skillName, commands, UA_NODEID_NUMERIC( 1000, 1000 ), logger );
                    parsedSkills.emplace_back(aux);
                    alreadyParsedSkillsNames.emplace_back(skillName);
                    skillsCounter = skillsCounter +1;
                }
            }
        }
    }


    // ParseComplexSkills
    auto complexSkillsNodes = data["ComplexSkills"];
    if( complexSkillsNodes )
    {
        for(auto complexSkillNode : complexSkillsNodes )
        {
            auto skillNode = complexSkillNode["ComplexSkill"];
            std::vector<UA_CRCLCommandsUnionDataType> commands;
            std::string skillName;
            if(skillNode)
            {
                skillName = skillNode["SkillName"].as<std::string>();
                if( nameIsCRCLCommand(skillName) || stringIsInStringsVector(skillName, alreadyParsedSkillsNames) ){
                    parsedSkills.clear();
                    std::string message = "ERROR! THE SKILL NAME IS THE SAME THAN A CRCL COMMAND; THIS IS NOT ALLOWED!\n"
                                          "SKILL NAME:  " + skillName;
                    throw std::runtime_error( message );
                    return false;
                }else{
                    auto commandsNode = skillNode["CRCLCommands_And_PreviousSkills"];
                        for(auto commandString : commandsNode)
                        {
                            std::string auxStr = commandString.as<std::string>();
                              auto foundSkill = std::find_if(alreadyParsedSkillsNames.begin(), alreadyParsedSkillsNames.end(),
                                                             [auxStr](const std::string& it)->bool{
                                                                        return (auxStr == it) ? true : false;
                                                                });
                          if(foundSkill != alreadyParsedSkillsNames.end()){
                                int index = std::distance(alreadyParsedSkillsNames.begin(), foundSkill);
                                std::vector<UA_CRCLCommandsUnionDataType> commandsAux = parsedSkills[index].getSkillCommands();
                                for(int j=0; j < commandsAux.size(); j++){
                                    commands.emplace_back(commandsAux[j]);
                                }
                            }else{
                                UA_CRCLCommandsUnionDataType commandTemp = stringToCRCLCommandUnion(auxStr);
                                if( commandTemp.switchField != UA_CRCLCOMMANDSUNIONDATATYPESWITCH_NONE ){
                                    commands.emplace_back(commandTemp);
                                }else{
                                    parsedSkills.clear();
                                    return false;
                                }
                            }
                        }
                }
                SAMY::SAMYSkill aux( skillName, commands, UA_NODEID_NUMERIC( 1000, 1000 ), logger );
                parsedSkills.emplace_back(aux);
                alreadyParsedSkillsNames.emplace_back(skillName);
                skillsCounter = skillsCounter +1;
            }
        }
    }
    return true;
}

SkillsParser::SkillsParser(std::shared_ptr<spdlog::logger> logger_):
    logger(logger_)
{}

}

}
