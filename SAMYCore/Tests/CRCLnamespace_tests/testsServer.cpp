//#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>


#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
/* Files namespace_foo_flt_generated.h and namespace_foo_flt_generated.c are created from FooFlt.NodeSet2.xml in the
 * /src_generated directory by CMake */

#include <thread>
#include <signal.h>
#include <samyskill.h>
#include <iostream>
#include <chrono>
#include <open62541/plugin/log_stdout.h>
#include <yaml_parsers.h>
#include "SAMYRobot.h"
#include <samycoreInterfaceGenerator.h>
#include <samycoreConfig.h>
#include <OpcUaServer.h>
#include <logging.h>
#include <logging_opcua.h>


/*
TEST_CASE("Test main", "[TestTag]"){

    UA_Boolean running = true;

        UA_Server* server = UA_Server_new();
        UA_ServerConfig *config = UA_Server_getConfig(server);
        UA_ServerConfig_setMinimal(config, 4567, NULL);

        SAMY::Parsers::SkillsParser skillsParser;
        REQUIRE( 1 ==  skillsParser.parse( "../Skills.yaml" ) );
        std::vector<SAMY::SAMYSkill>* skills = skillsParser.getParsedSkills();

        SAMY::Parsers::RobotsConfigurationParser robotsParser;
        REQUIRE( 1 == robotsParser.parse( "../RobotsConfiguration.yaml", *skills ));
        std::vector<SAMY::SAMYRobot>* robots = robotsParser.getParsedRobots();

        UA_StatusCode retVal = SAMY::ServerGenerator::generateSAMYCoreServer( server, robots, skills );
        REQUIRE( retVal == 0 );

        std::thread SAMYCoreOPCUAInterface(UA_Server_run, server, &running);
        SAMYCoreOPCUAInterface.detach();

        std::this_thread::sleep_for(std::chrono::milliseconds( 3000 ));
        running = false;

        UA_Server_delete( server );

        std::cout << "END TEST 1 ---------------------------------------------------------------------------" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds( 1000 ));

        REQUIRE( retVal == 0);
}

TEST_CASE("Server for testing nodes addition", "[TestTag]"){
        UA_Boolean running = true;

        UA_Server* server = UA_Server_new();
        UA_ServerConfig *config = UA_Server_getConfig(server);
        UA_ServerConfig_setMinimal(config, 4567, NULL);

        REQUIRE( 0 == namespace_crcl_generated( server ) );

        std::vector<UA_NodeId> typesNodesVector;
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE].typeId );
        typesNodesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE].typeId );

        std::vector<UA_NodeId> outputNodesVector( typesNodesVector.size(), UA_NODEID_NULL );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        UA_VariableAttributes vattr = UA_VariableAttributes_default;
        vattr.description = UA_LOCALIZEDTEXT("", "testNode");
        vattr.displayName = UA_LOCALIZEDTEXT("", "testNode");
        vattr.valueRank = UA_VALUERANK_SCALAR;
        vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

        for(int i = 0; i < typesNodesVector.size(); i++ ){

        UA_NodeId_init( &vattr.dataType );
                vattr.dataType = typesNodesVector[i];

                    retVal |= UA_Server_addVariableNode( server,
                                                         UA_NODEID_NUMERIC(1, 0),
                                                         UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                         UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                         UA_QUALIFIEDNAME(0, "testNode" ),
                                                         UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                         vattr, NULL, &(outputNodesVector[i])
                                                         );
                    REQUIRE( retVal == 0 );
                }

        std::thread SAMYCoreOPCUAInterface(UA_Server_run, server, &running);
        SAMYCoreOPCUAInterface.detach();

        std::this_thread::sleep_for(std::chrono::milliseconds( 3000 ));
        SAMYCoreOPCUAInterface.detach();

        running = false;

        UA_Server_delete( server );

        std::cout << "END TEST 2 ---------------------------------------------------------------------------" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds( 1000 ));

        REQUIRE( retVal == 0);
}
*/


