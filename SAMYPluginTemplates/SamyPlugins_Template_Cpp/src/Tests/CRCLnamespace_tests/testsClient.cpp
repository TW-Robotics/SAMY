//#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
/* Files namespace_foo_flt_generated.h and namespace_foo_flt_generated.c are created from FooFlt.NodeSet2.xml in the
 * /src_generated directory by CMake */
#include <thread>
#include <signal.h>
#include <iostream>
#include <chrono>
#include <open62541/plugin/log_stdout.h>
#include <namespace_crcl_generated.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_config_default.h>

#define SAMYCORE_ADDRESS_STRING "opc.tcp://localhost:4567"

TEST_CASE("Test client - Write commands", "[WriteCommands]"){

    UA_Client* client = UA_Client_new();
    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes{NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    SECTION("UA_InitCanonDataType"){
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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1000), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1001), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MessageDataType"){
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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1002), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveToDataType"){
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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1003), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveScrewDataType"){
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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1004), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1005), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1006), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1007), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1008), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1009), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1010), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1011), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1012), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1013), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1014), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1015), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1016), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1017), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1018), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1019), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1020), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1021), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1022), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1023), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1024), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1025), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1026), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1027), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1028), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1029), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1030), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1031), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1032), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1033), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1034), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}



TEST_CASE("Test client - Read commands", "[ReadCommands]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
  //  UA_DataTypeArray customDataTypes{NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};
    UA_DataTypeArray customDataTypes{NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};

    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    SECTION("UA_InitCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1000), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_InitCanonDataType* command;
        command = (UA_InitCanonDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EndCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1001), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EndCanonDataType* command;
        command = (UA_EndCanonDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MessageDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1002), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MessageDataType* command;
        command = (UA_MessageDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1003), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveToDataType* command;
        command = (UA_MoveToDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveScrewDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1004), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveScrewDataType* command;
        command = (UA_MoveScrewDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveThroughToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1005), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveThroughToDataType* command;
        command = (UA_MoveThroughToDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DwellDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1006), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DwellDataType* command;
        command = (UA_DwellDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ActuateJointsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1007), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ActuateJointsDataType* command;
        command = (UA_ActuateJointsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureJointReportsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1008), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ConfigureJointReportsDataType* command;
        command = (UA_ConfigureJointReportsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetDefaultJointPositionsTolerancesDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1009), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetDefaultJointPositionsTolerancesDataType* command;
        command = (UA_SetDefaultJointPositionsTolerancesDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_GetStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1010), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_GetStatusDataType* command;
        command = (UA_GetStatusDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_CloseToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1011), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CloseToolChangerDataType* command;
        command = (UA_CloseToolChangerDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_OpenToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1012), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_OpenToolChangerDataType* command;
        command = (UA_OpenToolChangerDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRobotParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1013), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRobotParametersDataType* command;
        command = (UA_SetRobotParametersDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1014), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorParametersDataType* command;
        command = (UA_SetEndeffectorParametersDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1015), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorDataType* command;
        command = (UA_SetEndeffectorDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1016), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTransAccelDataType* command;
        command = (UA_SetTransAccelDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1017), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTransSpeedDataType* command;
        command = (UA_SetTransSpeedDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1018), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRotAccelDataType* command;
        command = (UA_SetRotAccelDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1019), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRotSpeedDataType* command;
        command = (UA_SetRotSpeedDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetAngleUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1020), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetAngleUnitsDataType* command;
        command = (UA_SetAngleUnitsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndPoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1021), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndPoseToleranceDataType* command;
        command = (UA_SetEndPoseToleranceDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetForceUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1022), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetForceUnitsDataType* command;
        command = (UA_SetForceUnitsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetIntermediatePoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1023), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetIntermediatePoseToleranceDataType* command;
        command = (UA_SetIntermediatePoseToleranceDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetLengthUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1024), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetLengthUnitsDataType* command;
        command = (UA_SetLengthUnitsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetMotionCoordinationDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1025), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetMotionCoordinationDataType* command;
        command = (UA_SetMotionCoordinationDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTorqueUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1026), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTorqueUnitsDataType* command;
        command = (UA_SetTorqueUnitsDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_StopMotionDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1027), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_StopMotionDataType* command;
        command = (UA_StopMotionDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureStatusReportDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1028), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ConfigureStatusReportDataType* command;
        command = (UA_ConfigureStatusReportDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1029), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableSensorDataType* command;
        command = (UA_EnableSensorDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1030), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableSensorDataType* command;
        command = (UA_DisableSensorDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1031), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableGripperDataType* command;
        command = (UA_EnableGripperDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1032), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableGripperDataType* command;
        command = (UA_DisableGripperDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1033), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableRobotParameterStatusDataType* command;
        command = (UA_EnableRobotParameterStatusDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1034), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableRobotParameterStatusDataType* command;
        command = (UA_DisableRobotParameterStatusDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}


TEST_CASE("Test client - Write all commands in CRCLCommandsUnion", "[WriteCommandsInCRCLCommandsUnion]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

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
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1200), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1201), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MessageDataType"){
        UA_MessageDataType command;
        command.commandID = 1234;
        command.realTimeCommand = true;
        command.realTimeParameterNode = UA_NODEID_NUMERIC( 1, 1002);
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1202), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveToDataType"){
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

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVETOCOMMAND;
        commandsUnion.fields.moveToCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1203), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveScrewDataType"){
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

        UA_CRCLCommandsUnionDataType commandsUnion;
        commandsUnion.switchField = UA_CRCLCOMMANDSUNIONDATATYPESWITCH_MOVESCREWCOMMAND;
        commandsUnion.fields.moveScrewCommand = command;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &commandsUnion, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLCOMMANDSUNIONDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1204), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1205), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1206), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1207), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1208), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1209), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1210), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1211), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1212), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1213), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1214), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1215), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1216), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1217), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1218), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1219), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1220), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1221), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1222), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1223), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1224), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1225), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1226), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1227), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1228), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1229), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1230), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1231), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1232), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1233), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
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
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1234), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}


