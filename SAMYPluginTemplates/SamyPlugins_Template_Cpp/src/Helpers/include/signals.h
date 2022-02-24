#ifndef SIGNALS_H
#define SIGNALS_H

#include <boost/signals2.hpp>
#include <namespace_crcl_generated.h>
#include <types_crcl_generated.h>
#include <types_crcl_generated_handling.h>

struct Signals{
    // Signals for CRCL commands
    boost::signals2::signal<int(UA_InitCanonParametersSetDataType*)> InitCanon;
    boost::signals2::signal<int(UA_EndCanonParametersSetDataType*)> EndCanon;
    boost::signals2::signal<int(UA_MessageParametersSetDataType*)> Message;
    boost::signals2::signal<int(UA_MoveToParametersSetDataType*)> MoveTo;
    boost::signals2::signal<int(UA_MoveScrewParametersSetDataType*)> MoveScrew;
    boost::signals2::signal<int(UA_MoveThroughToParametersSetDataType*)> MoveThroughTo;
    boost::signals2::signal<int(UA_DwellParametersSetDataType*)> Dwell;
    boost::signals2::signal<int(UA_ActuateJointsParametersSetDataType*)> ActuateJoints;
    boost::signals2::signal<int(UA_ConfigureJointReportsParametersSetDataType*)> ConfigureJointReports;
//    boost::signals2::signal<int(UA_ConfigureJointReportsParametersSetDataType*)> ConfigureJointReport;
    boost::signals2::signal<int(UA_SetDefaultJointPositionsTolerancesParametersSetDataType*)> SetDefaultJointPositionsTolerances;
    boost::signals2::signal<int(UA_GetStatusParametersSetDataType*)> GetStatus;
    boost::signals2::signal<int(UA_CloseToolChangerParametersSetDataType*)> CloseToolChanger;
    boost::signals2::signal<int(UA_OpenToolChangerParametersSetDataType*)> OpenToolChanger;
    boost::signals2::signal<int(UA_SetRobotParametersParametersSetDataType*)> SetRobotParameters;
    boost::signals2::signal<int(UA_SetEndeffectorParametersParametersSetDataType*)> SetEndeffectorParameters;
    boost::signals2::signal<int(UA_SetEndeffectorParametersSetDataType*)> SetEndeffector;
    boost::signals2::signal<int(UA_SetTransAccelParametersSetDataType*)> SetTransAccel;
    boost::signals2::signal<int(UA_SetTransSpeedParametersSetDataType*)> SetTransSpeed;
    boost::signals2::signal<int(UA_SetRotAccelParametersSetDataType*)> SetRotAccel;
    boost::signals2::signal<int(UA_SetRotSpeedParametersSetDataType*)> SetRotSpeed;
    boost::signals2::signal<int(UA_SetAngleUnitsParametersSetDataType*)> SetAngleUnits;
    boost::signals2::signal<int(UA_SetEndPoseToleranceParametersSetDataType*)> SetEndPoseTolerance;
    boost::signals2::signal<int(UA_SetForceUnitsParametersSetDataType*)> SetForceUnits;
    boost::signals2::signal<int(UA_SetIntermediatePoseToleranceParametersSetDataType*)> SetIntermediatePoseTolerance;
    boost::signals2::signal<int(UA_SetLengthUnitsParametersSetDataType*)> SetLengthUnits;
    boost::signals2::signal<int(UA_SetMotionCoordinationParametersSetDataType*)> SetMotionCoordination;
    boost::signals2::signal<int(UA_SetTorqueUnitsParametersSetDataType*)> SetTorqueUnits;
    boost::signals2::signal<int(UA_StopMotionParametersSetDataType*)> StopMotion;
    boost::signals2::signal<int(UA_ConfigureStatusReportParametersSetDataType*)> ConfigureStatusReport;
    boost::signals2::signal<int(UA_EnableSensorParametersSetDataType*)> EnableSensor;
    boost::signals2::signal<int(UA_DisableSensorParametersSetDataType*)> DisableSensor;
    boost::signals2::signal<int(UA_EnableGripperParametersSetDataType*)> EnableGripper;
    boost::signals2::signal<int(UA_DisableGripperParametersSetDataType*)> DisableGripper;
    boost::signals2::signal<int(UA_EnableRobotParameterStatusParametersSetDataType*)> EnableRobotParameterStatus;
    boost::signals2::signal<int(UA_DisableRobotParameterStatusParametersSetDataType*)> DisableRobotParameterStatus;
    // Signals for skill methods
    boost::signals2::signal<void()> Reset;
    boost::signals2::signal<void(UA_NodeId*)> Start;
    boost::signals2::signal<void()> Halt;
    boost::signals2::signal<void()> Resume;
    boost::signals2::signal<void()> Suspend;
};

#endif
