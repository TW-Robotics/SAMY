#ifndef SAMYCORE_H
#define SAMYCORE_H

#include <samycoreInterfaceGenerator.h>
#include <OpcUaServer.h>
#include <yaml_parsers.h>
#include <logging.h>
#include <logging_opcua.h>
#include <vector>
#include <memory>

namespace SAMY {

class SAMYCore{
public:
    SAMYCore(const std::string &serverConfigFilePath );
    std::shared_ptr<spdlog::logger> getLogger();
    void run(bool &running);
private:
    std::shared_ptr<OPCUA::OpcUaServer> server;
 //   UA_Server* server;
    SAMYCoreConfig config;
    std::vector< std::pair<UA_NodeId, std::string> > systemStatusNodesAndNames;
    std::vector<SAMYRobot> robots;
    std::vector<SAMYSkill> skills;
    std::vector<InformationSource> informationSources;
    std::vector< std::tuple< std::string, UA_UInt16, std::string > > dataBaseTypes; /* tuple is (namespace, index, browsename) */
    std::shared_ptr<spdlog::logger> logger;
};

}

#endif
