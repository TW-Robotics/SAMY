#ifndef ROBOT_H
#define ROBOT_H

#include <signals.h>
#include <string>
#include <iostream>
#include <time.h>

#include "spdlog/spdlog.h"

#include <namespace_crcl_generated.h>
#include <types_crcl_generated_handling.h>
#include <open62541/client_highlevel.h>
#include <plugin.h>

class Robot
{
public:
    Robot(std::string address_, Signals* signals_, Plugin* plugin_);
    ~Robot()=default;

    int InitCanon(UA_InitCanonParametersSetDataType* init);
    int EndCanon(UA_EndCanonParametersSetDataType* endCanon);
    int Message(UA_MessageParametersSetDataType* message);
    int MoveTo(UA_MoveToParametersSetDataType *moveTo);
    int MoveScrew(UA_MoveScrewParametersSetDataType* moveScrew);
    int MoveThroughTo(UA_MoveThroughToParametersSetDataType* moveThroughTo);
    int Dwell(UA_DwellParametersSetDataType* dwell);
    int ActuateJoints(UA_ActuateJointsParametersSetDataType* actuateJoints);
    int ConfigureJointReports(UA_ConfigureJointReportsParametersSetDataType* configureJointReports);
    int SetDefaultJointPositionsTolerances(UA_SetDefaultJointPositionsTolerancesParametersSetDataType* setDefaultJointPositionsTolerances);
    int GetStatus(UA_GetStatusParametersSetDataType* getStatus);
    int CloseToolChanger(UA_CloseToolChangerParametersSetDataType* closeToolChanger);
    int OpenToolChanger(UA_OpenToolChangerParametersSetDataType* openToolChanger);
    int SetRobotParameters(UA_SetRobotParametersParametersSetDataType* setRobotParameters);
    int SetEndeffectorParameters(UA_SetEndeffectorParametersParametersSetDataType* setEndeffectorParameters);
    int SetEndeffector(UA_SetEndeffectorParametersSetDataType* setEndeffector);
    int SetTransAccel(UA_SetTransAccelParametersSetDataType* setTransAccel);
    int SetTransSpeed(UA_SetTransSpeedParametersSetDataType* setTransSpeed);
    int SetRotAccel(UA_SetRotAccelParametersSetDataType* setRotAccel);
    int SetRotSpeed(UA_SetRotSpeedParametersSetDataType* setRotSpeed);
    int SetAngleUnits(UA_SetAngleUnitsParametersSetDataType* setAngleUnits);
    int SetEndPoseTolerance(UA_SetEndPoseToleranceParametersSetDataType* setEndPoseTolerance);
    int SetForceUnits(UA_SetForceUnitsParametersSetDataType* setForceUnits);
    int SetIntermediatePoseTolerance(UA_SetIntermediatePoseToleranceParametersSetDataType* setIntermediatePoseTolerance);
    int SetLengthUnits(UA_SetLengthUnitsParametersSetDataType* setLengthUnits);
    int SetMotionCoordination(UA_SetMotionCoordinationParametersSetDataType* setMotionCoordination);
    int SetTorqueUnits(UA_SetTorqueUnitsParametersSetDataType* setTorqueUnits);
    int StopMotion(UA_StopMotionParametersSetDataType* stopMotion);
    int ConfigureStatusReport(UA_ConfigureStatusReportParametersSetDataType* configureStatusReport);
    int EnableSensor(UA_EnableSensorParametersSetDataType* enableSensor);
    int DisableSensor(UA_DisableSensorParametersSetDataType* disableSensor);
    int EnableGripper(UA_EnableGripperParametersSetDataType* enableGripper);
    int DisableGripper(UA_DisableGripperParametersSetDataType* disableGripper);
    int EnableRobotParameterStatus(UA_EnableRobotParameterStatusParametersSetDataType* enableRobotParameterStatus);
    int DisableRobotParameterStatus(UA_DisableRobotParameterStatusParametersSetDataType* disableRobotParameterStatus);

private:
    Signals* signals;
    std::string address;
    Plugin* plugin;
    UA_CRCL_SettingsStatusDataType settings;
};

#endif // ROBOT_H
