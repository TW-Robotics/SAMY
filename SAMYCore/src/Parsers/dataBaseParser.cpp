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

static bool stringIsInTuple(std::string& name, std::vector< std::tuple<std::string, UA_UInt16, std::string> >& existing )
{
    auto found = std::find_if(existing.begin(), existing.end(),
                                   [&](std::tuple<std::string, UA_UInt16, std::string>& it)->bool{
                                              std::string aux = name;
                                              return noCaseSensStringComparison(aux, std::get<2>(it) );
                                      });

    return ( found != existing.end() ) ? true : false;
}

static void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void DataBaseParser::iterateDataTypesArray( const std::string& type,
                                            const YAML::Node& dataBaseNode, bool& found,
                                            const std::string& dataTypeName,
                                            std::vector< std::tuple < std::string, UA_UInt16, std::string > > &typesIndexes,
                                            int elementsCounter ){
    const int32_t dataTypeSize = sizeof(UA_DataType);
    UA_DataType* auxArray = nullptr;
    int arrSize = 0;

    if( type == "UA_TYPES_CRCL" ){
        auxArray = const_cast<UA_DataType*>( UA_TYPES_CRCL );
        arrSize = sizeof(UA_TYPES_CRCL)/dataTypeSize;
    }else if( type == "UA_TYPES" ){
        auxArray = const_cast<UA_DataType*>( UA_TYPES );
        arrSize = sizeof(UA_TYPES)/dataTypeSize;
    }else if( type == "UA_TYPES_DI" ){
        auxArray = const_cast<UA_DataType*>( UA_TYPES_DI );
        arrSize = sizeof(UA_TYPES_DI)/dataTypeSize;
    }else if( type == "UA_TYPES_ROBOTICS" ){
        auxArray = const_cast<UA_DataType*>( UA_TYPES_ROBOTICS );
        arrSize = sizeof(UA_TYPES_ROBOTICS)/dataTypeSize;
    }else{
        std::string msg = type + " is not a valid DataType array.";
        throw std::runtime_error(msg);
    }

    for( int i = 0; i < arrSize; i++)
    {
        UA_DataType dataType = *(auxArray + i);
        if( dataTypeName == std::string{ dataType.typeName } ){
            if( !dataBaseNode["name"] && !dataBaseNode["Name"]  ){
                found = true;
                std::string elementName = dataTypeName + std::to_string(elementsCounter);
                logger->warn("AN ELEMENT IN THE DATABASE FILE WITH TYPE {} DOES NOT HAVE A NAME."
                             " A NODE WITH A DEFAULT THE DEFAULT NAME {} WAS ADDED.", dataTypeName, elementName );
                typesIndexes.emplace_back( std::tuple<std::string,
                                           UA_UInt16, std::string>( type, dataType.typeIndex,  elementName ) );
                break;
            }

            std::string browseName = "";

            if( dataBaseNode["name"] )
                 browseName = dataBaseNode["name"].as<std::string>();
            else
                 browseName = dataBaseNode["Name"].as<std::string>();

            if( stringIsInTuple( browseName, typesIndexes ) ){
                found = true;
                logger->warn("AN ELEMENT IN THE DATABASE FILE HAS A NAME THAT WAS ALREADY USED (NO CASE SENSITIVE COMPARISON), "
                              "AND THIS NAME IS USED AS BROWSE NAME: {}. SKIPPING THE ELEMENT.", browseName );
                break;
            }
            typesIndexes.emplace_back( std::tuple<std::string,
                                       UA_UInt16, std::string>( type, dataType.typeIndex,  browseName ) );
            found = true;
            break;
        }
    }
}

bool DataBaseParser::parseDataBase(const std::string& filepath,
                                   std::vector< std::tuple< std::string, UA_UInt16, std::string > > &typesIndexes )
{
    std::ifstream stream(filepath);
    std::stringstream strStream;
    strStream << stream.rdbuf();

    YAML::Node data = YAML::Load(strStream.str());
    if(!data["DataBase"])
        return false;

    int elementsCounter = 0;
    auto dataBaseNodes = data["DataBase"];
    if( dataBaseNodes )
    {
        for(YAML::Node dataBaseNode : dataBaseNodes )
        {

            std::vector<std::string> splitTag;
            tokenize( dataBaseNode.Tag(), ':', splitTag );
            std::string aux = splitTag[splitTag.size()-1];
            splitTag.clear();
            tokenize( aux, '.', splitTag );
            std::string dataTypeName = splitTag[1];

            bool found = false;

            if( !found )
                iterateDataTypesArray("UA_TYPES_CRCL", dataBaseNode, found, dataTypeName, typesIndexes, elementsCounter );

            if( !found )
                iterateDataTypesArray("UA_TYPES", dataBaseNode, found, dataTypeName, typesIndexes, elementsCounter );

            if( !found )
                iterateDataTypesArray("UA_TYPES_DI", dataBaseNode, found, dataTypeName, typesIndexes, elementsCounter );

            if( !found )
                iterateDataTypesArray("UA_TYPES_ROBOTICS", dataBaseNode, found, dataTypeName, typesIndexes, elementsCounter );

            if( !found )
                logger->error("AN ELEMENT IN THE DATABASE FILE WITH TYPE {} COULD NOT BE FOUND AND THEREFORE "
                              "A NODE FOR IT COULD NOT BE ADDED", dataTypeName );

            elementsCounter++;
        }
    }

    return true;
}

DataBaseParser::DataBaseParser(std::shared_ptr<spdlog::logger> logger_):
    logger(logger_)
{}


}
}