TEST_CASE("Server testing", "[ServerAutoRead]"){

    std::vector<UA_DataType> typesVector;
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE] );

    UA_Server* server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 4567, NULL);

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    REQUIRE( 0 == namespace_crcl_generated( server ) );

    SECTION("UA_InitCanonDataType"){

            UA_LocalizedText_init( &vattr.description );
            UA_LocalizedText_init( &vattr.displayName );
            vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[0].typeName )  );
            vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[0].typeName ) );
            UA_NodeId_init( &vattr.dataType );
            vattr.dataType = typesVector[0].typeId;

            UA_StatusCode retVal = UA_STATUSCODE_GOOD;

            retVal |= UA_Server_addVariableNode( server,
                                                 UA_NODEID_NUMERIC(1, 1000),
                                                 UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                 UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[0].typeName ) ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                 vattr, NULL, NULL
                                                 );

            REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_InitCanonDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_InitCanonDataType" );
        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE] );

        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1000), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);
        UA_InitCanonDataType* commandAux = (UA_InitCanonDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EndCanonDataType"){
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[1].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[1].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[1].typeId;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1001),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[1].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_EndCanonDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1001);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EndCanonDataType" );
        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE] );

        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1001), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1001), &var);
        UA_EndCanonDataType* commandAux = (UA_EndCanonDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MessageDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[2].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[2].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[2].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1002),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[2].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_MessageDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1002);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MessageDataType" );

        command.message = UA_STRING( "TEST MESSAGE!" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1002), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1002), &var);
        UA_MessageDataType* commandAux = (UA_MessageDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveToDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[3].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[3].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[3].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1003),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[4].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_MoveToDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1003);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveToDataType" );

        command.endPosition.id = 987;
        command.endPosition.name = UA_STRING( "POSITIONNAME" );
        command.endPosition.point.id = 87;
        command.endPosition.point.name = UA_STRING( "POINT NAME" );
        command.endPosition.point.x = 0.987;
        command.endPosition.point.y = 6.543;
        command.endPosition.point.z = 1.467;
        command.endPosition.xAxis.id = 8711;
        command.endPosition.xAxis.name = UA_STRING( "xVector NAME" );
        command.endPosition.xAxis.i = 0.987;
        command.endPosition.xAxis.j = 6.543;
        command.endPosition.xAxis.k = 1.467;
        command.endPosition.zAxis.id = 8764;
        command.endPosition.zAxis.name = UA_STRING( "zVector NAME" );
        command.endPosition.zAxis.i = 5.987;
        command.endPosition.zAxis.j = 8.543;
        command.endPosition.zAxis.k = 121.467;
        command.moveStraight = UA_TRUE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1003), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1003), &var);
        UA_MoveToDataType* commandAux = (UA_MoveToDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveScrewDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[4].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[4].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[4].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1004),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[4].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_MoveScrewDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1004);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveScrewDataType" );

        command.axialDistanceFree = 6.543;
        command.axialDistanceScrew = 87.123;
        command.axisPoint.id = 87;
        command.axisPoint.name = UA_STRING( "POINT NAME" );
        command.axisPoint.x = 0.987;
        command.axisPoint.y = 6.543;
        command.axisPoint.z = 1.467;
        command.turn = 5.123;

        UA_CRCL_PoseDataType pose1;
        pose1.id = 743;
        pose1.name = UA_STRING( "POSE1" );
        pose1.point.id = 87;
        pose1.point.name = UA_STRING( "POINT NAME" );
        pose1.point.x = 0.987;
        pose1.point.y = 6.543;
        pose1.point.z = 1.467;
        pose1.xAxis.id = 8711;
        pose1.xAxis.name = UA_STRING( "xVector NAME" );
        pose1.xAxis.i = 0.987;
        pose1.xAxis.j = 6.543;
        pose1.xAxis.k = 1.467;
        pose1.zAxis.id = 8764;
        pose1.zAxis.name = UA_STRING( "zVector NAME" );
        pose1.zAxis.i = 5.987;
        pose1.zAxis.j = 8.543;
        pose1.zAxis.k = 121.467;

        command.startPosition = pose1;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE] );

        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1004), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1004), &var);
        UA_MoveScrewDataType* commandAux = (UA_MoveScrewDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveThroughToDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[5].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[5].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[5].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1005),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[5].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_MoveThroughToDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1005);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveThroughToDataType" );

        UA_CRCL_PoseDataType pose1;
        pose1.id = 743;
        pose1.name = UA_STRING( "POSE1" );
        pose1.point.id = 87;
        pose1.point.name = UA_STRING( "POINT NAME" );
        pose1.point.x = 0.987;
        pose1.point.y = 6.543;
        pose1.point.z = 1.467;
        pose1.xAxis.id = 8711;
        pose1.xAxis.name = UA_STRING( "xVector NAME" );
        pose1.xAxis.i = 0.987;
        pose1.xAxis.j = 6.543;
        pose1.xAxis.k = 1.467;
        pose1.zAxis.id = 8764;
        pose1.zAxis.name = UA_STRING( "zVector NAME" );
        pose1.zAxis.i = 5.987;
        pose1.zAxis.j = 8.543;
        pose1.zAxis.k = 121.467;

        UA_CRCL_PoseDataType pose2;
        pose2.id = 743;
        pose2.name = UA_STRING( "POSE2" );
        pose2.point.id = 87;
        pose2.point.name = UA_STRING( "POINT NAME" );
        pose2.point.x = 0.987;
        pose2.point.y = 6.543;
        pose2.point.z = 1.467;
        pose2.xAxis.id = 8711;
        pose2.xAxis.name = UA_STRING( "xVector NAME" );
        pose2.xAxis.i = 0.987;
        pose2.xAxis.j = 6.543;
        pose2.xAxis.k = 1.467;
        pose2.zAxis.id = 8764;
        pose2.zAxis.name = UA_STRING( "zVector NAME" );
        pose2.zAxis.i = 5.987;
        pose2.zAxis.j = 8.543;
        pose2.zAxis.k = 121.467;

        UA_CRCL_PoseDataType *waypoint = (UA_CRCL_PoseDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_POSEDATATYPE]);

        waypoint[0] = pose1;
        waypoint[1] = pose2;

        command.moveStraight = UA_TRUE;
        command.waypointSize = 2;
        command.waypoint = waypoint;
        command.numPositions = 2;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1005), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1005), &var);
        UA_MoveThroughToDataType* commandAux = (UA_MoveThroughToDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DwellDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[6].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[6].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[6].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1006),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[6].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_DwellDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1006);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DwellDataType" );

        command.dwellTime = 101.101;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1006), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1006), &var);
        UA_DwellDataType* commandAux = (UA_DwellDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ActuateJointsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[7].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[7].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[7].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1007),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[7].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_ActuateJointsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1007);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ActuateJointsDataType" );

        UA_CRCL_ActuateJointDataType act1;
        act1.id = 134;
        act1.name = UA_STRING( "actuate joint 1" );
        act1.jointNumber = 2;
        act1.jointPosition = 54.74;
        act1.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTSPEEDACCEL;
        act1.jointDetails.fields.jointSpeedAccel.id = 101;
        act1.jointDetails.fields.jointSpeedAccel.name = UA_STRING( "Actuate Joint jointSpeedAccel" );
        act1.jointDetails.fields.jointSpeedAccel.jointAccel = 10.101;
        act1.jointDetails.fields.jointSpeedAccel.jointSpeed = 210.101;

        UA_CRCL_ActuateJointDataType act2;
        act2.id = 6341;
        act2.name = UA_STRING( "actuate joint 2" );
        act2.jointNumber = 5;
        act2.jointPosition = 98.314;
        act2.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTFORCETORQUE;
        act2.jointDetails.fields.jointForceTorque.id = 101;
        act2.jointDetails.fields.jointForceTorque.name = UA_STRING( "Actuate Joint jointForceTorque" );
        act2.jointDetails.fields.jointForceTorque.changeRate = 10.101;
        act2.jointDetails.fields.jointForceTorque.setting = 210.101;

        UA_CRCL_ActuateJointDataType *actuateJoints = (UA_CRCL_ActuateJointDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_ACTUATEJOINTDATATYPE]);

        actuateJoints[0] = act1;
        actuateJoints[1] = act2;

        UA_CRCL_JointPositionsTolerancesDataType tols;
        tols.id = 9532;
        tols.name = UA_STRING( "JointPosition tolerances test" );

        UA_CRCL_JointPositionToleranceSettingDataType tol1;
        tol1.id = 6363;
        tol1.name = UA_STRING( "JointPositionTolerance 1" );
        tol1.jointNumber = 1;
        tol1.jointPositionTolerance = 9.876;

        UA_CRCL_JointPositionToleranceSettingDataType tol2;
        tol2.id = 15638;
        tol2.name = UA_STRING( "JointPositionTolerance 2" );
        tol2.jointNumber = 4;
        tol2.jointPositionTolerance = 5.6272;

        UA_CRCL_JointPositionToleranceSettingDataType *settings = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);
        settings[0] = tol1;
        settings[1] = tol2;

        tols.setting = settings;
        tols.settingSize = 2;

        command.actuateJointSize = 2;
        command.actuateJoint = actuateJoints;
        command.jointTolerances = tols;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1007), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1007), &var);
        UA_ActuateJointsDataType* commandAux = (UA_ActuateJointsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ConfigureJointReportsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[8].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[8].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[8].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1008),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[8].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_ConfigureJointReportsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1008);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ConfigureJointReportsDataType" );

        UA_CRCL_ConfigureJointReportDataType conf1;
        conf1.id = 9213;
        conf1.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 1" );
        conf1.jointNumber = 2;
        conf1.reportPosition = UA_TRUE;
        conf1.reportTorqueOrForce = UA_FALSE;
        conf1.reportVelocity = UA_TRUE;

        UA_CRCL_ConfigureJointReportDataType conf2;
        conf2.id = 9213;
        conf2.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 2" );
        conf2.jointNumber = 3;
        conf2.reportPosition = UA_TRUE;
        conf2.reportTorqueOrForce = UA_TRUE;
        conf2.reportVelocity = UA_TRUE;

        UA_CRCL_ConfigureJointReportDataType *confReports = (UA_CRCL_ConfigureJointReportDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_CONFIGUREJOINTREPORTDATATYPE]);

        confReports[0] = conf1;
        confReports[1] = conf2;

        command.configureJointReport = confReports;
        command.configureJointReportSize = 2;

        command.resetAll = UA_FALSE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1008), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1008), &var);
        UA_ConfigureJointReportsDataType* commandAux = (UA_ConfigureJointReportsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetDefaultJointPositionsTolerancesDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[9].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[9].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[9].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1009),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[9].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetDefaultJointPositionsTolerancesDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1009);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetDefaultJointPositionsTolerancesDataType" );

        UA_CRCL_JointPositionToleranceSettingDataType tolSet1;
        tolSet1.id = 663;
        tolSet1.name = UA_STRING( "JointPositionTolerance 1" );
        tolSet1.jointNumber = 43;
        tolSet1.jointPositionTolerance = 411.12;

        UA_CRCL_JointPositionToleranceSettingDataType tolSet2;
        tolSet2.id = 7564;
        tolSet2.name = UA_STRING( "JointPositionTolerance 2" );
        tolSet2.jointNumber = 21;
        tolSet2.jointPositionTolerance = 354.236;

        UA_CRCL_JointPositionToleranceSettingDataType *tolSettings = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);

        tolSettings[0] = tolSet1;
        tolSettings[1] = tolSet2;

        UA_CRCL_JointPositionsTolerancesDataType tol;
        tol.id = 534;
        tol.name = UA_STRING( "JOINT TOLERANCES" );
        tol.setting = tolSettings;
        tol.settingSize = 2;

        command.jointTolerances = tol;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1009), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1009), &var);
        UA_SetDefaultJointPositionsTolerancesDataType* commandAux = (UA_SetDefaultJointPositionsTolerancesDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_GetStatusDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[10].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[10].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[10].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1010),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[10].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_GetStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1010);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_GetStatusDataType" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1010), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1010), &var);
        UA_GetStatusDataType* commandAux = (UA_GetStatusDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_CloseToolChangerDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[11].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[11].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[11].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1011),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[11].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_CloseToolChangerDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1011);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_CloseToolChangerDataType" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1011), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1011), &var);
        UA_CloseToolChangerDataType* commandAux = (UA_CloseToolChangerDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_OpenToolChangerDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[12].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[12].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[12].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1012),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[12].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        UA_OpenToolChangerDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1012);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_OpenToolChangerDataType" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1012), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1012), &var);
        UA_OpenToolChangerDataType* commandAux = (UA_OpenToolChangerDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRobotParametersDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[13].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[13].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[13].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1013),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[13].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetRobotParametersDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1013);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRobotParametersDataType" );

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.parameterSetting = settings;
        command.parameterSettingSize = 2;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1013), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1013), &var);
        UA_SetRobotParametersDataType* commandAux = (UA_SetRobotParametersDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndeffectorParametersDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[14].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[14].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[14].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1014),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[14].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorParametersDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1014);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndeffectorParametersDataType" );

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.parameterSetting = settings;
        command.parameterSettingSize = 2;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1014), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1014), &var);
        UA_SetEndeffectorParametersDataType* commandAux = (UA_SetEndeffectorParametersDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndeffectorDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[15].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[15].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[15].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1015),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[15].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1015);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndeffectorDataType" );

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.654;
        command.setting = fraction;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1015), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1015), &var);
        UA_SetEndeffectorDataType* commandAux = (UA_SetEndeffectorDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTransAccelDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[16].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[16].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[16].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1016),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[16].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetTransAccelDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1016);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTransAccelDataType" );

        UA_CRCL_TransAccelDataType accel;
        accel.switchField = UA_CRCL_TRANSACCELDATATYPESWITCH_TRANSACCELABSOLUTEDATATYPE;
        UA_CRCL_TransAccelAbsoluteDataType absolAccel;
        absolAccel.id = 835;
        absolAccel.name = UA_STRING( "absolute Accel" );
        absolAccel.setting = 7452.423;
        accel.fields.transAccelAbsoluteDataType = absolAccel;
        command.transAccel = accel;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1016), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1016), &var);
        UA_SetTransAccelDataType* commandAux = (UA_SetTransAccelDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTransSpeedDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[17].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[17].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[17].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1017),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[17].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetTransSpeedDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1017);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTransSpeedDataType" );

        UA_CRCL_TransSpeedDataType speed;
        speed.switchField = UA_CRCL_TRANSSPEEDDATATYPESWITCH_TRANSSPEEDRELATIVEDATATYPE;
        UA_CRCL_TransSpeedRelativeDataType relSpeed;
        relSpeed.name = UA_STRING( "rel Speed test" );
        relSpeed.id = 634;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.654;

        relSpeed.fraction = fraction;
        speed.fields.transSpeedRelativeDataType = relSpeed;
        command.transSpeed = speed;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1017), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1017), &var);
        UA_SetTransSpeedDataType* commandAux = (UA_SetTransSpeedDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRotAccelDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[18].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[18].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[18].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1018),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[18].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetRotAccelDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1018);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRotAccelDataType" );

        UA_CRCL_RotAccelDataType accel;
        accel.switchField = UA_CRCL_ROTACCELDATATYPESWITCH_ROTACCELRELATIVEDATATYPE;

        UA_CRCL_RotAccelRelativeDataType relAccel;
        relAccel.name = UA_STRING( "rot rel accel test" );
        relAccel.id = 749;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.123;

        relAccel.fraction = fraction;

        accel.fields.rotAccelRelativeDataType = relAccel;
        command.rotAccel = accel;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1018), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1018), &var);
        UA_SetRotAccelDataType* commandAux = (UA_SetRotAccelDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRotSpeedDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[19].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[19].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[19].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1019),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[19].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetRotSpeedDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1019);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRotSpeedDataType" );

        UA_CRCL_RotSpeedDataType speed;
        speed.switchField = UA_CRCL_ROTSPEEDDATATYPESWITCH_ROTSPEEDRELATIVEDATATYPE;

        UA_CRCL_RotSpeedRelativeDataType relSpeed;
        relSpeed.name = UA_STRING( "rot rel Speed test" );
        relSpeed.id = 634;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.123;

        relSpeed.fraction = fraction;

        speed.fields.rotSpeedRelativeDataType = relSpeed;
        command.rotSpeed = speed;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1019), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1019), &var);
        UA_SetRotSpeedDataType* commandAux = (UA_SetRotSpeedDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetAngleUnitsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[20].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[20].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[20].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1020),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[20].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetAngleUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1020);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetAngleUnitsDataType" );

        command.unitName = UA_CRCL_ANGLEUNITENUMDATATYPE_RADIAN;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1020), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1020), &var);
        UA_SetAngleUnitsDataType* commandAux = (UA_SetAngleUnitsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndPoseToleranceDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[21].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[21].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[21].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1021),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[21].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetEndPoseToleranceDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1021);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndPoseToleranceDataType" );

        UA_CRCL_PoseToleranceDataType poseTol;
        poseTol.id = 8563;
        poseTol.name = UA_STRING( "pose Tolerance test ");
        poseTol.xAxisTolerance = 865.213;
        poseTol.xPointTolerance = 9764.523;
        poseTol.yPointTolerance = 913.678;
        poseTol.zAxisTolerance = 954.7343;
        poseTol.zPointTolerance = 6452.523;

        command.tolerance = poseTol;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1021), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1021), &var);
        UA_SetEndPoseToleranceDataType* commandAux = (UA_SetEndPoseToleranceDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetForceUnitsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[22].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[22].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[22].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1022),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[22].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetForceUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1022);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetForceUnitsDataType" );

        command.unitName = UA_CRCL_FORCEUNITENUMDATATYPE_NEWTON;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1022), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1022), &var);
        UA_SetForceUnitsDataType* commandAux = (UA_SetForceUnitsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetIntermediatePoseToleranceDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[23].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[23].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[23].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1023),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[23].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetIntermediatePoseToleranceDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1023);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetIntermediatePoseToleranceDataType" );

        UA_CRCL_PoseToleranceDataType poseTol;
        poseTol.id = 8563;
        poseTol.name = UA_STRING( "pose Tolerance test ");
        poseTol.xAxisTolerance = 865.213;
        poseTol.xPointTolerance = 9764.523;
        poseTol.yPointTolerance = 913.678;
        poseTol.zAxisTolerance = 954.7343;
        poseTol.zPointTolerance = 6452.523;

        command.tolerance = poseTol;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1023), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1023), &var);
        UA_SetIntermediatePoseToleranceDataType* commandAux = (UA_SetIntermediatePoseToleranceDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetLengthUnitsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[24].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[24].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[24].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1024),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[24].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetLengthUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1024);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetLengthUnitsDataType" );

        command.unitName = UA_CRCL_LENGTHUNITENUMDATATYPE_METER;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1024), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1024), &var);
        UA_SetLengthUnitsDataType* commandAux = (UA_SetLengthUnitsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetMotionCoordinationDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[25].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[25].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[25].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1025),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[25].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetMotionCoordinationDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1025);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetMotionCoordinationDataType" );

        command.coordinated = UA_TRUE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1025), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1025), &var);
        UA_SetMotionCoordinationDataType* commandAux = (UA_SetMotionCoordinationDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTorqueUnitsDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[26].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[26].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[26].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1026),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[26].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_SetTorqueUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1026);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTorqueUnitsDataType" );

        command.unitName = UA_CRCL_TORQUEUNITENUMDATATYPE_NEWTONMETER;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1026), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1026), &var);
        UA_SetTorqueUnitsDataType* commandAux = (UA_SetTorqueUnitsDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_StopMotionDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[27].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[27].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[27].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1027),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[27].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_StopMotionDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1027);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_StopMotionDataType" );

        command.stopCondition = UA_CRCL_STOPCONDITIONENUMDATATYPE_IMMEDIATE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1027), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1027), &var);
        UA_StopMotionDataType* commandAux = (UA_StopMotionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ConfigureStatusReportDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[28].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[28].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[28].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1028),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[28].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_ConfigureStatusReportDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1028);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ConfigureStatusReportDataType" );

        command.reportJointStatuses = true;
        command.reportPoseStatus = true;
        command.reportGripperStatus = true;
        command.reportSettingsStatus = true;
        command.reportSensorsStatus = true;
        command.reportGuardsStatus = true;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1028), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1028), &var);
        UA_ConfigureStatusReportDataType* commandAux = (UA_ConfigureStatusReportDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableSensorDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[29].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[29].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[29].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1029),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[29].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_EnableSensorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1029);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableSensorDataType" );

        command.sensorID = UA_STRING( "TestSensorName");

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.sensorOption = settings;
        command.sensorOptionSize = 2;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1029), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1029), &var);
        UA_EnableSensorDataType* commandAux = (UA_EnableSensorDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DisableSensorDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[30].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[30].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[30].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1030),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[30].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_DisableSensorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1030);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableSensorDataType" );

        command.sensorID = UA_STRING( "TestSensorID" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1030), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1030), &var);
        UA_DisableSensorDataType* commandAux = (UA_DisableSensorDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableGripperDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[31].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[31].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[31].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1031),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[31].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_EnableGripperDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1031);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableGripperDataType" );

        command.gripperName = UA_STRING( "TestGripperName");

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );

        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
        settings[0] = setting1;
        settings[1] = setting2;

        command.gripperOption = settings;
        command.gripperOptionSize = 2;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1031), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1031), &var);
        UA_EnableGripperDataType* commandAux = (UA_EnableGripperDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DisableGripperDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[32].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[32].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[32].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1032),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[32].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_DisableGripperDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1032);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableGripperDataType" );

        command.gripperName = UA_STRING( "TestGripperName");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1032), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1032), &var);
        UA_DisableGripperDataType* commandAux = (UA_DisableGripperDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableRobotParameterStatusDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[33].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[33].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[33].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1033),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[33].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_EnableRobotParameterStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1033);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableRobotParametersStatusDataType" );

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1033), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1033), &var);
        UA_EnableRobotParameterStatusDataType* commandAux = (UA_EnableRobotParameterStatusDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[34].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[34].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[34].typeId;

        UA_StatusCode retVal = UA_STATUSCODE_GOOD;

        retVal |= UA_Server_addVariableNode( server,
                                             UA_NODEID_NUMERIC(1, 1034),
                                             UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                             UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[34].typeName ) ),
                                             UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                             vattr, NULL, NULL
                                             );

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_DisableRobotParameterStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1034);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableRobotParametersStatusDataType" );

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE] );
        retVal |= UA_Server_writeValue(server, UA_NODEID_NUMERIC(1, 1034), var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1034), &var);
        UA_DisableRobotParameterStatusDataType* commandAux = (UA_DisableRobotParameterStatusDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( commandAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
}


/*
TEST_CASE("Test client - Write all commands in CRCLCommandsUnion", "[WriteCommandsInCRCLCommandsUnion]"){

    UA_Boolean running = true;

    UA_StatusCode retVal = UA_STATUSCODE_GOOD;

    UA_Server* server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 4567, NULL);

    REQUIRE( 0 == namespace_crcl_generated( server ) );

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName )  );
    vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName ) );
    UA_NodeId_init( &vattr.dataType );
    vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeId;

    retVal |= UA_Server_addVariableNode( server,
                                                 UA_NODEID_NUMERIC(1, 1000),
                                                 UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                 UA_QUALIFIEDNAME(0, const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName ) ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                 vattr, NULL, NULL
                                                 );
        REQUIRE( retVal == 0 );

        std::thread serverThread(UA_Server_run, server, &running);
        serverThread.detach();

    std::vector<UA_DataType> typesVector;
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE] );

    std::unique_ptr< UA_Client, SAMY::SAMYRobot::ClientDeleter > client;
    std::string address = "opc.tcp://localhost:4567";
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    client.reset( UA_Client_new() );
    UA_ClientConfig *cc = UA_Client_getConfig( client.get() );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    retVal |= UA_Client_connect( client.get(), address.c_str() );

    SECTION("UA_InitCanonDataType"){
        UA_InitCanonDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_InitCanonDataType" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND;
        commandsUnion.fields.initCanonCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.initCanonCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE], &str );
        std::cout<< str.data << std::endl;


        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_EndCanonDataType"){
        UA_EndCanonDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1001);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EndCanonDataType" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND;
        commandsUnion.fields.endCanonCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.endCanonCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_MessageDataType"){
        UA_MessageDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MessageDataType" );

        command.message = UA_STRING( "TEST MESSAGE!" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND;
        commandsUnion.fields.messageCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.messageCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_MoveToDataType"){
        UA_MoveToDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveToDataType" );

        command.endPosition.id = 987;
        command.endPosition.name = UA_STRING( "POSITIONNAME" );
        command.endPosition.point.id = 87;
        command.endPosition.point.name = UA_STRING( "POINT NAME" );
        command.endPosition.point.x = 0.987;
        command.endPosition.point.y = 6.543;
        command.endPosition.point.z = 1.467;
        command.endPosition.xAxis.id = 8711;
        command.endPosition.xAxis.name = UA_STRING( "xVector NAME" );
        command.endPosition.xAxis.i = 0.987;
        command.endPosition.xAxis.j = 6.543;
        command.endPosition.xAxis.k = 1.467;
        command.endPosition.zAxis.id = 8764;
        command.endPosition.zAxis.name = UA_STRING( "zVector NAME" );
        command.endPosition.zAxis.i = 5.987;
        command.endPosition.zAxis.j = 8.543;
        command.endPosition.zAxis.k = 121.467;
        command.moveStraight = UA_TRUE;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND;
        commandsUnion.fields.moveToCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.moveToCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_MoveScrewDataType"){
        UA_MoveScrewDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveScrewDataType" );

        command.axialDistanceFree = 6.543;
        command.axialDistanceScrew = 87.123;
        command.axisPoint.id = 87;
        command.axisPoint.name = UA_STRING( "POINT NAME" );
        command.axisPoint.x = 0.987;
        command.axisPoint.y = 6.543;
        command.axisPoint.z = 1.467;
        command.turn = 5.123;

        UA_CRCL_PoseDataType pose1;
        pose1.id = 743;
        pose1.name = UA_STRING( "POSE1" );
        pose1.point.id = 87;
        pose1.point.name = UA_STRING( "POINT NAME" );
        pose1.point.x = 0.987;
        pose1.point.y = 6.543;
        pose1.point.z = 1.467;
        pose1.xAxis.id = 8711;
        pose1.xAxis.name = UA_STRING( "xVector NAME" );
        pose1.xAxis.i = 0.987;
        pose1.xAxis.j = 6.543;
        pose1.xAxis.k = 1.467;
        pose1.zAxis.id = 8764;
        pose1.zAxis.name = UA_STRING( "zVector NAME" );
        pose1.zAxis.i = 5.987;
        pose1.zAxis.j = 8.543;
        pose1.zAxis.k = 121.467;

        command.startPosition = pose1;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND;
        commandsUnion.fields.moveScrewCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.moveScrewCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_MoveThroughToDataType"){
        UA_MoveThroughToDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1005);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_MoveThroughToDataType" );

        UA_CRCL_PoseDataType pose1;
        pose1.id = 743;
        pose1.name = UA_STRING( "POSE1" );
        pose1.point.id = 87;
        pose1.point.name = UA_STRING( "POINT NAME" );
        pose1.point.x = 0.987;
        pose1.point.y = 6.543;
        pose1.point.z = 1.467;
        pose1.xAxis.id = 8711;
        pose1.xAxis.name = UA_STRING( "xVector NAME" );
        pose1.xAxis.i = 0.987;
        pose1.xAxis.j = 6.543;
        pose1.xAxis.k = 1.467;
        pose1.zAxis.id = 8764;
        pose1.zAxis.name = UA_STRING( "zVector NAME" );
        pose1.zAxis.i = 5.987;
        pose1.zAxis.j = 8.543;
        pose1.zAxis.k = 121.467;

        UA_CRCL_PoseDataType pose2;
        pose2.id = 743;
        pose2.name = UA_STRING( "POSE2" );
        pose2.point.id = 87;
        pose2.point.name = UA_STRING( "POINT NAME" );
        pose2.point.x = 0.987;
        pose2.point.y = 6.543;
        pose2.point.z = 1.467;
        pose2.xAxis.id = 8711;
        pose2.xAxis.name = UA_STRING( "xVector NAME" );
        pose2.xAxis.i = 0.987;
        pose2.xAxis.j = 6.543;
        pose2.xAxis.k = 1.467;
        pose2.zAxis.id = 8764;
        pose2.zAxis.name = UA_STRING( "zVector NAME" );
        pose2.zAxis.i = 5.987;
        pose2.zAxis.j = 8.543;
        pose2.zAxis.k = 121.467;

        UA_CRCL_PoseDataType *waypoint = (UA_CRCL_PoseDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_POSEDATATYPE]);

        waypoint[0] = pose1;
        waypoint[1] = pose2;

        command.moveStraight = UA_TRUE;
        command.waypointSize = 2;
        command.waypoint = waypoint;
        command.numPositions = 2;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND;
        commandsUnion.fields.moveThroughToCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.moveThroughToCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_DwellDataType"){
        UA_DwellDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1006);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DwellDataType" );

        command.dwellTime = 101.101;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND;
        commandsUnion.fields.dwellCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.dwellCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_ActuateJointsDataType"){
        UA_ActuateJointsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1007);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ActuateJointsDataType" );

        UA_CRCL_ActuateJointDataType act1;
        act1.id = 134;
        act1.name = UA_STRING( "actuate joint 1" );
        act1.jointNumber = 2;
        act1.jointPosition = 54.74;
        act1.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTSPEEDACCEL;
        act1.jointDetails.fields.jointSpeedAccel.id = 101;
        act1.jointDetails.fields.jointSpeedAccel.name = UA_STRING( "Actuate Joint jointSpeedAccel" );
        act1.jointDetails.fields.jointSpeedAccel.jointAccel = 10.101;
        act1.jointDetails.fields.jointSpeedAccel.jointSpeed = 210.101;

        UA_CRCL_ActuateJointDataType act2;
        act2.id = 6341;
        act2.name = UA_STRING( "actuate joint 2" );
        act2.jointNumber = 5;
        act2.jointPosition = 98.314;
        act2.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTFORCETORQUE;
        act2.jointDetails.fields.jointForceTorque.id = 101;
        act2.jointDetails.fields.jointForceTorque.name = UA_STRING( "Actuate Joint jointForceTorque" );
        act2.jointDetails.fields.jointForceTorque.changeRate = 10.101;
        act2.jointDetails.fields.jointForceTorque.setting = 210.101;

        UA_CRCL_ActuateJointDataType *actuateJoints = (UA_CRCL_ActuateJointDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_ACTUATEJOINTDATATYPE]);

        actuateJoints[0] = act1;
        actuateJoints[1] = act2;

        UA_CRCL_JointPositionsTolerancesDataType tols;
        tols.id = 9532;
        tols.name = UA_STRING( "JointPosition tolerances test" );

        UA_CRCL_JointPositionToleranceSettingDataType tol1;
        tol1.id = 6363;
        tol1.name = UA_STRING( "JointPositionTolerance 1" );
        tol1.jointNumber = 1;
        tol1.jointPositionTolerance = 9.876;

        UA_CRCL_JointPositionToleranceSettingDataType tol2;
        tol2.id = 15638;
        tol2.name = UA_STRING( "JointPositionTolerance 2" );
        tol2.jointNumber = 4;
        tol2.jointPositionTolerance = 5.6272;

        UA_CRCL_JointPositionToleranceSettingDataType *settings = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);
        settings[0] = tol1;
        settings[1] = tol2;

        tols.setting = settings;
        tols.settingSize = 2;

        command.actuateJointSize = 2;
        command.actuateJoint = actuateJoints;
        command.jointTolerances = tols;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND;
        commandsUnion.fields.actuateJointsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.actuateJointsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_ConfigureJointReportsDataType"){
        UA_ConfigureJointReportsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1008);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ConfigureJointReportsDataType" );

        UA_CRCL_ConfigureJointReportDataType conf1;
        conf1.id = 9213;
        conf1.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 1" );
        conf1.jointNumber = 2;
        conf1.reportPosition = UA_TRUE;
        conf1.reportTorqueOrForce = UA_FALSE;
        conf1.reportVelocity = UA_TRUE;

        UA_CRCL_ConfigureJointReportDataType conf2;
        conf2.id = 9213;
        conf2.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 2" );
        conf2.jointNumber = 3;
        conf2.reportPosition = UA_TRUE;
        conf2.reportTorqueOrForce = UA_TRUE;
        conf2.reportVelocity = UA_TRUE;

        UA_CRCL_ConfigureJointReportDataType *confReports = (UA_CRCL_ConfigureJointReportDataType *) UA_Array_new(2,
                                                                              &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_CONFIGUREJOINTREPORTDATATYPE]);

        confReports[0] = conf1;
        confReports[1] = conf2;

        command.configureJointReport = confReports;
        command.configureJointReportSize = 2;

        command.resetAll = UA_FALSE;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND;
        commandsUnion.fields.configureJointReportsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.configureJointReportsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetDefaultJointPositionsTolerancesDataType"){
        UA_SetDefaultJointPositionsTolerancesDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1009);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetDefaultJointPositionsTolerancesDataType" );

        UA_CRCL_JointPositionToleranceSettingDataType tolSet1;
        tolSet1.id = 663;
        tolSet1.name = UA_STRING( "JointPositionTolerance 1" );
        tolSet1.jointNumber = 43;
        tolSet1.jointPositionTolerance = 411.12;

        UA_CRCL_JointPositionToleranceSettingDataType tolSet2;
        tolSet2.id = 7564;
        tolSet2.name = UA_STRING( "JointPositionTolerance 2" );
        tolSet2.jointNumber = 21;
        tolSet2.jointPositionTolerance = 354.236;

        UA_CRCL_JointPositionToleranceSettingDataType *tolSettings = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);

        tolSettings[0] = tolSet1;
        tolSettings[1] = tolSet2;

        UA_CRCL_JointPositionsTolerancesDataType tol;
        tol.id = 534;
        tol.name = UA_STRING( "JOINT TOLERANCES" );
        tol.setting = tolSettings;
        tol.settingSize = 2;

        command.jointTolerances = tol;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND;
        commandsUnion.fields.setDefaultJointPositionsTolerancesCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setDefaultJointPositionsTolerancesCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_GetStatusDataType"){
        UA_GetStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1010);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_GetStatusDataType" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND;
        commandsUnion.fields.getStatusCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.getStatusCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_CloseToolChangerDataType"){
        UA_CloseToolChangerDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1011);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_CloseToolChangerDataType" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND;
        commandsUnion.fields.closeToolChangerCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.closeToolChangerCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_OpenToolChangerDataType"){
        UA_OpenToolChangerDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1012);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_OpenToolChangerDataType" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND;
        commandsUnion.fields.openToolChangerCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.openToolChangerCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetRobotParametersDataType"){
        UA_SetRobotParametersDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1013);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRobotParametersDataType" );

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.parameterSetting = settings;
        command.parameterSettingSize = 2;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND;
        commandsUnion.fields.setRobotParametersCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setRobotParametersCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetEndeffectorParametersDataType"){
        UA_SetEndeffectorParametersDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1014);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndeffectorParametersDataType" );

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.parameterSetting = settings;
        command.parameterSettingSize = 2;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND;
        commandsUnion.fields.setEndeffectorParametersCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setEndeffectorParametersCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetEndeffectorDataType"){
        UA_SetEndeffectorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1015);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndeffectorDataType" );

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.654;
        command.setting = fraction;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND;
        commandsUnion.fields.setEndeffectorCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setEndeffectorCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetTransAccelDataType"){
        UA_SetTransAccelDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1016);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTransAccelDataType" );

        UA_CRCL_TransAccelDataType accel;
        accel.switchField = UA_CRCL_TRANSACCELDATATYPESWITCH_TRANSACCELABSOLUTEDATATYPE;
        UA_CRCL_TransAccelAbsoluteDataType absolAccel;
        absolAccel.id = 835;
        absolAccel.name = UA_STRING( "absolute Accel" );
        absolAccel.setting = 7452.423;
        accel.fields.transAccelAbsoluteDataType = absolAccel;
        command.transAccel = accel;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND;
        commandsUnion.fields.setTransAccelCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setTransAccelCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetTransSpeedDataType"){
        UA_SetTransSpeedDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1017);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTransSpeedDataType" );

        UA_CRCL_TransSpeedDataType speed;
        speed.switchField = UA_CRCL_TRANSSPEEDDATATYPESWITCH_TRANSSPEEDRELATIVEDATATYPE;
        UA_CRCL_TransSpeedRelativeDataType relSpeed;
        relSpeed.name = UA_STRING( "rel Speed test" );
        relSpeed.id = 634;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.654;

        relSpeed.fraction = fraction;
        speed.fields.transSpeedRelativeDataType = relSpeed;
        command.transSpeed = speed;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND;
        commandsUnion.fields.setTransSpeedCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setTransSpeedCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetRotAccelDataType"){
        UA_SetRotAccelDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1018);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRotAccelDataType" );

        UA_CRCL_RotAccelDataType accel;
        accel.switchField = UA_CRCL_ROTACCELDATATYPESWITCH_ROTACCELRELATIVEDATATYPE;

        UA_CRCL_RotAccelRelativeDataType relAccel;
        relAccel.name = UA_STRING( "rot rel accel test" );
        relAccel.id = 749;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.123;

        relAccel.fraction = fraction;

        accel.fields.rotAccelRelativeDataType = relAccel;
        command.rotAccel = accel;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND;
        commandsUnion.fields.setRotAccelCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setRotAccelCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetRotSpeedDataType"){
        UA_SetRotSpeedDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1019);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetRotSpeedDataType" );

        UA_CRCL_RotSpeedDataType speed;
        speed.switchField = UA_CRCL_ROTSPEEDDATATYPESWITCH_ROTSPEEDRELATIVEDATATYPE;

        UA_CRCL_RotSpeedRelativeDataType relSpeed;
        relSpeed.name = UA_STRING( "rot rel Speed test" );
        relSpeed.id = 634;

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.123;

        relSpeed.fraction = fraction;

        speed.fields.rotSpeedRelativeDataType = relSpeed;
        command.rotSpeed = speed;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND;
        commandsUnion.fields.setRotSpeedCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setRotSpeedCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetAngleUnitsDataType"){
        UA_SetAngleUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1020);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetAngleUnitsDataType" );

        command.unitName = UA_CRCL_ANGLEUNITENUMDATATYPE_RADIAN;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND;
        commandsUnion.fields.setAngleUnitsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setAngleUnitsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetEndPoseToleranceDataType"){
        UA_SetEndPoseToleranceDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1021);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetEndPoseToleranceDataType" );

        UA_CRCL_PoseToleranceDataType poseTol;
        poseTol.id = 8563;
        poseTol.name = UA_STRING( "pose Tolerance test ");
        poseTol.xAxisTolerance = 865.213;
        poseTol.xPointTolerance = 9764.523;
        poseTol.yPointTolerance = 913.678;
        poseTol.zAxisTolerance = 954.7343;
        poseTol.zPointTolerance = 6452.523;

        command.tolerance = poseTol;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND;
        commandsUnion.fields.setEndPoseToleranceCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setEndPoseToleranceCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetForceUnitsDataType"){
        UA_SetForceUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1022);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetForceUnitsDataType" );

        command.unitName = UA_CRCL_FORCEUNITENUMDATATYPE_NEWTON;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND;
        commandsUnion.fields.setForceUnitsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setForceUnitsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetIntermediatePoseToleranceDataType"){
        UA_SetIntermediatePoseToleranceDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1023);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetIntermediatePoseToleranceDataType" );

        UA_CRCL_PoseToleranceDataType poseTol;
        poseTol.id = 8563;
        poseTol.name = UA_STRING( "pose Tolerance test ");
        poseTol.xAxisTolerance = 865.213;
        poseTol.xPointTolerance = 9764.523;
        poseTol.yPointTolerance = 913.678;
        poseTol.zAxisTolerance = 954.7343;
        poseTol.zPointTolerance = 6452.523;

        command.tolerance = poseTol;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND;
        commandsUnion.fields.setIntermediatePoseToleranceCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setIntermediatePoseToleranceCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetLengthUnitsDataType"){
        UA_SetLengthUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1024);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetLengthUnitsDataType" );

        command.unitName = UA_CRCL_LENGTHUNITENUMDATATYPE_METER;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND;
        commandsUnion.fields.setLengthUnitsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setLengthUnitsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetMotionCoordinationDataType"){
        UA_SetMotionCoordinationDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1025);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetMotionCoordinationDataType" );

        command.coordinated = UA_TRUE;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND;
        commandsUnion.fields.setMotionCoordinationCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setMotionCoordinationCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_SetTorqueUnitsDataType"){
        UA_SetTorqueUnitsDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1026);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_SetTorqueUnitsDataType" );

        command.unitName = UA_CRCL_TORQUEUNITENUMDATATYPE_NEWTONMETER;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND;
        commandsUnion.fields.setTorqueUnitsCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.setTorqueUnitsCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_StopMotionDataType"){
        UA_StopMotionDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1027);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_StopMotionDataType" );

        command.stopCondition = UA_CRCL_STOPCONDITIONENUMDATATYPE_IMMEDIATE;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND;
        commandsUnion.fields.stopMotionCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.stopMotionCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_ConfigureStatusReportDataType"){
        UA_ConfigureStatusReportDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1028);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_ConfigureStatusReportDataType" );

        command.reportJointStatuses = true;
        command.reportPoseStatus = true;
        command.reportGripperStatus = true;
        command.reportSettingsStatus = true;
        command.reportSensorsStatus = true;
        command.reportGuardsStatus = true;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND;
        commandsUnion.fields.configureStatusReportCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.configureStatusReportCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_EnableSensorDataType"){
        UA_EnableSensorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1029);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableSensorDataType" );

        command.sensorID = UA_STRING( "TestSensorName");

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

        settings[0] = setting1;
        settings[1] = setting2;

        command.sensorOption = settings;
        command.sensorOptionSize = 2;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND;
        commandsUnion.fields.enableSensorCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.enableSensorCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_DisableSensorDataType"){
        UA_DisableSensorDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1030);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableSensorDataType" );

        command.sensorID = UA_STRING( "TestSensorID" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND;
        commandsUnion.fields.disableSensorCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.disableSensorCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_EnableGripperDataType"){
        UA_EnableGripperDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1031);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableGripperDataType" );

        command.gripperName = UA_STRING( "TestGripperName");

        UA_CRCL_ParameterSettingDataType setting1;
        setting1.id = 1398;
        setting1.name = UA_STRING( "SETTING1" );
        setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
        setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

        UA_CRCL_ParameterSettingDataType setting2;
        setting2.id = 357;
        setting2.name = UA_STRING( "SETTING2" );
        setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
        setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );

        UA_CRCL_ParameterSettingDataType *settings = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                       &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
        settings[0] = setting1;
        settings[1] = setting2;

        command.gripperOption = settings;
        command.gripperOptionSize = 2;

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND;
        commandsUnion.fields.enableGripperCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.enableGripperCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_DisableGripperDataType"){
        UA_DisableGripperDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1032);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableGripperDataType" );

        command.gripperName = UA_STRING( "TestGripperName");

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND;
        commandsUnion.fields.disableGripperCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.disableGripperCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_EnableRobotParameterStatusDataType"){
        UA_EnableRobotParameterStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1033);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_EnableRobotParametersStatusDataType" );

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND;
        commandsUnion.fields.enableRobotParameterStatusCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.enableRobotParameterStatusCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
        UA_DisableRobotParameterStatusDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1034);
        command.guard = NULL;
        command.guardSize = 0;
        command.id = 5678;
        command.name = UA_STRING( "UA_DisableRobotParameterStatusDataType" );

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND;
        commandsUnion.fields.disableRobotParameterStatusCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client.get(), UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        UA_Client_disconnect( client.get() );

        UA_Variant_init( &var );
        retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1000), &var);

        UA_CRCLCommandsUnionDataType* commandAux = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_String str;
        UA_String_init( &str );
        UA_print( &commandAux->fields.disableRobotParameterStatusCommand, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout<< str.data << std::endl;

        REQUIRE( retVal == UA_STATUSCODE_GOOD );

        running = false;

        UA_Server_delete( server );

    }
}
*/





TEST_CASE("Test Server/Client - Write CRCLSkill with all the commands with client and read it with the server", "[ClientWriteCRCLSkillServerAutoRead]"){

    UA_Boolean running = true;

    UA_StatusCode retVal = UA_STATUSCODE_GOOD;

    UA_Server* server = UA_Server_new();
    UA_ServerConfig *config = UA_Server_getConfig(server);
    UA_ServerConfig_setMinimal(config, 4567, NULL);

    REQUIRE( 0 == namespace_crcl_generated( server ) );

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName )  );
    vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName ) );
    UA_NodeId_init( &vattr.dataType );
    vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeId;

    retVal |= UA_Server_addVariableNode( server,
                                                 UA_NODEID_NUMERIC(1, 1300),
                                                 UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                 UA_QUALIFIEDNAME(0, const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName ) ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                 vattr, NULL, NULL
                                                 );
        REQUIRE( retVal == 0 );

        std::thread serverThread(UA_Server_run, server, &running);
        serverThread.detach();

    UA_CRCLSkillDataType skill;
    skill.name = UA_STRING( "Skill test" );
    skill.id = 999;
    skill.cRCLCommandsSize = 35;

    UA_CRCLCommandsUnionDataType *commandsArray = (UA_CRCLCommandsUnionDataType *) UA_Array_new(35,
                                                                          &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE]);



    UA_InitCanonDataType command1;
    command1.commandID = 1234;
    command1.realTimeCommand = true;
    command1.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1000);
    command1.guard = NULL;
    command1.guardSize = 0;
    command1.id = 5678;
    command1.name = UA_STRING( "UA_InitCanonDataType" );

    UA_CRCLCommandsUnionDataType commandsUnion1;
    commandsUnion1.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_INITCANONCOMMAND;
    commandsUnion1.fields.initCanonCommand = command1;



    UA_EndCanonDataType command2;
    command2.commandID = 1234;
    command2.realTimeCommand = true;
    command2.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1001);
    command2.guard = NULL;
    command2.guardSize = 0;
    command2.id = 5678;
    command2.name = UA_STRING( "UA_EndCanonDataType" );

    UA_CRCLCommandsUnionDataType commandsUnion2;
    commandsUnion2.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENDCANONCOMMAND;
    commandsUnion2.fields.endCanonCommand = command2;



    UA_MessageDataType command3;
    command3.commandID = 1234;
    command3.realTimeCommand = true;
    command3.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1002);
    command3.guard = NULL;
    command3.guardSize = 0;
    command3.id = 5678;
    command3.name = UA_STRING( "UA_MessageDataType" );

    command3.message = UA_STRING( "TEST MESSAGE!" );

    UA_CRCLCommandsUnionDataType commandsUnion3;
    commandsUnion3.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MESSAGECOMMAND;
    commandsUnion3.fields.messageCommand = command3;



    UA_MoveToDataType command4;
    command4.commandID = 1234;
    command4.realTimeCommand = true;
    command4.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1003);
    command4.guard = NULL;
    command4.guardSize = 0;
    command4.id = 5678;
    command4.name = UA_STRING( "UA_MoveToDataType" );

    command4.endPosition.id = 987;
    command4.endPosition.name = UA_STRING( "POSITIONNAME" );
    command4.endPosition.point.id = 87;
    command4.endPosition.point.name = UA_STRING( "POINT NAME" );
    command4.endPosition.point.x = 0.987;
    command4.endPosition.point.y = 6.543;
    command4.endPosition.point.z = 1.467;
    command4.endPosition.xAxis.id = 8711;
    command4.endPosition.xAxis.name = UA_STRING( "xVector NAME" );
    command4.endPosition.xAxis.i = 0.987;
    command4.endPosition.xAxis.j = 6.543;
    command4.endPosition.xAxis.k = 1.467;
    command4.endPosition.zAxis.id = 8764;
    command4.endPosition.zAxis.name = UA_STRING( "zVector NAME" );
    command4.endPosition.zAxis.i = 5.987;
    command4.endPosition.zAxis.j = 8.543;
    command4.endPosition.zAxis.k = 121.467;
    command4.moveStraight = UA_TRUE;

    UA_CRCLCommandsUnionDataType commandsUnion4;
    commandsUnion4.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND;
    commandsUnion4.fields.moveToCommand = command4;



    UA_MoveScrewDataType command5;
    command5.commandID = 1234;
    command5.realTimeCommand = true;
    command5.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1004);
    command5.guard = NULL;
    command5.guardSize = 0;
    command5.id = 5678;
    command5.name = UA_STRING( "UA_MoveScrewDataType" );

    command5.axialDistanceFree = 6.543;
    command5.axialDistanceScrew = 87.123;
    command5.axisPoint.id = 87;
    command5.axisPoint.name = UA_STRING( "POINT NAME" );
    command5.axisPoint.x = 0.987;
    command5.axisPoint.y = 6.543;
    command5.axisPoint.z = 1.467;
    command5.turn = 5.123;

    UA_CRCL_PoseDataType pose1;
    pose1.id = 743;
    pose1.name = UA_STRING( "POSE1" );
    pose1.point.id = 87;
    pose1.point.name = UA_STRING( "POINT NAME" );
    pose1.point.x = 0.987;
    pose1.point.y = 6.543;
    pose1.point.z = 1.467;
    pose1.xAxis.id = 8711;
    pose1.xAxis.name = UA_STRING( "xVector NAME" );
    pose1.xAxis.i = 0.987;
    pose1.xAxis.j = 6.543;
    pose1.xAxis.k = 1.467;
    pose1.zAxis.id = 8764;
    pose1.zAxis.name = UA_STRING( "zVector NAME" );
    pose1.zAxis.i = 5.987;
    pose1.zAxis.j = 8.543;
    pose1.zAxis.k = 121.467;

    command5.startPosition = pose1;

    UA_CRCLCommandsUnionDataType commandsUnion5;
    commandsUnion5.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND;
    commandsUnion5.fields.moveScrewCommand = command5;



    UA_MoveThroughToDataType command6;
    command6.commandID = 1234;
    command6.realTimeCommand = true;
    command6.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1005);
    command6.guard = NULL;
    command6.guardSize = 0;
    command6.id = 5678;
    command6.name = UA_STRING( "UA_MoveThroughToDataType" );

    UA_CRCL_PoseDataType pose12;
    pose12.id = 743;
    pose12.name = UA_STRING( "POSE1" );
    pose12.point.id = 87;
    pose12.point.name = UA_STRING( "POINT NAME" );
    pose12.point.x = 0.987;
    pose12.point.y = 6.543;
    pose12.point.z = 1.467;
    pose12.xAxis.id = 8711;
    pose12.xAxis.name = UA_STRING( "xVector NAME" );
    pose12.xAxis.i = 0.987;
    pose12.xAxis.j = 6.543;
    pose12.xAxis.k = 1.467;
    pose12.zAxis.id = 8764;
    pose12.zAxis.name = UA_STRING( "zVector NAME" );
    pose12.zAxis.i = 5.987;
    pose12.zAxis.j = 8.543;
    pose12.zAxis.k = 121.467;

    UA_CRCL_PoseDataType pose2;
    pose2.id = 743;
    pose2.name = UA_STRING( "POSE2" );
    pose2.point.id = 87;
    pose2.point.name = UA_STRING( "POINT NAME" );
    pose2.point.x = 0.987;
    pose2.point.y = 6.543;
    pose2.point.z = 1.467;
    pose2.xAxis.id = 8711;
    pose2.xAxis.name = UA_STRING( "xVector NAME" );
    pose2.xAxis.i = 0.987;
    pose2.xAxis.j = 6.543;
    pose2.xAxis.k = 1.467;
    pose2.zAxis.id = 8764;
    pose2.zAxis.name = UA_STRING( "zVector NAME" );
    pose2.zAxis.i = 5.987;
    pose2.zAxis.j = 8.543;
    pose2.zAxis.k = 121.467;

    UA_CRCL_PoseDataType *waypoint = (UA_CRCL_PoseDataType *) UA_Array_new(2,
                                                                          &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_POSEDATATYPE]);

    waypoint[0] = pose12;
    waypoint[1] = pose2;

    command6.moveStraight = UA_TRUE;
    command6.waypointSize = 2;
    command6.waypoint = waypoint;
    command6.numPositions = 2;

    UA_CRCLCommandsUnionDataType commandsUnion6;
    commandsUnion6.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETHROUGHTOCOMMAND;
    commandsUnion6.fields.moveThroughToCommand = command6;



    UA_DwellDataType command7;
    command7.commandID = 1234;
    command7.realTimeCommand = true;
    command7.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1006);
    command7.guard = NULL;
    command7.guardSize = 0;
    command7.id = 5678;
    command7.name = UA_STRING( "UA_DwellDataType" );

    command7.dwellTime = 101.101;

    UA_CRCLCommandsUnionDataType commandsUnion7;
    commandsUnion7.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DWELLCOMMAND;
    commandsUnion7.fields.dwellCommand = command7;



    UA_ActuateJointsDataType command8;
    command8.commandID = 1234;
    command8.realTimeCommand = true;
    command8.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1007);
    command8.guard = NULL;
    command8.guardSize = 0;
    command8.id = 5678;
    command8.name = UA_STRING( "UA_ActuateJointsDataType" );

    UA_CRCL_ActuateJointDataType act1;
    act1.id = 134;
    act1.name = UA_STRING( "actuate joint 1" );
    act1.jointNumber = 2;
    act1.jointPosition = 54.74;
    act1.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTSPEEDACCEL;
    act1.jointDetails.fields.jointSpeedAccel.id = 101;
    act1.jointDetails.fields.jointSpeedAccel.name = UA_STRING( "Actuate Joint jointSpeedAccel" );
    act1.jointDetails.fields.jointSpeedAccel.jointAccel = 10.101;
    act1.jointDetails.fields.jointSpeedAccel.jointSpeed = 210.101;

    UA_CRCL_ActuateJointDataType act2;
    act2.id = 6341;
    act2.name = UA_STRING( "actuate joint 2" );
    act2.jointNumber = 5;
    act2.jointPosition = 98.314;
    act2.jointDetails.switchField = UA_CRCL_JOINTDETAILSDATATYPESWITCH_JOINTFORCETORQUE;
    act2.jointDetails.fields.jointForceTorque.id = 101;
    act2.jointDetails.fields.jointForceTorque.name = UA_STRING( "Actuate Joint jointForceTorque" );
    act2.jointDetails.fields.jointForceTorque.changeRate = 10.101;
    act2.jointDetails.fields.jointForceTorque.setting = 210.101;

    UA_CRCL_ActuateJointDataType *actuateJoints = (UA_CRCL_ActuateJointDataType *) UA_Array_new(2,
                                                                          &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_ACTUATEJOINTDATATYPE]);

    actuateJoints[0] = act1;
    actuateJoints[1] = act2;

    UA_CRCL_JointPositionsTolerancesDataType tols;
    tols.id = 9532;
    tols.name = UA_STRING( "JointPosition tolerances test" );

    UA_CRCL_JointPositionToleranceSettingDataType tol1;
    tol1.id = 6363;
    tol1.name = UA_STRING( "JointPositionTolerance 1" );
    tol1.jointNumber = 1;
    tol1.jointPositionTolerance = 9.876;

    UA_CRCL_JointPositionToleranceSettingDataType tol2;
    tol2.id = 15638;
    tol2.name = UA_STRING( "JointPositionTolerance 2" );
    tol2.jointNumber = 4;
    tol2.jointPositionTolerance = 5.6272;

    UA_CRCL_JointPositionToleranceSettingDataType *settings1 = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                          &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);
    settings1[0] = tol1;
    settings1[1] = tol2;

    tols.setting = settings1;
    tols.settingSize = 2;

    command8.actuateJointSize = 2;
    command8.actuateJoint = actuateJoints;
    command8.jointTolerances = tols;

    UA_CRCLCommandsUnionDataType commandsUnion8;
    commandsUnion8.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ACTUATEJOINTSCOMMAND;
    commandsUnion8.fields.actuateJointsCommand = command8;



    UA_ConfigureJointReportsDataType command9;
    command9.commandID = 1234;
    command9.realTimeCommand = true;
    command9.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1008);
    command9.guard = NULL;
    command9.guardSize = 0;
    command9.id = 5678;
    command9.name = UA_STRING( "UA_ConfigureJointReportsDataType" );

    UA_CRCL_ConfigureJointReportDataType conf1;
    conf1.id = 9213;
    conf1.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 1" );
    conf1.jointNumber = 2;
    conf1.reportPosition = UA_TRUE;
    conf1.reportTorqueOrForce = UA_FALSE;
    conf1.reportVelocity = UA_TRUE;

    UA_CRCL_ConfigureJointReportDataType conf2;
    conf2.id = 9213;
    conf2.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportDataType 2" );
    conf2.jointNumber = 3;
    conf2.reportPosition = UA_TRUE;
    conf2.reportTorqueOrForce = UA_TRUE;
    conf2.reportVelocity = UA_TRUE;

    UA_CRCL_ConfigureJointReportDataType *confReports = (UA_CRCL_ConfigureJointReportDataType *) UA_Array_new(2,
                                                                          &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_CONFIGUREJOINTREPORTDATATYPE]);

    confReports[0] = conf1;
    confReports[1] = conf2;

    command9.configureJointReport = confReports;
    command9.configureJointReportSize = 2;

    command9.resetAll = UA_FALSE;

    UA_CRCLCommandsUnionDataType commandsUnion9;
    commandsUnion9.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGUREJOINTREPORTSCOMMAND;
    commandsUnion9.fields.configureJointReportsCommand = command9;



    UA_SetDefaultJointPositionsTolerancesDataType command10;
    command10.commandID = 1234;
    command10.realTimeCommand = true;
    command10.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1009);
    command10.guard = NULL;
    command10.guardSize = 0;
    command10.id = 5678;
    command10.name = UA_STRING( "UA_SetDefaultJointPositionsTolerancesDataType" );

    UA_CRCL_JointPositionToleranceSettingDataType tolSet1;
    tolSet1.id = 663;
    tolSet1.name = UA_STRING( "JointPositionTolerance 1" );
    tolSet1.jointNumber = 43;
    tolSet1.jointPositionTolerance = 411.12;

    UA_CRCL_JointPositionToleranceSettingDataType tolSet2;
    tolSet2.id = 7564;
    tolSet2.name = UA_STRING( "JointPositionTolerance 2" );
    tolSet2.jointNumber = 21;
    tolSet2.jointPositionTolerance = 354.236;

    UA_CRCL_JointPositionToleranceSettingDataType *tolSettings = (UA_CRCL_JointPositionToleranceSettingDataType *) UA_Array_new(2,
                                                                   &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_JOINTPOSITIONTOLERANCESETTINGDATATYPE]);

    tolSettings[0] = tolSet1;
    tolSettings[1] = tolSet2;

    UA_CRCL_JointPositionsTolerancesDataType posTol;
    posTol.id = 534;
    posTol.name = UA_STRING( "JOINT TOLERANCES" );
    posTol.setting = tolSettings;
    posTol.settingSize = 2;

    command10.jointTolerances = posTol;

    UA_CRCLCommandsUnionDataType commandsUnion10;
    commandsUnion10.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETDEFAULTJOINTPOSITIONSTOLERANCESCOMMAND;
    commandsUnion10.fields.setDefaultJointPositionsTolerancesCommand = command10;



    UA_GetStatusDataType command11;
    command11.commandID = 1234;
    command11.realTimeCommand = true;
    command11.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1010);
    command11.guard = NULL;
    command11.guardSize = 0;
    command11.id = 5678;
    command11.name = UA_STRING( "UA_GetStatusDataType" );

    UA_CRCLCommandsUnionDataType commandsUnion11;
    commandsUnion11.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_GETSTATUSCOMMAND;
    commandsUnion11.fields.getStatusCommand = command11;



    UA_CloseToolChangerDataType command12;
    command12.commandID = 1234;
    command12.realTimeCommand = true;
    command12.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1011);
    command12.guard = NULL;
    command12.guardSize = 0;
    command12.id = 5678;
    command12.name = UA_STRING( "UA_CloseToolChangerDataType" );

    UA_CRCLCommandsUnionDataType commandsUnion12;
    commandsUnion12.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CLOSETOOLCHANGERCOMMAND;
    commandsUnion12.fields.closeToolChangerCommand = command12;



    UA_OpenToolChangerDataType command13;
    command13.commandID = 1234;
    command13.realTimeCommand = true;
    command13.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1012);
    command13.guard = NULL;
    command13.guardSize = 0;
    command13.id = 5678;
    command13.name = UA_STRING( "UA_OpenToolChangerDataType" );

    UA_CRCLCommandsUnionDataType commandsUnion13;
    commandsUnion13.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_OPENTOOLCHANGERCOMMAND;
    commandsUnion13.fields.openToolChangerCommand = command13;



    UA_SetRobotParametersDataType command14;
    command14.commandID = 1234;
    command14.realTimeCommand = true;
    command14.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1013);
    command14.guard = NULL;
    command14.guardSize = 0;
    command14.id = 5678;
    command14.name = UA_STRING( "UA_SetRobotParametersDataType" );

    UA_CRCL_ParameterSettingDataType setting1;
    setting1.id = 1398;
    setting1.name = UA_STRING( "SETTING1" );
    setting1.parameterName = UA_STRING( "Name of the setting 1 test" );
    setting1.parameterValue = UA_STRING( "Value of the setting 1 test" );

    UA_CRCL_ParameterSettingDataType setting2;
    setting2.id = 357;
    setting2.name = UA_STRING( "SETTING2" );
    setting2.parameterName = UA_STRING( "Name of the setting 2 test" );
    setting2.parameterValue = UA_STRING( "Value of the setting 2 test" );


    UA_CRCL_ParameterSettingDataType *settings2 = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                   &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

    settings2[0] = setting1;
    settings2[1] = setting2;

    command14.parameterSetting = settings2;
    command14.parameterSettingSize = 2;

    UA_CRCLCommandsUnionDataType commandsUnion14;
    commandsUnion14.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROBOTPARAMETERSCOMMAND;
    commandsUnion14.fields.setRobotParametersCommand = command14;



    UA_SetEndeffectorParametersDataType command15;
    command15.commandID = 1234;
    command15.realTimeCommand = true;
    command15.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1014);
    command15.guard = NULL;
    command15.guardSize = 0;
    command15.id = 5678;
    command15.name = UA_STRING( "UA_SetEndeffectorParametersDataType" );

    UA_CRCL_ParameterSettingDataType setting001;
    setting001.id = 1398;
    setting001.name = UA_STRING( "SETTING1" );
    setting001.parameterName = UA_STRING( "Name of the setting 1 test" );
    setting001.parameterValue = UA_STRING( "Value of the setting 1 test" );

    UA_CRCL_ParameterSettingDataType setting002;
    setting002.id = 357;
    setting002.name = UA_STRING( "SETTING2" );
    setting002.parameterName = UA_STRING( "Name of the setting 2 test" );
    setting002.parameterValue = UA_STRING( "Value of the setting 2 test" );


    UA_CRCL_ParameterSettingDataType *settings3 = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                   &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

    settings3[0] = setting1;
    settings3[1] = setting2;

    command15.parameterSetting = settings3;
    command15.parameterSettingSize = 2;

    UA_CRCLCommandsUnionDataType commandsUnion15;
    commandsUnion15.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORPARAMETERSCOMMAND;
    commandsUnion15.fields.setEndeffectorParametersCommand = command15;



    UA_SetEndeffectorDataType command16;
    command16.commandID = 1234;
    command16.realTimeCommand = true;
    command16.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1015);
    command16.guard = NULL;
    command16.guardSize = 0;
    command16.id = 5678;
    command16.name = UA_STRING( "UA_SetEndeffectorDataType" );

    UA_CRCL_FractionDataType fraction1;
    fraction1.fractionMax = 1.0;
    fraction1.fractionMin = 0.0;
    fraction1.fraction = 0.654;
    command16.setting = fraction1;

    UA_CRCLCommandsUnionDataType commandsUnion16;
    commandsUnion16.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDEFFECTORCOMMAND;
    commandsUnion16.fields.setEndeffectorCommand = command16;



    UA_SetTransAccelDataType command17;
    command17.commandID = 1234;
    command17.realTimeCommand = true;
    command17.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1016);
    command17.guard = NULL;
    command17.guardSize = 0;
    command17.id = 5678;
    command17.name = UA_STRING( "UA_SetTransAccelDataType" );

    UA_CRCL_TransAccelDataType transAccel;
    transAccel.switchField = UA_CRCL_TRANSACCELDATATYPESWITCH_TRANSACCELABSOLUTEDATATYPE;
    UA_CRCL_TransAccelAbsoluteDataType absolAccel;
    absolAccel.id = 835;
    absolAccel.name = UA_STRING( "absolute Accel" );
    absolAccel.setting = 7452.423;
    transAccel.fields.transAccelAbsoluteDataType = absolAccel;
    command17.transAccel = transAccel;

    UA_CRCLCommandsUnionDataType commandsUnion17;
    commandsUnion17.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSACCELCOMMAND;
    commandsUnion17.fields.setTransAccelCommand = command17;



    UA_SetTransSpeedDataType command18;
    command18.commandID = 1234;
    command18.realTimeCommand = true;
    command18.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1017);
    command18.guard = NULL;
    command18.guardSize = 0;
    command18.id = 5678;
    command18.name = UA_STRING( "UA_SetTransSpeedDataType" );

    UA_CRCL_TransSpeedDataType transSpeed;
    transSpeed.switchField = UA_CRCL_TRANSSPEEDDATATYPESWITCH_TRANSSPEEDRELATIVEDATATYPE;
    UA_CRCL_TransSpeedRelativeDataType relSpeed;
    relSpeed.name = UA_STRING( "rel Speed test" );
    relSpeed.id = 634;

    UA_CRCL_FractionDataType fraction;
    fraction.fractionMax = 1.0;
    fraction.fractionMin = 0.0;
    fraction.fraction = 0.654;

    relSpeed.fraction = fraction;
    transSpeed.fields.transSpeedRelativeDataType = relSpeed;
    command18.transSpeed = transSpeed;

    UA_CRCLCommandsUnionDataType commandsUnion18;
    commandsUnion18.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTRANSSPEEDCOMMAND;
    commandsUnion18.fields.setTransSpeedCommand = command18;



    UA_SetRotAccelDataType command19;
    command19.commandID = 1234;
    command19.realTimeCommand = true;
    command19.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1018);
    command19.guard = NULL;
    command19.guardSize = 0;
    command19.id = 5678;
    command19.name = UA_STRING( "UA_SetRotAccelDataType" );

    UA_CRCL_RotAccelDataType rotAccel;
    rotAccel.switchField = UA_CRCL_ROTACCELDATATYPESWITCH_ROTACCELRELATIVEDATATYPE;

    UA_CRCL_RotAccelRelativeDataType relAccel;
    relAccel.name = UA_STRING( "rot rel accel test" );
    relAccel.id = 749;

    UA_CRCL_FractionDataType fraction19;
    fraction19.fractionMax = 1.0;
    fraction19.fractionMin = 0.0;
    fraction19.fraction = 0.123;

    relAccel.fraction = fraction19;

    rotAccel.fields.rotAccelRelativeDataType = relAccel;
    command19.rotAccel = rotAccel;

    UA_CRCLCommandsUnionDataType commandsUnion19;
    commandsUnion19.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTACCELCOMMAND;
    commandsUnion19.fields.setRotAccelCommand = command19;



    UA_SetRotSpeedDataType command20;
    command20.commandID = 1234;
    command20.realTimeCommand = true;
    command20.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1019);
    command20.guard = NULL;
    command20.guardSize = 0;
    command20.id = 5678;
    command20.name = UA_STRING( "UA_SetRotSpeedDataType" );

    UA_CRCL_RotSpeedDataType rotSpeed;
    rotSpeed.switchField = UA_CRCL_ROTSPEEDDATATYPESWITCH_ROTSPEEDRELATIVEDATATYPE;

    UA_CRCL_RotSpeedRelativeDataType relSpeed2;
    relSpeed2.name = UA_STRING( "rot rel Speed test" );
    relSpeed2.id = 634;

    UA_CRCL_FractionDataType fraction22;
    fraction22.fractionMax = 1.0;
    fraction22.fractionMin = 0.0;
    fraction22.fraction = 0.123;

    relSpeed2.fraction = fraction22;

    rotSpeed.fields.rotSpeedRelativeDataType = relSpeed2;
    command20.rotSpeed = rotSpeed;

    UA_CRCLCommandsUnionDataType commandsUnion20;
    commandsUnion20.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETROTSPEEDCOMMAND;
    commandsUnion20.fields.setRotSpeedCommand = command20;



    UA_SetAngleUnitsDataType command21;
    command21.commandID = 1234;
    command21.realTimeCommand = true;
    command21.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1020);
    command21.guard = NULL;
    command21.guardSize = 0;
    command21.id = 5678;
    command21.name = UA_STRING( "UA_SetAngleUnitsDataType" );

    command21.unitName = UA_CRCL_ANGLEUNITENUMDATATYPE_RADIAN;

    UA_CRCLCommandsUnionDataType commandsUnion21;
    commandsUnion21.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETANGLEUNITSCOMMAND;
    commandsUnion21.fields.setAngleUnitsCommand = command21;



    UA_SetEndPoseToleranceDataType command22;
    command22.commandID = 1234;
    command22.realTimeCommand = true;
    command22.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1021);
    command22.guard = NULL;
    command22.guardSize = 0;
    command22.id = 5678;
    command22.name = UA_STRING( "UA_SetEndPoseToleranceDataType" );

    UA_CRCL_PoseToleranceDataType poseTol;
    poseTol.id = 8563;
    poseTol.name = UA_STRING( "pose Tolerance test ");
    poseTol.xAxisTolerance = 865.213;
    poseTol.xPointTolerance = 9764.523;
    poseTol.yPointTolerance = 913.678;
    poseTol.zAxisTolerance = 954.7343;
    poseTol.zPointTolerance = 6452.523;

    command22.tolerance = poseTol;

    UA_CRCLCommandsUnionDataType commandsUnion22;
    commandsUnion22.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETENDPOSETOLERANCECOMMAND;
    commandsUnion22.fields.setEndPoseToleranceCommand = command22;



    UA_SetForceUnitsDataType command23;
    command23.commandID = 1234;
    command23.realTimeCommand = true;
    command23.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1022);
    command23.guard = NULL;
    command23.guardSize = 0;
    command23.id = 5678;
    command23.name = UA_STRING( "UA_SetForceUnitsDataType" );

    command23.unitName = UA_CRCL_FORCEUNITENUMDATATYPE_NEWTON;

    UA_CRCLCommandsUnionDataType commandsUnion23;
    commandsUnion23.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETFORCEUNITSCOMMAND;
    commandsUnion23.fields.setForceUnitsCommand = command23;



    UA_SetIntermediatePoseToleranceDataType command24;
    command24.commandID = 1234;
    command24.realTimeCommand = true;
    command24.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1023);
    command24.guard = NULL;
    command24.guardSize = 0;
    command24.id = 5678;
    command24.name = UA_STRING( "UA_SetIntermediatePoseToleranceDataType" );

    UA_CRCL_PoseToleranceDataType poseTol2;
    poseTol2.id = 8563;
    poseTol2.name = UA_STRING( "pose Tolerance test ");
    poseTol2.xAxisTolerance = 865.213;
    poseTol2.xPointTolerance = 9764.523;
    poseTol2.yPointTolerance = 913.678;
    poseTol2.zAxisTolerance = 954.7343;
    poseTol2.zPointTolerance = 6452.523;

    command24.tolerance = poseTol2;

    UA_CRCLCommandsUnionDataType commandsUnion24;
    commandsUnion24.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETINTERMEDIATEPOSETOLERANCECOMMAND;
    commandsUnion24.fields.setIntermediatePoseToleranceCommand = command24;



    UA_SetLengthUnitsDataType command25;
    command25.commandID = 1234;
    command25.realTimeCommand = true;
    command25.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1024);
    command25.guard = NULL;
    command25.guardSize = 0;
    command25.id = 5678;
    command25.name = UA_STRING( "UA_SetLengthUnitsDataType" );

    command25.unitName = UA_CRCL_LENGTHUNITENUMDATATYPE_METER;

    UA_CRCLCommandsUnionDataType commandsUnion25;
    commandsUnion25.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETLENGTHUNITSCOMMAND;
    commandsUnion25.fields.setLengthUnitsCommand = command25;



    UA_SetMotionCoordinationDataType command26;
    command26.commandID = 1234;
    command26.realTimeCommand = true;
    command26.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1025);
    command26.guard = NULL;
    command26.guardSize = 0;
    command26.id = 5678;
    command26.name = UA_STRING( "UA_SetMotionCoordinationDataType" );

    command26.coordinated = UA_TRUE;

    UA_CRCLCommandsUnionDataType commandsUnion26;
    commandsUnion26.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETMOTIONCOORDINATIONCOMMAND;
    commandsUnion26.fields.setMotionCoordinationCommand = command26;



    UA_SetTorqueUnitsDataType command27;
    command27.commandID = 1234;
    command27.realTimeCommand = true;
    command27.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1026);
    command27.guard = NULL;
    command27.guardSize = 0;
    command27.id = 5678;
    command27.name = UA_STRING( "UA_SetTorqueUnitsDataType" );

    command27.unitName = UA_CRCL_TORQUEUNITENUMDATATYPE_NEWTONMETER;

    UA_CRCLCommandsUnionDataType commandsUnion27;
    commandsUnion27.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_SETTORQUEUNITSCOMMAND;
    commandsUnion27.fields.setTorqueUnitsCommand = command27;



    UA_StopMotionDataType command28;
    command28.commandID = 1234;
    command28.realTimeCommand = true;
    command28.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1027);
    command28.guard = NULL;
    command28.guardSize = 0;
    command28.id = 5678;
    command28.name = UA_STRING( "UA_StopMotionDataType" );

    command28.stopCondition = UA_CRCL_STOPCONDITIONENUMDATATYPE_IMMEDIATE;

    UA_CRCLCommandsUnionDataType commandsUnion28;
    commandsUnion28.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_STOPMOTIONCOMMAND;
    commandsUnion28.fields.stopMotionCommand = command28;



    UA_ConfigureStatusReportDataType command29;
    command29.commandID = 1234;
    command29.realTimeCommand = true;
    command29.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1028);
    command29.guard = NULL;
    command29.guardSize = 0;
    command29.id = 5678;
    command29.name = UA_STRING( "UA_ConfigureStatusReportDataType" );

    command29.reportJointStatuses = true;
    command29.reportPoseStatus = true;
    command29.reportGripperStatus = true;
    command29.reportSettingsStatus = true;
    command29.reportSensorsStatus = true;
    command29.reportGuardsStatus = true;

    UA_CRCLCommandsUnionDataType commandsUnion29;
    commandsUnion29.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_CONFIGURESTATUSREPORTCOMMAND;
    commandsUnion29.fields.configureStatusReportCommand = command29;



    UA_EnableSensorDataType command30;
    command30.commandID = 1234;
    command30.realTimeCommand = true;
    command30.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1029);
    command30.guard = NULL;
    command30.guardSize = 0;
    command30.id = 5678;
    command30.name = UA_STRING( "UA_EnableSensorDataType" );

    command30.sensorID = UA_STRING( "TestSensorName");

    UA_CRCL_ParameterSettingDataType setting101;
    setting101.id = 1398;
    setting101.name = UA_STRING( "SETTING1" );
    setting101.parameterName = UA_STRING( "Name of the setting 1 test" );
    setting101.parameterValue = UA_STRING( "Value of the setting 1 test" );

    UA_CRCL_ParameterSettingDataType setting202;
    setting202.id = 357;
    setting202.name = UA_STRING( "SETTING2" );
    setting202.parameterName = UA_STRING( "Name of the setting 2 test" );
    setting202.parameterValue = UA_STRING( "Value of the setting 2 test" );


    UA_CRCL_ParameterSettingDataType *settings123 = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                   &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);

    settings123[0] = setting101;
    settings123[1] = setting202;

    command30.sensorOption = settings123;
    command30.sensorOptionSize = 2;

    UA_CRCLCommandsUnionDataType commandsUnion30;
    commandsUnion30.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLESENSORCOMMAND;
    commandsUnion30.fields.enableSensorCommand = command30;



    UA_DisableSensorDataType command31;
    command31.commandID = 1234;
    command31.realTimeCommand = true;
    command31.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1030);
    command31.guard = NULL;
    command31.guardSize = 0;
    command31.id = 5678;
    command31.name = UA_STRING( "UA_DisableSensorDataType" );

    command31.sensorID = UA_STRING( "TestSensorID" );

    UA_CRCLCommandsUnionDataType commandsUnion31;
    commandsUnion31.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLESENSORCOMMAND;
    commandsUnion31.fields.disableSensorCommand = command31;



    UA_EnableGripperDataType command32;
    command32.commandID = 1234;
    command32.realTimeCommand = true;
    command32.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1031);
    command32.guard = NULL;
    command32.guardSize = 0;
    command32.id = 5678;
    command32.name = UA_STRING( "UA_EnableGripperDataType" );

    command32.gripperName = UA_STRING( "TestGripperName");

    UA_CRCL_ParameterSettingDataType setting111;
    setting111.id = 1398;
    setting111.name = UA_STRING( "SETTING1" );
    setting111.parameterName = UA_STRING( "Name of the setting 1 test" );
    setting111.parameterValue = UA_STRING( "Value of the setting 1 test" );

    UA_CRCL_ParameterSettingDataType setting222;
    setting222.id = 357;
    setting222.name = UA_STRING( "SETTING2" );
    setting222.parameterName = UA_STRING( "Name of the setting 2 test" );
    setting222.parameterValue = UA_STRING( "Value of the setting 2 test" );

    UA_CRCL_ParameterSettingDataType *settings987 = (UA_CRCL_ParameterSettingDataType *) UA_Array_new(2,
                                                                   &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_PARAMETERSETTINGDATATYPE]);
    settings987[0] = setting111;
    settings987[1] = setting222;

    command32.gripperOption = settings987;
    command32.gripperOptionSize = 2;

    UA_CRCLCommandsUnionDataType commandsUnion32;
    commandsUnion32.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEGRIPPERCOMMAND;
    commandsUnion32.fields.enableGripperCommand = command32;



    UA_DisableGripperDataType command33;
    command33.commandID = 1234;
    command33.realTimeCommand = true;
    command33.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1032);
    command33.guard = NULL;
    command33.guardSize = 0;
    command33.id = 5678;
    command33.name = UA_STRING( "UA_DisableGripperDataType" );

    command33.gripperName = UA_STRING( "TestGripperName");

    UA_CRCLCommandsUnionDataType commandsUnion33;
    commandsUnion33.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEGRIPPERCOMMAND;
    commandsUnion33.fields.disableGripperCommand = command33;



    UA_EnableRobotParameterStatusDataType command34;
    command34.commandID = 1234;
    command34.realTimeCommand = true;
    command34.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1033);
    command34.guard = NULL;
    command34.guardSize = 0;
    command34.id = 5678;
    command34.name = UA_STRING( "UA_EnableRobotParametersStatusDataType" );

    command34.robotParameterName = UA_STRING( "TestParameterName" );

    UA_CRCLCommandsUnionDataType commandsUnion34;
    commandsUnion34.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_ENABLEROBOTPARAMETERSTATUSCOMMAND;
    commandsUnion34.fields.enableRobotParameterStatusCommand = command34;



    UA_DisableRobotParameterStatusDataType command35;
    command35.commandID = 1234;
    command35.realTimeCommand = true;
    command35.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1034);
    command35.guard = NULL;
    command35.guardSize = 0;
    command35.id = 5678;
    command35.name = UA_STRING( "UA_DisableRobotParameterStatusDataType" );

    command35.robotParameterName = UA_STRING( "TestParameterName" );

    UA_CRCLCommandsUnionDataType commandsUnion35;
    commandsUnion35.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_DISABLEROBOTPARAMETERSTATUSCOMMAND;
    commandsUnion35.fields.disableRobotParameterStatusCommand = command35;

    commandsArray[0] = commandsUnion1;
    commandsArray[1] = commandsUnion2;
    commandsArray[2] = commandsUnion3;
    commandsArray[3] = commandsUnion4;
    commandsArray[4] = commandsUnion5;
    commandsArray[5] = commandsUnion6;
    commandsArray[6] = commandsUnion7;
    commandsArray[7] = commandsUnion8;
    commandsArray[8] = commandsUnion9;
    commandsArray[9] = commandsUnion10;
    commandsArray[10] = commandsUnion11;
    commandsArray[11] = commandsUnion12;
    commandsArray[12] = commandsUnion13;
    commandsArray[13] = commandsUnion14;
    commandsArray[14] = commandsUnion15;
    commandsArray[15] = commandsUnion16;
    commandsArray[16] = commandsUnion17;
    commandsArray[17] = commandsUnion18;
    commandsArray[18] = commandsUnion19;
    commandsArray[19] = commandsUnion20;
    commandsArray[20] = commandsUnion21;
    commandsArray[21] = commandsUnion22;
    commandsArray[22] = commandsUnion23;
    commandsArray[23] = commandsUnion24;
    commandsArray[24] = commandsUnion25;
    commandsArray[25] = commandsUnion26;
    commandsArray[26] = commandsUnion27;
    commandsArray[27] = commandsUnion28;
    commandsArray[28] = commandsUnion29;
    commandsArray[29] = commandsUnion30;
    commandsArray[30] = commandsUnion31;
    commandsArray[31] = commandsUnion32;
    commandsArray[32] = commandsUnion33;
    commandsArray[33] = commandsUnion34;
    commandsArray[34] = commandsUnion35;

    skill.cRCLCommands = commandsArray;

    UA_Variant var;
    UA_Variant_init( &var );
    UA_Variant_setScalar( &var, &skill, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE] );

    UA_Client* client = UA_Client_new();
    std::string address = "opc.tcp://localhost:4567";
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );


    retVal |= UA_Client_writeValueAttribute( client, UA_NODEID_NUMERIC(1, 1300), &var);
    REQUIRE( retVal == UA_STATUSCODE_GOOD );

    UA_Client_disconnect( client );

    UA_Variant_init( &var );
    retVal |= UA_Server_readValue(server, UA_NODEID_NUMERIC(1, 1300), &var );

    UA_CRCLSkillDataType* skillAux = (UA_CRCLSkillDataType*)var.data;

    UA_String str;
    UA_String_init( &str );
    UA_print( skillAux, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE], &str );
    std::cout<< str.data << std::endl;

    SAMY::printCRCLSkill( skillAux );

    REQUIRE( retVal == UA_STATUSCODE_GOOD );

    running = false;

    UA_Server_delete( server );

}






