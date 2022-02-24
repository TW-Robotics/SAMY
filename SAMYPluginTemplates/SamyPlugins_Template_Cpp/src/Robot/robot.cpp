#include "robot.h"

Robot::Robot(std::string address_, Signals* signals_, Plugin* plugin_):
    address(address_),
    signals(signals_),
    plugin(plugin_)
    {
        //Set default values
        settings.transSpeedAbsolute.setting = 10;
        settings.transAccelAbsolute.setting = 10;
        settings.lengthUnitName = UA_CRCL_LENGTHUNITENUMDATATYPE_METER;
        settings.rotAccelAbsolute.setting = 1.2;
        settings.rotSpeedAbsolute.setting = 1.2;
    }

int Robot::InitCanon(UA_InitCanonParametersSetDataType* initCanon){
    spdlog::info("Robot: Execute InitCanon command");
    spdlog::info("InitCanon Name: {}", initCanon->name.data);
    return COMMAND_SUCCESS;
}

int Robot::EndCanon(UA_EndCanonParametersSetDataType* endCanon){
    spdlog::info("Robot: Execute EndCanon command");
    spdlog::info("EndCanon Name: {}", endCanon->name.data);
    return COMMAND_SUCCESS;
}

int Robot::Message(UA_MessageParametersSetDataType* message){
    spdlog::info("Robot: Execute Message command");
    spdlog::info("Message Name: {}", message->name.data);
    return COMMAND_SUCCESS;
}

int Robot::MoveTo(UA_MoveToParametersSetDataType* moveTo){
    spdlog::info("Robot: Execute MoveTo command");
    spdlog::info("MoveStraight {}", (bool) moveTo->moveStraight);
    spdlog::info("MoveTo Name: {}", (char*) moveTo->name.data);
    //Test write infoSource
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
    UA_NodeId id = plugin->GetInformationSourceNodeId("SuperPose_0");
    bool ret = WriteInfoSource(&pose1, &UA_TYPES_CRCL[UA_TYPES_CRCL_CRCL_POSEDATATYPE],
                    id, plugin->samy_core_client_read);
    if (ret){
        return COMMAND_SUCCESS;
    } else {
        signals->Halt(); // Tells the SAMYCore that the execution of the skill failed by setting the
                         // state of the skill to halted.
        return COMMAND_ERROR;
    }
}

int Robot::MoveScrew(UA_MoveScrewParametersSetDataType* moveScrew){
    spdlog::info("Robot: Execute MoveScrew command");
    spdlog::info("MoveScrew Name: {}", moveScrew->name.data);
    return COMMAND_SUCCESS;
}

int Robot::MoveThroughTo(UA_MoveThroughToParametersSetDataType* moveThroughTo){
    spdlog::info("Robot: Execute MoveThroughTo command");
    spdlog::info("MoveThroughTo Name: {}", moveThroughTo->name.data);
    return COMMAND_SUCCESS;
}

int Robot::Dwell(UA_DwellParametersSetDataType* dwell){
    spdlog::info("Robot: Execute Dwell command");
    spdlog::info("Dwell Name: {}", dwell->name.data);
    return COMMAND_SUCCESS;
}

int Robot::ActuateJoints(UA_ActuateJointsParametersSetDataType* actuateJoints){
    spdlog::info("Robot: Execute ActuateJoints command");
    spdlog::info("ActuateJoints Name: {}", actuateJoints->name.data);
    return COMMAND_SUCCESS;
}