TEST_CASE("Test client - Read all commands from CRCLCommandsUnion", "[ReadCommandsFromCRCLCommandsUnion]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    SECTION("UA_InitCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1200), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_InitCanonDataType command;
        command = commandsUnion->fields.initCanonCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EndCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1201), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_EndCanonDataType command;
        command = commandsUnion->fields.endCanonCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MessageDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1202), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_MessageDataType command;
        command = commandsUnion->fields.messageCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1203), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_MoveToDataType command;
        command = commandsUnion->fields.moveToCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETODATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveScrewDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1204), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_MoveScrewDataType command;
        command = commandsUnion->fields.moveScrewCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveThroughToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1205), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_MoveThroughToDataType command;
        command = commandsUnion->fields.moveThroughToCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTODATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DwellDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1206), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_DwellDataType command;
        command = commandsUnion->fields.dwellCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ActuateJointsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1207), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_ActuateJointsDataType command;
        command = commandsUnion->fields.actuateJointsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureJointReportsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1208), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_ConfigureJointReportsDataType command;
        command = commandsUnion->fields.configureJointReportsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetDefaultJointPositionsTolerancesDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1209), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetDefaultJointPositionsTolerancesDataType command;
        command = commandsUnion->fields.setDefaultJointPositionsTolerancesCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_GetStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1210), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_GetStatusDataType command;
        command = commandsUnion->fields.getStatusCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_CloseToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1211), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_CloseToolChangerDataType command;
        command = commandsUnion->fields.closeToolChangerCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_OpenToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1212), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_OpenToolChangerDataType command;
        command = commandsUnion->fields.openToolChangerCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRobotParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1213), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetRobotParametersDataType command;
        command = commandsUnion->fields.setRobotParametersCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1214), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetEndeffectorParametersDataType command;
        command = commandsUnion->fields.setEndeffectorParametersCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1215), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetEndeffectorDataType command;
        command = commandsUnion->fields.setEndeffectorCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1216), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetTransAccelDataType command;
        command = commandsUnion->fields.setTransAccelCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1217), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetTransSpeedDataType command;
        command = commandsUnion->fields.setTransSpeedCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1218), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetRotAccelDataType command;
        command = commandsUnion->fields.setRotAccelCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1219), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetRotSpeedDataType command;
        command = commandsUnion->fields.setRotSpeedCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetAngleUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1220), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetAngleUnitsDataType command;
        command = commandsUnion->fields.setAngleUnitsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndPoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1221), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetEndPoseToleranceDataType command;
        command = commandsUnion->fields.setEndPoseToleranceCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetForceUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1222), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetForceUnitsDataType command;
        command = commandsUnion->fields.setForceUnitsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetIntermediatePoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1223), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetIntermediatePoseToleranceDataType command;
        command = commandsUnion->fields.setIntermediatePoseToleranceCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetLengthUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1224), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetLengthUnitsDataType command;
        command = commandsUnion->fields.setLengthUnitsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetMotionCoordinationDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1225), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetMotionCoordinationDataType command;
        command = commandsUnion->fields.setMotionCoordinationCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTorqueUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1226), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_SetTorqueUnitsDataType command;
        command = commandsUnion->fields.setTorqueUnitsCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_StopMotionDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1227), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_StopMotionDataType command;
        command = commandsUnion->fields.stopMotionCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureStatusReportDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1228), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_ConfigureStatusReportDataType command;
        command = commandsUnion->fields.configureStatusReportCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1229), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_EnableSensorDataType command;
        command = commandsUnion->fields.enableSensorCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1230), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_DisableSensorDataType command;
        command = commandsUnion->fields.disableSensorCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1231), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_EnableGripperDataType command;
        command = commandsUnion->fields.enableGripperCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1232), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_DisableGripperDataType command;
        command = commandsUnion->fields.disableGripperCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1233), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_EnableRobotParameterStatusDataType command;
        command = commandsUnion->fields.enableRobotParameterStatusCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1234), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CRCLCommandsUnionDataType* commandsUnion = (UA_CRCLCommandsUnionDataType*)var.data;

        UA_DisableRobotParameterStatusDataType command;
        command = commandsUnion->fields.disableRobotParameterStatusCommand;
        UA_String str;
        UA_String_init( &str );
        UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}


