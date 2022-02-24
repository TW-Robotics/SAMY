#include <yaml_parsers.h>

namespace SAMY {

bool Parsers::SAMYCoreConfigParser::parseSAMYCoreConfig(const std::string& filepath, SAMYCoreConfig &config ){
    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    YAML::Node data = YAML::Load(strStream.str());
    if(!data["SAMYCoreConfig"])
        return false;

    auto serverConfig = data["SAMYCoreConfig"];
    if( serverConfig )
    {

        config.pathToSkillsConfig = serverConfig["AppURI"].as<std::string>();
        config.pathToRobotsConfig = serverConfig["AppName"].as<std::string>();

        auto server = serverConfig["Server"];

        if(!server) return false;

        config.serverPort = server["Port"].as<int>();
        config.certificatesPath = server["CertificatesPath"].as<std::string>();
        config.encryption = server["Encryption"].as<bool>();
        config.anonymous = server["Anonymous"].as<bool>();

        auto logging = serverConfig["Logging"];

        if(!logging) return false;

        auto level = logging["Level"];

        if(!level) return false;

        config.appLoggingLevel = level["App"].as<std::string>();
        config.serverLoggingLevel = level["OPCUA"].as<std::string>();
        config.logsPath = logging["Path"].as<std::string>();

        auto configFiles = serverConfig["ConfigFiles"];
        config.pathToSkillsConfig = configFiles["SkillsFile"].as<std::string>();
        config.pathToRobotsConfig = configFiles["RobotsFile"].as<std::string>();
        config.pathToInformationSourcesConfig = configFiles["InformationSourcesFile"].as<std::string>();
        config.pathToDataBaseConfig = configFiles["DataBaseFile"].as<std::string>();

        return true;
    }
    return false;
}

Parsers::SAMYCoreConfigParser::SAMYCoreConfigParser( std::shared_ptr<spdlog::logger> logger_):
    logger(logger_)
{}


}
