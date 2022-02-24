
import logging
import os
import sys
import time
PACKAGE_PARENT = '..'
SCRIPT_DIR = os.path.dirname(os.path.realpath(os.path.join(os.getcwd(), os.path.expanduser(__file__))))
sys.path.append(os.path.normpath(os.path.join(SCRIPT_DIR, PACKAGE_PARENT)))

from pubsub import pub
import samyplugin.CRCL_DataTypes
#from transform import Transform

class Robot(object):
    # This class represents the robot.

    def __init__(self, host):
        # create a logger for the robot object
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(logging.INFO)
        fh = logging.StreamHandler()
        fh.setFormatter(logging.Formatter("%(levelname)s %(filename)s - %(message)s"))
        self.logger.addHandler(fh)
        self.host = host

        # Subscribe to the CRCL command topics
        pub.subscribe(self.init_canon, "InitCanon")
        pub.subscribe(self.end_canon, "EndCanon")
        pub.subscribe(self.message, "Message")
        pub.subscribe(self.move_to, "MoveTo")
        pub.subscribe(self.move_screw, "MoveScrew")
        pub.subscribe(self.move_through_to, "MoveThroughTo")
        pub.subscribe(self.dwell, "Dwell")
        pub.subscribe(self.actuate_joints, "ActuateJoints")
        pub.subscribe(self.configure_joint_reports, "ConfigureJointReports")
        #pub.subscribe(self.configure_joint_report, "ConfigureJointReport")
        pub.subscribe(self.set_default_joint_positions_tolerances, "SetDefaultJointPositionsTolerances")
        pub.subscribe(self.get_status, "GetStatus")
        pub.subscribe(self.close_tool_changer, "CloseToolChanger")
        pub.subscribe(self.open_tool_changer, "OpenToolChanger")
        pub.subscribe(self.set_robot_parameters, "SetRobotParameters")
        pub.subscribe(self.set_endeffector_parameters, "SetEndeffectorParameters")
        pub.subscribe(self.set_endeffector, "SetEndeffector")
        pub.subscribe(self.set_trans_accel, "SetTransAccel")
        pub.subscribe(self.set_trans_speed, "SetTransSpeed")
        pub.subscribe(self.set_rot_accel, "SetRotAccel")
        pub.subscribe(self.set_rot_speed, "SetRotSpeed")
        pub.subscribe(self.set_angle_units, "SetAngleUnits")
        pub.subscribe(self.set_end_pose_tolerance, "SetEndPoseTolerance")
        pub.subscribe(self.set_force_units, "SetForceUnits")
        pub.subscribe(self.set_intermediate_pose_tolerance, "SetIntermediatePoseTolerance")
        pub.subscribe(self.set_length_units, "SetLengthUnits")
        pub.subscribe(self.set_motion_coordination, "SetMotionCoordination")
        pub.subscribe(self.set_torque_units, "SetTorqueUnits")
        pub.subscribe(self.stop_motion, "StopMotion")
        pub.subscribe(self.configure_status_report, "ConfigureStatusReport")
        pub.subscribe(self.enable_sensor, "EnableSensor")
        pub.subscribe(self.enable_gripper, "EnableGripper")
        pub.subscribe(self.disable_gripper, "DisableGripper")
        pub.subscribe(self.enable_robot_parameter_status, "EnableRobotParameterStatus")
        pub.subscribe(self.disable_sensor, "DisableSensor")
        pub.subscribe(self.disable_robot_parameter_status, "DisableRobotParameterStatus")


    # Add robot specific methods here:

    def init_canon(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="InitCanon", data=data)

    def end_canon(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="EndCanon", data=data)

    def message(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="Message", data=data)

    def move_to(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="MoveTo", data=data)

    def move_screw(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="MoveScrew", data=data)

    def move_through_to(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="MoveThroughTo", data=data)

    def dwell(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="Dwell", data=data)

    def actuate_joints(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="ActuateJoints", data=data)

    def configure_joint_reports(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="ConfigureJointReports", data=data)

    def configure_joint_report(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="ConfigureJointReport", data=data)

    def set_default_joint_positions_tolerances(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetDefaultJointPositionsTolerances", data=data)

    def get_status(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="GetStatus", data=data)

    def close_tool_changer(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="CloseToolChanger", data=data)

    def open_tool_changer(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="OpenToolChanger", data=data)

    def set_robot_parameters(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetRobotParameters", data=data)

    def set_endeffector_parameters(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetEndeffectorParameters", data=data)

    def set_endeffector(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetEndeffector", data=data)

    def set_trans_accel(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetTransAccel", data=data)

    def set_trans_speed(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetTransSpeed", data=data)

    def set_rot_accel(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetRotAccel", data=data)

    def set_rot_speed(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetRotSpeed", data=data)

    def set_angle_units(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetAngleUnits", data=data)

    def set_end_pose_tolerance(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetEndPoseTolerance", data=data)

    def set_force_units(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetForceUnits", data=data)

    def set_intermediate_pose_tolerance(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetIntermediatePoseTolerance", data=data)

    def set_length_units(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetLengthUnits", data=data)

    def set_motion_coordination(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetMotionCoordination", data=data)

    def set_torque_units(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="SetTorqueUnits", data=data)

    def stop_motion(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="StopMotion", data=data)

    def configure_status_report(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="ConfigureStatusReport", data=data)

    def enable_sensor(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="EnableSensor", data=data)

    def enable_gripper(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="EnableGripper", data=data)

    def disable_gripper(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="DisableGripper", data=data)

    def enable_robot_parameter_status(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="EnableRobotParameterStatus", data=data)

    def disable_sensor(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="DisableSensor", data=data)

    def disable_robot_parameter_status(self, data):
        self.logger.info("Sending data to info Source")
        pub.sendMessage("write_information_source", name="DisableRobotParameterStatus", data=data)
