#include <yaml_parsers.h>

namespace SAMY {
namespace Parsers {

/* To upper should not be called with char, REVIEW! */
static bool noCaseSensStringComparison(std::string & str1, const std::string &strExt)
{
    std::string str2 = strExt;
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(),
            [](char & c1, char & c2){return (c1 == c2 || std::toupper(c1) == std::toupper(c2));}));
}

static bool stringIsInStringsVector(std::string& name, std::vector<std::string>& existing )
{
    auto found = std::find_if(existing.begin(), existing.end(),
                                   [&](std::string& it)->bool{
                                              std::string aux = name;
                                              return noCaseSensStringComparison(aux, it);
                                      });

    return ( found != existing.end() ) ? true : false;
}

bool skillExists( std::string& name, std::vector<SAMYSkill>& skills){
    auto found = std::find_if(skills.begin(), skills.end(),
                                   [&](SAMYSkill& it)->bool{
                                              std::string aux = it.getSkillName();
                                              return noCaseSensStringComparison(aux, name);
                                      });

    return ( found != skills.end() ) ? true : false;
}

int findSkillIndexInSkillsVectorBySkillName( std::string& name, std::vector<SAMYSkill> skills){
    auto found = std::find_if(skills.begin(), skills.end(),
                                   [&](SAMYSkill& it)->bool{
                                              std::string aux = it.getSkillName();
                                              return noCaseSensStringComparison(aux, name);
                                      });
    return (found != skills.end() ) ? ( found - skills.begin() ) : -1;
}

bool RobotsParser::parseRobots(const std::string& filepath, std::vector<SAMYSkill> &parsedSkills, std::vector<SAMYRobot> &parsedRobots)
{
    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    std::vector<std::string> alreadyParsedRobotNames;
    std::vector<std::string> alreadyParsedRobotAddresses;
    std::vector<std::string> alreadyParsedRobotIDs;

    YAML::Node data = YAML::Load(strStream.str());
    if(!data["Robots"])
        return false;

    auto robotsNodes = data["Robots"];
    if( robotsNodes )
    {
        for(auto robotNode : robotsNodes )
        {
            auto node = robotNode["Robot"];
            if(node)
            {
                SAMYRobot robotAux{ logger };
                std::string auxName = node["Name"].as<std::string>();
                std::string auxID = node["ID"].as<std::string>();
                std::string auxAddress = node["Address"].as<std::string>();
                std::vector<std::string> alreadyRobotParsedSkills;
                std::vector<SAMYSkill> parsedRobotSkills;

                if( stringIsInStringsVector(auxName, alreadyParsedRobotNames) ||
                        stringIsInStringsVector(auxID, alreadyParsedRobotIDs) ||
                            stringIsInStringsVector(auxAddress, alreadyParsedRobotAddresses) ){
                    parsedRobots.clear();
                    std::string message = "ERROR! THE ROBOT NAME OR ID OR ADDRESS IS THE SAME THAN A PREVIOUSLY DEFINED ROBOT. THIS IS NOT ALLOWED!\nROBOT NAME:  "
                                          + auxName + "     ID: "  + auxID + "     ADDRESS: " + auxAddress;
                    throw std::runtime_error( message );
                    return false;
                }else{
                    auto robotSkillsNode = node["Skills"];
                        for(auto robotSkillString : robotSkillsNode){
                            std::string auxSkillString = robotSkillString.as<std::string>();
                            if(skillExists(auxSkillString, parsedSkills)
                               && !stringIsInStringsVector(auxSkillString, alreadyRobotParsedSkills)){
                                    int skillIndex = findSkillIndexInSkillsVectorBySkillName(auxSkillString, parsedSkills);
                                    parsedRobotSkills.emplace_back(parsedSkills[skillIndex]);
                                    alreadyRobotParsedSkills.emplace_back(auxSkillString);
                            }else{
                                parsedRobots.clear();
                                std::string message = "ERROR! THE GIVEN SKILL FOR THE ROBOT EITHER DOES NOT EXIST OR WAS ALREADY DEFINED "
                                                      "FOR THIS ROBOT. THIS IS NOT ALLOWED!\nROBOT NAME:  "
                                                      + auxName + "     ROBOT SKILL: " + auxSkillString;
                                throw std::runtime_error( message );
                                return false;
                            }
                        }
                }
                robotAux.name = UA_STRING_ALLOC(const_cast<char*>(auxName.c_str()));
               // robotAux.requested_skill = 0;
                //robotAux.SAMYRobotVariableNodeId = UA_NODEID_STRING(2, const_cast<char*>(auxName.c_str()));
                robotAux.robotSkills = parsedRobotSkills;
                robotAux.address = auxAddress;

                parsedRobots.emplace_back( std::move( robotAux ) );

                alreadyParsedRobotNames.emplace_back(auxName);
                alreadyParsedRobotIDs.emplace_back(auxID);
                alreadyParsedRobotAddresses.emplace_back(auxAddress);
            }
        }
    }
    return true;
}

RobotsParser::RobotsParser(std::shared_ptr<spdlog::logger> logger_):
    logger(logger_)
{}


}
}