int Robot::ConfigureJointReports(UA_ConfigureJointReportsParametersSetDataType* configureJointReports){
    spdlog::info("Robot: Execute ConfigureJointReports command");
    spdlog::info("ConfigureJointReports Name: {}", configureJointReports->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetDefaultJointPositionsTolerances(UA_SetDefaultJointPositionsTolerancesParametersSetDataType* setDefaultJointPositionsTolerances){
    spdlog::info("Robot: Execute SetDefaultJointPositionsTolerances command");
    spdlog::info("SetDefaultJointPositionsTolerances Name: {}", setDefaultJointPositionsTolerances->name.data);
    return COMMAND_SUCCESS;
}

int Robot::GetStatus(UA_GetStatusParametersSetDataType* getStatus){
    spdlog::info("Robot: Execute GetStatus command");
    spdlog::info("GetStatus Name: {}", getStatus->name.data);
    return COMMAND_SUCCESS;
}

int Robot::CloseToolChanger(UA_CloseToolChangerParametersSetDataType* closeToolChanger){
    spdlog::info("Robot: Execute CloseToolChanger command");
    spdlog::info("CloseToolChanger Name: {}", closeToolChanger->name.data);
    return COMMAND_SUCCESS;
}

int Robot::OpenToolChanger(UA_OpenToolChangerParametersSetDataType* openToolChanger){
    spdlog::info("Robot: Execute OpenToolChanger command");
    spdlog::info("OpenToolChanger Name: {}", openToolChanger->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetRobotParameters(UA_SetRobotParametersParametersSetDataType* setRobotParameters){
    spdlog::info("Robot: Execute SetRobotParameters command");
    spdlog::info("SetRobotParameters Name: {}", setRobotParameters->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetEndeffectorParameters(UA_SetEndeffectorParametersParametersSetDataType* setEndeffectorParameters){
    spdlog::info("Robot: Execute SetEndeffectorParameters command");
    spdlog::info("SetEndeffectorParameters Name: {}", setEndeffectorParameters->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetEndeffector(UA_SetEndeffectorParametersSetDataType* setEndeffector){
    spdlog::info("Robot: Execute SetEndeffector command");
    spdlog::info("SetEndeffector Name: {}", setEndeffector->name.data);
    spdlog::info("SetEndeffector: Value {:f}",setEndeffector->setting.fraction);
    return COMMAND_SUCCESS;
}

int Robot::SetTransAccel(UA_SetTransAccelParametersSetDataType* setTransAccel){
    spdlog::info("Robot: Execute SetTransAccel command");
    spdlog::info("SetTransAccel Name: {}", setTransAccel->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetTransSpeed(UA_SetTransSpeedParametersSetDataType* setTransSpeed){
    spdlog::info("Robot: Execute SetTransSpeed command");
    spdlog::info("SetTransSpeed Name: {}", setTransSpeed->name.data);
    if (setTransSpeed->transSpeed.switchField == UA_CRCL_TRANSSPEEDDATATYPESWITCH_TRANSSPEEDABSOLUTEDATATYPE){
        settings.transSpeedAbsolute.setting = setTransSpeed->transSpeed.fields.transSpeedAbsoluteDataType.setting;
    } else {
        settings.transSpeedRelative.fraction.fraction = setTransSpeed->transSpeed.fields.transSpeedRelativeDataType.fraction.fraction;
    }
    return COMMAND_SUCCESS;
}

int Robot::SetRotAccel(UA_SetRotAccelParametersSetDataType* setRotAccel){
    spdlog::info("Robot: Execute SetRotAccel command");
    spdlog::info("SetRotAccel Name: {}", setRotAccel->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetRotSpeed(UA_SetRotSpeedParametersSetDataType* setRotSpeed){
    spdlog::info("Robot: Execute SetRotSpeed command");
    spdlog::info("SetRotSpeed Name: {}", setRotSpeed->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetAngleUnits(UA_SetAngleUnitsParametersSetDataType* setAngleUnits){
    spdlog::info("Robot: Execute SetAngleUnits command");
    spdlog::info("SetAngleUnits Name: {}", setAngleUnits->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetEndPoseTolerance(UA_SetEndPoseToleranceParametersSetDataType* setEndPoseTolerance){
    spdlog::info("Robot: Execute SetEndPoseTolerance command");
    spdlog::info("SetEndPoseTolerance Name: {}", setEndPoseTolerance->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetForceUnits(UA_SetForceUnitsParametersSetDataType* setForceUnits){
    spdlog::info("Robot: Execute SetForceUnits command");
    spdlog::info("SetForceUnits Name: {}", setForceUnits->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetIntermediatePoseTolerance(UA_SetIntermediatePoseToleranceParametersSetDataType* setIntermediatePoseTolerance){
    spdlog::info("Robot: Execute SetIntermediatePoseTolerance command");
    spdlog::info("SetIntermediatePoseTolerance Name: {}", setIntermediatePoseTolerance->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetLengthUnits(UA_SetLengthUnitsParametersSetDataType* setLengthUnits){
    spdlog::info("Robot: Execute SetLengthUnits command");
    spdlog::info("SetLengthUnits Name: {}", setLengthUnits->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetMotionCoordination(UA_SetMotionCoordinationParametersSetDataType* setMotionCoordination){
    spdlog::info("Robot: Execute SetMotionCoordination command");
    spdlog::info("SetMotionCoordination Name: {}", setMotionCoordination->name.data);
    return COMMAND_SUCCESS;
}

int Robot::SetTorqueUnits(UA_SetTorqueUnitsParametersSetDataType* setTorqueUnits){
    spdlog::info("Robot: Execute SetTorqueUnits command");
    spdlog::info("SetTorqueUnits Name: {}", setTorqueUnits->name.data);
    return COMMAND_SUCCESS;
}

int Robot::StopMotion(UA_StopMotionParametersSetDataType* stopMotion){
    spdlog::info("Robot: Execute StopMotion command");
    spdlog::info("StopMotion Name: {}", stopMotion->name.data);
    return COMMAND_SUCCESS;
}

int Robot::ConfigureStatusReport(UA_ConfigureStatusReportParametersSetDataType* configureStatusReport){
    spdlog::info("Robot: Execute ConfigureStatusReport command");
    spdlog::info("ConfigureStatusReport Name: {}", configureStatusReport->name.data);
    return COMMAND_SUCCESS;
}

int Robot::EnableSensor(UA_EnableSensorParametersSetDataType* enableSensor){
    spdlog::info("Robot: Execute EnableSensor command");
    spdlog::info("EnableSensor Name: {}", enableSensor->name.data);
    return COMMAND_SUCCESS;
}

int Robot::DisableSensor(UA_DisableSensorParametersSetDataType* disableSensor){
    spdlog::info("Robot: Execute DisableSensor command");
    spdlog::info("DisableSensor Name: {}", disableSensor->name.data);
    return COMMAND_SUCCESS;
}

int Robot::EnableGripper(UA_EnableGripperParametersSetDataType* enableGripper){
    spdlog::info("Robot: Execute EnableGripper command");
    spdlog::info("EnableGripper Name: {}", enableGripper->name.data);
    return COMMAND_SUCCESS;
}

int Robot::DisableGripper(UA_DisableGripperParametersSetDataType* disableGripper){
    spdlog::info("Robot: Execute DisableGripper command");
    spdlog::info("DisableGripper Name: {}", disableGripper->name.data);
    return COMMAND_SUCCESS;
}

int Robot::EnableRobotParameterStatus(UA_EnableRobotParameterStatusParametersSetDataType* enableRobotParameterStatus){
    spdlog::info("Robot: Execute EnableRobotParameterStatus command");
    spdlog::info("EnableRobotParameterStatus Name: {}", enableRobotParameterStatus->name.data);
    return COMMAND_SUCCESS;
}

int Robot::DisableRobotParameterStatus(UA_DisableRobotParameterStatusParametersSetDataType* disableRobotParameterStatus){
    spdlog::info("Robot: Execute DisableRobotParameterStatus command");
    spdlog::info("DisableRobotParameterStatus Name: {}", disableRobotParameterStatus->name.data);
    return COMMAND_SUCCESS;
}
