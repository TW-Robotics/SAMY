#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <string>

struct SAMYCoreConfig{
    std::string appLoggingLevel;
    std::string serverLoggingLevel;
    std::string logsPath;
    int serverPort;
    bool encryption = false;
    bool anonymous = true;
    std::string pathToRobotsConfig;
    std::string pathToSkillsConfig;
    std::string pathToInformationSourcesConfig;
    std::string pathToDataBaseConfig;
    std::string appUri;
    std::string appName;
    std::string certificatesPath;
};

#endif
