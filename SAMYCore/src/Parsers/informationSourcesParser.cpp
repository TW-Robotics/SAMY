#include <yaml_parsers.h>
//#include <crcl_nodeids.h>
#include <namespace_crcl_generated.h>

namespace SAMY {
namespace Parsers {

static bool noCaseSensStringComparison(std::string & str1, const std::string &strExt)
{
    std::string str2 = strExt;
    return ((str1.size() == str2.size()) && std::equal(str1.begin(), str1.end(), str2.begin(),
            [](char & c1, char & c2){return (c1 == c2 || std::toupper(c1) == std::toupper(c2));}));
}

/* We check that the given data type name is either a standard data type or a custom defined CRCL data type */
UA_NodeId nameToDataTypeNodeId(const std::string& name){
    for( int i=0; i < sizeof(UA_TYPES)/sizeof(UA_TYPES[0]); i++){
        std::string aux = name;
        if( noCaseSensStringComparison( aux, std::string{UA_TYPES[i].typeName} ) )
            return UA_TYPES[i].typeId;
    }
    for( int i=0; i < sizeof(UA_TYPES_CRCL)/sizeof(UA_TYPES_CRCL[0]); i++){
        std::string aux = name;
        if( noCaseSensStringComparison( aux, std::string{UA_TYPES_CRCL[i].typeName} ) )
            return UA_TYPES_CRCL[i].typeId;
    }
    return UA_NODEID_NUMERIC(9999, 9999);
}

static bool stringIsInStringsVector(std::string& name, std::vector<std::string>& existing ){
    auto found = std::find_if(existing.begin(), existing.end(),
                                   [&](std::string& it)->bool{
                                              std::string aux = name;
                                              return noCaseSensStringComparison(aux, it);
                                      });

    return ( found != existing.end() ) ? true : false;
}


std::vector<InformationSource> InformationSourcesParser::parseInformationSourcesDescriptions( const YAML::Node& data ){

    std::vector<InformationSource> parsedSources;

    std::vector<std::string> alreadyParsedInformationSourcesNames;

    if(!data["InformationSourcesDescriptions"])
        return parsedSources;

    auto informationSourcesDescriptions = data["InformationSourcesDescriptions"];

    if( informationSourcesDescriptions )
    {
        for(auto informationSourceDescript : informationSourcesDescriptions )
        {
            auto InformationSourceNode = informationSourceDescript["InformationSourceDescription"];
            std::vector<UA_NodeId> dataTypes;
            std::string InformationSourceName;
            if(InformationSourceNode)
            {
                InformationSourceName = InformationSourceNode["InformationSourceName"].as<std::string>();

                if( stringIsInStringsVector(InformationSourceName, alreadyParsedInformationSourcesNames) ){
                    parsedSources.clear();
                    std::string message = "ERROR: THE INFORMATIONSOURCE NAME " + InformationSourceName +
                            " IS THE SAME THAN ANOTHER INFORMATIONSOURCE; THIS IS NOT ALLOWED!";
                    throw std::runtime_error( message );
                }else{
                    auto dataTypesNodes = InformationSourceNode["DataTypes"];
                        for(auto dataTypeNode : dataTypesNodes){
                            std::string auxStr = dataTypeNode.as<std::string>();
                            UA_NodeId nodeTemp = nameToDataTypeNodeId(auxStr);
                            if( nodeTemp.namespaceIndex != 9999 ){
                                dataTypes.emplace_back(nodeTemp);
                            }else{
                                parsedSources.clear();
                                std::string message = "ERROR: THE PROVIDED DATATYPE " + auxStr +
                                        " IS NOT AN EXISTING DATA TYPE OR PREVIOUSLY DEFINED INFORMATION SOURCE;THIS IS NOT ALLOWED!";
                                throw std::runtime_error( message );
                            }
                        }
                    SAMY::InformationSource aux( InformationSourceName, dataTypes);
                    parsedSources.emplace_back(aux);
                    alreadyParsedInformationSourcesNames.emplace_back(InformationSourceName);
                }
            }
        }
    }


}

bool InformationSourcesParser::parseInformationSources( const std::string& filepath,
                                                        std::vector<InformationSource>& parsedSources ){

    if( filepath.size() == 0 ) /* In case we do not want any information source */
        return true;

    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();
    YAML::Node data = YAML::Load(strStream.str());

    std::vector<InformationSource> infoSourcesDescriptions = std::move( parseInformationSourcesDescriptions(data) );
    std::vector<std::string> alreadyParsedInformationSourcesNames;

    for( InformationSource& infoSourceDesc : infoSourcesDescriptions ){
        alreadyParsedInformationSourcesNames.emplace_back( infoSourceDesc.getName() );
    }

    if(!data["InformationSources"])
        return true;

    // ParseComplexInformationSources
    auto complexInformationSourcesNodes = data["InformationSources"];
    if( complexInformationSourcesNodes )
    {
        for(auto complexInformationSourceNode : complexInformationSourcesNodes )
        {
            auto InformationSourceNode = complexInformationSourceNode["InformationSource"];
            std::vector<UA_NodeId> dataTypes;
            std::string InformationSourceName;
            if(InformationSourceNode)
            {
                InformationSourceName = InformationSourceNode["InformationSourceName"].as<std::string>();
                if( stringIsInStringsVector(InformationSourceName, alreadyParsedInformationSourcesNames) ){
                    parsedSources.clear();
                    std::string message = "ERROR: THE INFORMATIONSOURCE NAME " + InformationSourceName +
                            " IS THE SAME THAN ANOTHER INFORMATIONSOURCE; THIS IS NOT ALLOWED!";
                    throw std::runtime_error( message );
                    return false;
                }else{
                    auto dataTypesNodes = InformationSourceNode["DataTypes"];
                        for(auto dataTypeNode : dataTypesNodes){
                            std::string auxStr = dataTypeNode.as<std::string>();

                              auto foundInformationSource = std::find_if(alreadyParsedInformationSourcesNames.begin(),
                                                                         alreadyParsedInformationSourcesNames.end(),
                                                             [auxStr](const std::string& it)->bool{
                                                                        return (auxStr == it) ? true : false;
                                                                });
                          if(foundInformationSource != alreadyParsedInformationSourcesNames.end())
                          {
                                int index = std::distance(alreadyParsedInformationSourcesNames.begin(), foundInformationSource);
                                std::vector<UA_NodeId> dataTypesAux;
                                if( index < infoSourcesDescriptions.size() )
                                     dataTypesAux = infoSourcesDescriptions[index].getDataTypesNodeIds();
                                else
                                    dataTypesAux = parsedSources[index-infoSourcesDescriptions.size()].getDataTypesNodeIds();

                                for(int j=0; j < dataTypesAux.size(); j++){
                                    dataTypes.emplace_back(dataTypesAux[j]);
                                }
                            }else{
                                UA_NodeId dataTypeNodeTemp = nameToDataTypeNodeId(auxStr);
                                if( dataTypeNodeTemp.namespaceIndex != 9999 ){
                                    dataTypes.emplace_back(dataTypeNodeTemp);
                                }else{
                                    parsedSources.clear();
                                    std::string message = "ERROR: THE PROVIDED DATATYPE " + auxStr +
                                            " IS NOT AN EXISTING DATA TYPE OR PREVIOUSLY DEFINED INFORMATION SOURCE;THIS IS NOT ALLOWED!";
                                    throw std::runtime_error( message );
                                    return false;
                                }
                            }
                        }
                }
                SAMY::InformationSource aux( InformationSourceName, dataTypes );
                parsedSources.emplace_back(aux);
                alreadyParsedInformationSourcesNames.emplace_back(InformationSourceName);
            }
        }
    }
    return true;
}

InformationSourcesParser::InformationSourcesParser(std::shared_ptr<spdlog::logger> logger_):
    logger(logger_)
{}

}
}
