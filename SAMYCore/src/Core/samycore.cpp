#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include <samycore.h>

namespace SAMY {

    void SAMYCore::run( bool& running ){
        while ( running ) {
            server->iterate();
            std::this_thread::yield();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    SAMYCore::SAMYCore( const std::string& serverConfigFilePath )
    {
        logger = SAMY::Logging::LoggerFactory::createLogger("SAMYCore",
                                                           config.appLoggingLevel,
                                                           config.logsPath);

        Parsers::SAMYCoreConfigParser parserConfig{logger};
        parserConfig.parseSAMYCoreConfig( serverConfigFilePath, config );

        Parsers::DataBaseParser parserDataBase{logger};
        parserDataBase.parseDataBase( config.pathToDataBaseConfig, dataBaseTypes );

        Parsers::SkillsParser skillsParser{ logger };
        skillsParser.parseSkills( config.pathToSkillsConfig, skills );

        Parsers::RobotsParser robotsParser{ logger };
        robotsParser.parseRobots( config.pathToRobotsConfig, skills, robots );

        Parsers::InformationSourcesParser infoParser{ logger };
        infoParser.parseInformationSources( config.pathToInformationSourcesConfig, informationSources );

         std::stringstream msg;
         msg <<"SKILLS SIZE: "<< skills.size() << "  ROBOTS SIZE: "<<robots.size()<<"   INFO SOURCES SIZE: "
            << informationSources.size() <<  "  ELEMENTS IN DATABASE: " << dataBaseTypes.size() << std::endl << std::endl;
         logger->info(msg.str());

         server = std::make_shared<SAMY::OPCUA::OpcUaServer>( config, logger );

        LockedServer ls = server->getLocked();

        SAMY::SAMYCoreInterfaceGenerator generator{logger};
        generator.generateSAMYCoreInterface( ls.get(), &robots, &skills, &informationSources, &dataBaseTypes );

        systemStatusNodesAndNames = generator.getSystemStatusNodesAndNames();

         std::stringstream msg2;
        msg2 <<"NUMBER OF RELEVANT NODES FOR DESCRIBING SYSTEM STATUS: " << systemStatusNodesAndNames.size() << std::endl << std::endl;
        logger->info(msg2.str());

        server->init();
    }
}