static void print_bytes(const void *object, size_t size)
{
#ifdef __cplusplus
  const unsigned char * const bytes = static_cast<const unsigned char *>(object);
#else // __cplusplus
  const unsigned char * const bytes = object;
#endif // __cplusplus

  size_t i;

  printf("[ ");
  for(i = 0; i < size; i++)
  {
    printf("%02x ", bytes[i]);
  }
  printf("]\n");
}


TEST_CASE("Test client - Write CRCLSkill with all the commands", "[WriteCRCLSkill]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

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
    UA_StatusCode retVal = UA_STATUSCODE_GOOD;
    retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1300), &var);

  //  print_bytes( &var.data, sizeof(*var.data));
    REQUIRE( retVal == UA_STATUSCODE_GOOD );

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}



TEST_CASE("Test client - Read CRCLSkill", "[ReadCRCLSkill]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    UA_Variant var;
    UA_Variant_init( &var );
    retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1300), &var);

    REQUIRE( retval == UA_STATUSCODE_GOOD );

    UA_CRCLSkillDataType* skill = (UA_CRCLSkillDataType*)var.data;
    UA_String str;
    UA_String_init( &str );
    UA_print( skill, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCLSKILLDATATYPE], &str );
    std::cout << str.data << std::endl;
    UA_String_clear( &str );

    UA_ActuateJointsDataType command;
    command = skill->cRCLCommands[7].fields.actuateJointsCommand;
    UA_String_init( &str );
    UA_print( &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSDATATYPE], &str );
    std::cout << str.data << std::endl;
    UA_String_clear( &str );

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );

}

TEST_CASE("Test client - Read Robot", "[ReadRobot]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    UA_Variant var;
    UA_Variant_init( &var );
    retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1400), &var);

    REQUIRE( retval == UA_STATUSCODE_GOOD );

    UA_SAMYRobotDataType* robot = (UA_SAMYRobotDataType*)var.data;
    UA_String str;
    UA_String_init( &str );
    UA_print( robot, &UA_TYPES_CRCL[UA_TYPES_CRCL_SAMYROBOTDATATYPE], &str );
    std::cout << str.data << std::endl;
    UA_String_clear( &str );

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );

}

