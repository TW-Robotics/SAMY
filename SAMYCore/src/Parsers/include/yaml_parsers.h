#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <iostream>
#include <fstream>
#include <tuple>
#include "string.h"
//#include "crcl_nodeids.h"
#include <namespace_crcl_generated.h>
#include "types_crcl_generated.h"
#include <samyskill.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>
#include <vector>
#include "SAMYRobot.h"
#include "informationSource.h"
#include <samycoreConfig.h>

namespace SAMY {

namespace Parsers {

    class SkillsParser{
    public:
        SkillsParser( std::shared_ptr<spdlog::logger> logger_ );
        bool parseSkills(const std::string& filepath, std::vector<SAMYSkill>& parsedSkills );
    private:
        std::shared_ptr<spdlog::logger> logger;
    };

    class RobotsParser{
    public:
        RobotsParser( std::shared_ptr<spdlog::logger> logger_ );
        bool parseRobots(const std::string& filepath, std::vector<SAMYSkill> &parsedSkills, std::vector<SAMYRobot>& parsedRobots);
    private:
        std::shared_ptr<spdlog::logger> logger;

    };


    class InformationSourcesParser{
    public:
        InformationSourcesParser( std::shared_ptr<spdlog::logger> logger_ );
        bool parseInformationSources( const std::string& filepath, std::vector<InformationSource>& parsedSources );
    private:
        std::vector<InformationSource> parseInformationSourcesDescriptions(const YAML::Node &data );
        std::shared_ptr<spdlog::logger> logger;

    };


    class SAMYCoreConfigParser{
    public:
        SAMYCoreConfigParser( std::shared_ptr<spdlog::logger> logger_ );
        bool parseSAMYCoreConfig(const std::string& filepath, SAMYCoreConfig& config );
    private:
        std::shared_ptr<spdlog::logger> logger;
    };

    class DataBaseParser{
    public:
        DataBaseParser( std::shared_ptr<spdlog::logger> logger_ );
        bool parseDataBase(const std::string& filepath, std::vector<std::tuple<std::string, UA_UInt16, std::string> > &typesIndexes );
        void iterateDataTypesArray(const std::string& type,
                                    const YAML::Node& dataBaseNode, bool& found,
                                    const std::string& dataTypeName,
                                    std::vector< std::tuple < std::string, UA_UInt16, std::string > > &typesIndexes, int elementsCounter);
    private:
        std::shared_ptr<spdlog::logger> logger;
    };


}

}

#endif /*YAML_PARSER_H*/
