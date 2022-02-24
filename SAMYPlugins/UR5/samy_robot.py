from pubsub import pub
import yaml
import time
from urx import Robot
import math3d as m3d
import numpy
import logging

class RobotSettings:

    def __init__(self, name):
        self.max_speed = 5.0  # m/s
        self.max_accel = 2.0  # m/s²
        self.max_rot_speed = 3.14
        self.max_rot_accel = 3.14

        self.name = name
        self.lengthUnit = "meter"
        self.angleUnit = "radian"
        self.forceUnit = "newton"
        self.rotSpeed = 2.0
        self.rotAccel = 0.3
        self.transSpeed = 1
        self.transAccel = 0.2
        self.radius = 0.0
        self.workobject = [[-0.060, 0.400, 0.100],[3.14, -3.14, 0]]   # in mm and rad [[-110, 350, 250],[3.14, -3.14, 0]], [[-560, -40, -195], [0, 0, 0]] [[-0.0, 0.350, 0.200],[3.14, -3.14, 0]]
        self.workobject_m3d = m3d.Transform(m3d.Orientation.new_rotation_vector((
            self.workobject[1][0], self.workobject[1][1], self.workobject[1][2])),
            m3d.Vector(self.workobject[0][0], self.workobject[0][1], self.workobject[0][2]))
        #self.tcp = (0, 0, 0, 0, 0, 0)  # (x, y, z, rx, ry, rz)

    def read_global_settings(self, global_settings): # not used anymore
        workobject = global_settings["Workobject"]
        # Write the relevant settings into the RobotSettings member variables
        self.workobject = [[workobject[0], workobject[1], workobject[2]],[workobject[3], workobject[4], workobject[5]]]
        print(self.workobject)
        self.workobject_m3d = m3d.Transform(m3d.Orientation.new_rotation_vector((
            self.workobject[1][0], self.workobject[1][1], self.workobject[1][2])),
            m3d.Vector(self.workobject[0][0], self.workobject[0][1], self.workobject[0][2]))

class SAMY_Robot():
    def __init__(self, global_settings):
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(logging.INFO)
        log_handler = logging.StreamHandler()
        log_handler.setFormatter(logging.Formatter("%(levelname)s %(filename)s - %(message)s"))
        self.logger.addHandler(log_handler)

        self.robot = Robot(global_settings["Address"])
        self.robot_settings = RobotSettings(global_settings["Name"])
        self.global_settings = global_settings
        self.robot_settings.read_global_settings(global_settings)
        # Subscribe to Topics
        self.logger.info("Subscribing to topics")
        pub.subscribe(self.popup, "Message")
        pub.subscribe(self.move_to, "MoveTo")
        pub.subscribe(self.move_through_to, "MoveThroughTo")
        pub.subscribe(self.dwell, "Dwell")
        pub.subscribe(self.send_status, "GetStatus")
        pub.subscribe(self.set_end_effector, "SetEndeffector")
        pub.subscribe(self.set_trans_accel, "SetTransAccel")
        pub.subscribe(self.set_trans_speed, "SetTransSpeed")
        #pub.subscribe(self.set_length_units, "SetLengthUnits")
        pub.subscribe(self.stop_robot, "StopMotion")

    def popup(self, data):
        self.robot.send_message(str(data.Message))

    def move_to(self, data):
        self.logger.info("Got MoveTo")
        trans = self.crcl_pose_to_m3d_pose(data.EndPosition)

        if data.MoveStraight:
            command = "movel"
        else:
            command = "movej"
        self.robot.set_pose(trans, acc=self.robot_settings.transAccel, vel=self.robot_settings.transSpeed, wait=True, command=command, threshold=None)

    def move_through_to(self, data):
        self.logger.info("Not supported")

    def dwell(self, data):
        """ Sleep for an amount of time.
            Input parameters:
                dwell_time: time the robot waits
        """
        line = "sleep({})\n".format(data.DwellTime)
        self.robot.send_program(line)

    def send_status(self, data):
        self.logger.info("Not supported")

    def set_end_effector(self, data):
        if data.Setting.fraction == 0.0:
            self.robot.open_gripper()
            self.logger.info("Opening Gripper")
        else:
            self.robot.close_gripper()
            if self.robot.holds_object():
                self.logger.info("Gripper is holding an Object.")
                pub.sendMessage("write_information_source", name="GripperHoldsObject", data=True)
            else:
                self.logger.info("Gripper is empty. ")
                pub.sendMessage("write_information_source", name="GripperHoldsObject", data=False)
                #pub.sendMessage("command_halt")
                #time.sleep(1)
                #pub.sendMessage("command_reset")

    def set_trans_accel(self, data):
        if data.TransAccel.switchField == 1:
            self.robot_settings.transAccel = data.TransAccel.unionValue.setting
        else:
            self.logger.info("Setting transAccel as fraction is not supported")

    def set_trans_speed(self, data):
        if data.TransSpeed.switchField == 1:
            self.robot_settings.transSpeed = data.TransSpeed.unionValue.setting
        else:
            self.logger.info("Setting transSpeed as fraction is not supported")

    def stop_robot(self, data):
        self.robot.stop()


    def crcl_pose_to_m3d_pose(self, crcl_pose):
        xaxis = numpy.array([crcl_pose.xAxis.i, crcl_pose.xAxis.j, crcl_pose.xAxis.k])
        zaxis = numpy.array([crcl_pose.zAxis.i, crcl_pose.zAxis.j, crcl_pose.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        trans = m3d.Transform()
        trans.pos.x = (crcl_pose.point.x + self.robot_settings.workobject_m3d.pos.x)
        trans.pos.y = (crcl_pose.point.y + self.robot_settings.workobject_m3d.pos.y)
        trans.pos.z = (crcl_pose.point.z + self.robot_settings.workobject_m3d.pos.z)
        trans.orient[0][0] = crcl_pose.xAxis.i
        trans.orient[0][1] = crcl_pose.xAxis.j
        trans.orient[0][2] = crcl_pose.xAxis.k

        trans.orient[1][0] = yaxis[0]
        trans.orient[1][1] = yaxis[1]
        trans.orient[1][2] = yaxis[2]

        trans.orient[2][0] = crcl_pose.zAxis.i
        trans.orient[2][1] = crcl_pose.zAxis.j
        trans.orient[2][2] = crcl_pose.zAxis.k

        return trans