TEST_CASE("Test client - Write commands parameters", "[WriteCommandsParameters]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customParametersSetDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customParametersSetDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    SECTION("UA_InitCanonParametersSetDataType"){
        UA_InitCanonParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_InitCanonParametersSetDataType");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1500), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EndCanonParametersSetDataType"){
        UA_EndCanonParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_EndCanonParametersSetDataType");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1501), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MessageParametersSetDataType"){
        UA_MessageParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_MessageParametersSetDataType");

        command.message = UA_STRING( "TEST MESSAGE!" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1502), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveToParametersSetDataType"){
        UA_MoveToParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_MoveToParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETOPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1503), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveScrewParametersSetDataType"){
        UA_MoveScrewParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_MoveScrewParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1504), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_MoveThroughToParametersSetDataType"){
        UA_MoveThroughToParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_MoveThroughToParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTOPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1505), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DwellParametersSetDataType"){
        UA_DwellParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_DwellParametersSetDataType");

        command.dwellTime = 101.101;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1506), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ActuateJointsParametersSetDataType"){
        UA_ActuateJointsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_ActuateJointsParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1507), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ConfigureJointReportsParametersSetDataType"){
        UA_ConfigureJointReportsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_ConfigureJointReportsParametersSetDataType");

        UA_CRCL_ConfigureJointReportDataType conf1;
        conf1.id = 9213;
        conf1.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportParametersSetDataType 1" );
        conf1.jointNumber = 2;
        conf1.reportPosition = UA_TRUE;
        conf1.reportTorqueOrForce = UA_FALSE;
        conf1.reportVelocity = UA_TRUE;

        UA_CRCL_ConfigureJointReportDataType conf2;
        conf2.id = 9213;
        conf2.name = UA_STRING( "name testing UA_CRCL_ConfigureJointReportParametersSetDataType 2" );
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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1508), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetDefaultJointPositionsTolerancesParametersSetDataType"){
        UA_SetDefaultJointPositionsTolerancesParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetDefaultJointPositionsTolerancesParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1509), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_GetStatusParametersSetDataType"){
        UA_GetStatusParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_GetStatusParametersSetDataType");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1510), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_CloseToolChangerParametersSetDataType"){
        UA_CloseToolChangerParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_CloseToolChangerParametersSetDataType");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1511), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_OpenToolChangerParametersSetDataType"){
        UA_OpenToolChangerParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_OpenToolChangerParametersSetDataType");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1512), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRobotParametersParametersSetDataType"){
        UA_SetRobotParametersParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetRobotParametersParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1513), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndeffectorParametersParametersSetDataType"){
        UA_SetEndeffectorParametersParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetEndeffectorParametersParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1514), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndeffectorParametersSetDataType"){
        UA_SetEndeffectorParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetEndeffectorParametersSetDataType");

        UA_CRCL_FractionDataType fraction;
        fraction.fractionMax = 1.0;
        fraction.fractionMin = 0.0;
        fraction.fraction = 0.654;
        command.setting = fraction;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1515), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTransAccelParametersSetDataType"){
        UA_SetTransAccelParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetTransAccelParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1516), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTransSpeedParametersSetDataType"){
        UA_SetTransSpeedParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetTransSpeedParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1517), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRotAccelParametersSetDataType"){
        UA_SetRotAccelParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetRotAccelParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1518), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetRotSpeedParametersSetDataType"){
        UA_SetRotSpeedParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetRotSpeedParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1519), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetAngleUnitsParametersSetDataType"){
        UA_SetAngleUnitsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetAngleUnitsParametersSetDataType");

        command.unitName = UA_CRCL_ANGLEUNITENUMDATATYPE_RADIAN;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1520), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetEndPoseToleranceParametersSetDataType"){
        UA_SetEndPoseToleranceParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetEndPoseToleranceParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1521), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetForceUnitsParametersSetDataType"){
        UA_SetForceUnitsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetForceUnitsParametersSetDataType");

        command.unitName = UA_CRCL_FORCEUNITENUMDATATYPE_NEWTON;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1522), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetIntermediatePoseToleranceParametersSetDataType"){
        UA_SetIntermediatePoseToleranceParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetIntermediatePoseToleranceParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1523), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetLengthUnitsParametersSetDataType"){
        UA_SetLengthUnitsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetLengthUnitsParametersSetDataType");

        command.unitName = UA_CRCL_LENGTHUNITENUMDATATYPE_METER;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1524), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetMotionCoordinationParametersSetDataType"){
        UA_SetMotionCoordinationParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetMotionCoordinationParametersSetDataType");

        command.coordinated = UA_TRUE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1525), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_SetTorqueUnitsParametersSetDataType"){
        UA_SetTorqueUnitsParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_SetTorqueUnitsParametersSetDataType");

        command.unitName = UA_CRCL_TORQUEUNITENUMDATATYPE_NEWTONMETER;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1526), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_StopMotionParametersSetDataType"){
        UA_StopMotionParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_StopMotionParametersSetDataType");

        command.stopCondition = UA_CRCL_STOPCONDITIONENUMDATATYPE_IMMEDIATE;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1527), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_ConfigureStatusReportParametersSetDataType"){
        UA_ConfigureStatusReportParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_ConfigureStatusReportParametersSetDataType");

        command.reportJointStatuses = true;
        command.reportPoseStatus = true;
        command.reportGripperStatus = true;
        command.reportSettingsStatus = true;
        command.reportSensorsStatus = true;
        command.reportGuardsStatus = true;

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1528), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableSensorParametersSetDataType"){
        UA_EnableSensorParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_EnableSensorParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1529), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DisableSensorParametersSetDataType"){
        UA_DisableSensorParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_DisableSensorParametersSetDataType");

        command.sensorID = UA_STRING( "TestSensorID" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1530), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableGripperParametersSetDataType"){
        UA_EnableGripperParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_EnableGripperParametersSetDataType");

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
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1531), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_DisableGripperParametersSetDataType"){
        UA_DisableGripperParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_DisableGripperParametersSetDataType");

        command.gripperName = UA_STRING( "TestGripperName");

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1532), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }
    SECTION("UA_EnableRobotParameterStatusParametersSetDataType"){
        UA_EnableRobotParameterStatusParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_EnableRobotParameterStatusParametersSetDataType");

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1533), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );    }
    SECTION("UA_DisableRobotParameterStatusParametersSetDataType"){
        UA_DisableRobotParameterStatusParametersSetDataType command;

        command.realTimeParameter = true;
        command.name = UA_STRING("UA_DisableRobotParameterStatusParametersSetDataType");

        command.robotParameterName = UA_STRING( "TestParameterName" );

        UA_Variant var;
        UA_Variant_init( &var );
        UA_Variant_setScalar( &var, &command, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE] );
        UA_StatusCode retVal = UA_STATUSCODE_GOOD;
        retVal |= UA_Client_writeValueAttribute(client, UA_NODEID_NUMERIC(1, 1534), &var);
        REQUIRE( retVal == UA_STATUSCODE_GOOD );
    }

    retval |= UA_Client_disconnect( client );
    REQUIRE( retval == UA_STATUSCODE_GOOD );
}