UA_Boolean running = true;
static void stopHandler(int sign){
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

TEST_CASE("Server for testing clients against it", "[ServerTest]"){

    SAMYCoreConfig config;
    config.appLoggingLevel = "debug";
    config.serverLoggingLevel = "debug";
    config.logsPath = "";
    config.serverPort = 4567;
    config.encryption = false;
    config.anonymous = true;
    config.pathToRobotsConfig = "";
    config.pathToSkillsConfig = "";
    config.pathToInformationSourcesConfig = "";
    config.pathToDataBaseConfig = "";
    config.appUri = "TEST_SERVER";
    config.appName = "TEST_SERVER";
    config.certificatesPath = "";

    std::shared_ptr<spdlog::logger> logger = SAMY::Logging::LoggerFactory::createLogger("TEST_SERVER",
                                                       config.appLoggingLevel,
                                                       config.logsPath);

    std::shared_ptr<SAMY::OPCUA::OpcUaServer> server = std::make_shared<SAMY::OPCUA::OpcUaServer>( config, logger );

    LockedServer ls = server->getLocked();

    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    retVal |= namespace_crcl_generated( ls.get() );

    std::vector<UA_DataType> typesVector;
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE] );
    typesVector.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE] );

    std::vector<UA_NodeId> outputNodesVector( typesVector.size(), UA_NODEID_NULL );

    UA_VariableAttributes vattr = UA_VariableAttributes_default;
    vattr.valueRank = UA_VALUERANK_SCALAR;
    vattr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Adds one variable node for each command */
    for(int i = 0; i < typesVector.size(); i++ ){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[i].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVector[i].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVector[i].typeId;

        retVal |= UA_Server_addVariableNode( ls.get(),
                                                     UA_NODEID_NUMERIC(1, i+1000),
                                                     UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                     UA_QUALIFIEDNAME(0, const_cast<char*>( typesVector[i].typeName ) ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                     vattr, NULL, &(outputNodesVector[i])
                                                     );
            REQUIRE( retVal == 0 );
    }

    /* Add one CRCLCommandsUnion variable node by each command, so all the commands can be tested */
    for(int i = 0; i < typesVector.size(); i++ ){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeId;

        retVal |= UA_Server_addVariableNode( ls.get(),
                                                     UA_NODEID_NUMERIC(1, i+1200),
                                                     UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                     UA_QUALIFIEDNAME(0, const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE].typeName ) ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                     vattr, NULL, NULL
                                                     );
            REQUIRE( retVal == 0 );
    }

    /* Add a CRCLSkill variable node */
    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName )  );
    vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName ) );
    UA_NodeId_init( &vattr.dataType );
    vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeId;

    retVal |= UA_Server_addVariableNode( ls.get(),
                                                 UA_NODEID_NUMERIC(1, 1300),
                                                 UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                 UA_QUALIFIEDNAME(0, const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE].typeName ) ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                 vattr, NULL, NULL
                                                 );
    REQUIRE( retVal == 0 );

    /* Add a SAMYRobot variable node */
    UA_LocalizedText_init( &vattr.description );
    UA_LocalizedText_init( &vattr.displayName );
    vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE].typeName )  );
    vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE].typeName ) );
    UA_NodeId_init( &vattr.dataType );
    vattr.dataType = UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE].typeId;

    retVal |= UA_Server_addVariableNode( ls.get(),
                                                 UA_NODEID_NUMERIC(1, 1400),
                                                 UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                 UA_QUALIFIEDNAME(0, const_cast<char*>( UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE].typeName ) ),
                                                 UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                 vattr, NULL, NULL
                                                 );
    REQUIRE( retVal == 0 );


    /* Add a Command Parameters variable node */

    std::vector<UA_DataType> typesVectorParams;
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETOPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTOPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE] );
    typesVectorParams.emplace_back( UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE] );

    for(int i = 0; i < typesVectorParams.size(); i++ ){
        UA_LocalizedText_init( &vattr.description );
        UA_LocalizedText_init( &vattr.displayName );
        vattr.description = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVectorParams[i].typeName )  );
        vattr.displayName = UA_LOCALIZEDTEXT("", const_cast<char*>( typesVectorParams[i].typeName ) );
        UA_NodeId_init( &vattr.dataType );
        vattr.dataType = typesVectorParams[i].typeId;

        retVal |= UA_Server_addVariableNode( ls.get(),
                                                     UA_NODEID_NUMERIC(1, i+1500),
                                                     UA_NODEID_NUMERIC( 0, UA_NS0ID_OBJECTSFOLDER ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT ),
                                                     UA_QUALIFIEDNAME(0, const_cast<char*>( typesVectorParams[i].typeName ) ),
                                                     UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                                                     vattr, NULL, NULL
                                                     );
       REQUIRE( retVal == 0 );
    }


    server->init();

    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    while ( running ) {
        server->iterate();
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

 //   UA_Server_delete( ls.get() );

    std::cout << "END TEST 3 ---------------------------------------------------------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds( 1000 ));

    REQUIRE( retVal == 0);




}