TEST_CASE("Test client - Read commandParameterss parameters", "[ReadcommandParameterssParameters]"){

    UA_Client* client = UA_Client_new();

    std::string address = SAMYCORE_ADDRESS_STRING;
    UA_DataTypeArray customDataTypes = {NULL, UA_TYPES_CRCL_COUNT, UA_TYPES_CRCL};


    UA_ClientConfig *cc = UA_Client_getConfig( client );

    UA_ClientConfig_setDefault(cc);
    cc->customDataTypes = &customDataTypes;
    //cc->stateCallback = stateCallback;

    UA_StatusCode retval = UA_Client_connect( client, address.c_str() );

    SECTION("UA_InitCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1500), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_InitCanonParametersSetDataType* commandParameters;
        commandParameters = (UA_InitCanonParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_INITCANONPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EndCanonDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1501), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EndCanonParametersSetDataType* commandParameters;
        commandParameters = (UA_EndCanonParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENDCANONPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MessageDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1502), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MessageParametersSetDataType* commandParameters;
        commandParameters = (UA_MessageParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_MESSAGEPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1503), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveToParametersSetDataType* commandParameters;
        commandParameters = (UA_MoveToParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETOPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveScrewDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1504), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveScrewParametersSetDataType* commandParameters;
        commandParameters = (UA_MoveScrewParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVESCREWPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_MoveThroughToDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1505), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_MoveThroughToParametersSetDataType* commandParameters;
        commandParameters = (UA_MoveThroughToParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_MOVETHROUGHTOPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DwellDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1506), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DwellParametersSetDataType* commandParameters;
        commandParameters = (UA_DwellParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_DWELLPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ActuateJointsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1507), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ActuateJointsParametersSetDataType* commandParameters;
        commandParameters = (UA_ActuateJointsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_ACTUATEJOINTSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureJointReportsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1508), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ConfigureJointReportsParametersSetDataType* commandParameters;
        commandParameters = (UA_ConfigureJointReportsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGUREJOINTREPORTSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetDefaultJointPositionsTolerancesDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1509), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetDefaultJointPositionsTolerancesParametersSetDataType* commandParameters;
        commandParameters = (UA_SetDefaultJointPositionsTolerancesParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETDEFAULTJOINTPOSITIONSTOLERANCESPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_GetStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1510), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_GetStatusParametersSetDataType* commandParameters;
        commandParameters = (UA_GetStatusParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_GETSTATUSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_CloseToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1511), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_CloseToolChangerParametersSetDataType* commandParameters;
        commandParameters = (UA_CloseToolChangerParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_CLOSETOOLCHANGERPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_OpenToolChangerDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1512), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_OpenToolChangerParametersSetDataType* commandParameters;
        commandParameters = (UA_OpenToolChangerParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_OPENTOOLCHANGERPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRobotParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1513), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRobotParametersParametersSetDataType* commandParameters;
        commandParameters = (UA_SetRobotParametersParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROBOTPARAMETERSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorParametersDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1514), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorParametersParametersSetDataType* commandParameters;
        commandParameters = (UA_SetEndeffectorParametersParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndeffectorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1515), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndeffectorParametersSetDataType* commandParameters;
        commandParameters = (UA_SetEndeffectorParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDEFFECTORPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1516), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTransAccelParametersSetDataType* commandParameters;
        commandParameters = (UA_SetTransAccelParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSACCELPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTransSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1517), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTransSpeedParametersSetDataType* commandParameters;
        commandParameters = (UA_SetTransSpeedParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTRANSSPEEDPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotAccelDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1518), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRotAccelParametersSetDataType* commandParameters;
        commandParameters = (UA_SetRotAccelParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTACCELPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetRotSpeedDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1519), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetRotSpeedParametersSetDataType* commandParameters;
        commandParameters = (UA_SetRotSpeedParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETROTSPEEDPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetAngleUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1520), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetAngleUnitsParametersSetDataType* commandParameters;
        commandParameters = (UA_SetAngleUnitsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETANGLEUNITSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetEndPoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1521), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetEndPoseToleranceParametersSetDataType* commandParameters;
        commandParameters = (UA_SetEndPoseToleranceParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETENDPOSETOLERANCEPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetForceUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1522), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetForceUnitsParametersSetDataType* commandParameters;
        commandParameters = (UA_SetForceUnitsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETFORCEUNITSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetIntermediatePoseToleranceDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1523), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetIntermediatePoseToleranceParametersSetDataType* commandParameters;
        commandParameters = (UA_SetIntermediatePoseToleranceParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETINTERMEDIATEPOSETOLERANCEPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetLengthUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1524), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetLengthUnitsParametersSetDataType* commandParameters;
        commandParameters = (UA_SetLengthUnitsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETLENGTHUNITSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetMotionCoordinationDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1525), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetMotionCoordinationParametersSetDataType* commandParameters;
        commandParameters = (UA_SetMotionCoordinationParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETMOTIONCOORDINATIONPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_SetTorqueUnitsDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1526), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_SetTorqueUnitsParametersSetDataType* commandParameters;
        commandParameters = (UA_SetTorqueUnitsParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_SETTORQUEUNITSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_StopMotionDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1527), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_StopMotionParametersSetDataType* commandParameters;
        commandParameters = (UA_StopMotionParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_STOPMOTIONPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_ConfigureStatusReportDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1528), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_ConfigureStatusReportParametersSetDataType* commandParameters;
        commandParameters = (UA_ConfigureStatusReportParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_CONFIGURESTATUSREPORTPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1529), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableSensorParametersSetDataType* commandParameters;
        commandParameters = (UA_EnableSensorParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLESENSORPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableSensorDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1530), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableSensorParametersSetDataType* commandParameters;
        commandParameters = (UA_DisableSensorParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLESENSORPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1531), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableGripperParametersSetDataType* commandParameters;
        commandParameters = (UA_EnableGripperParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEGRIPPERPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableGripperDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1532), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableGripperParametersSetDataType* commandParameters;
        commandParameters = (UA_DisableGripperParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEGRIPPERPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_EnableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1533), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_EnableRobotParameterStatusParametersSetDataType* commandParameters;
        commandParameters = (UA_EnableRobotParameterStatusParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_ENABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
    SECTION("UA_DisableRobotParameterStatusDataType"){
        UA_StatusCode retval = UA_STATUSCODE_GOOD;
        UA_Variant var;
        UA_Variant_init( &var );
        retval |= UA_Client_readValueAttribute( client, UA_NODEID_NUMERIC(1,1534), &var);

        REQUIRE( retval == UA_STATUSCODE_GOOD );

        UA_DisableRobotParameterStatusParametersSetDataType* commandParameters;
        commandParameters = (UA_DisableRobotParameterStatusParametersSetDataType*)var.data;
        UA_String str;
        UA_String_init( &str );
        UA_print( commandParameters, &UA_TYPES_CRCL[UA_TYPES_CRCL_DISABLEROBOTPARAMETERSTATUSPARAMETERSSETDATATYPE], &str );
        std::cout << str.data << std::endl;
        UA_String_clear( &str );
    }
}
