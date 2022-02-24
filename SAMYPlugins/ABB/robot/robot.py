"""
Michael Dawson-Haggerty

abb.py: contains classes and support functions which interact with an ABB Robot running our software stack (RAPID code module SERVER)

For functions which require targets (XYZ positions with quaternion orientation),
targets can be passed as [[XYZ], [Quats]] OR [XYZ, Quats]

"""

import logging
import os
import sys
import time
PACKAGE_PARENT = '..'
SCRIPT_DIR = os.path.dirname(os.path.realpath(os.path.join(os.getcwd(), os.path.expanduser(__file__))))
sys.path.append(os.path.normpath(os.path.join(SCRIPT_DIR, PACKAGE_PARENT)))

from pubsub import pub
import samyplugin.CRCL_DataTypes
from transform import transform
from robot import connection

import json
import ast
import copy


class RobotSettings:

    def __init__(self):
        self.max_speed = 5.0  # m/s
        self.max_accel = 2.0  # m/s
        self.max_rot_speed = 3.14
        self.max_rot_accel = 3.14

        self.lengthUnit = "meters"
        self.angleUnit = "degrees"
        self.forceUnit = "newton"
        self.scale_linear = None; # Will be set at startup according to lengthUnit
        self.scale_angle = None; # Will be set at startup according to angleUnit
        self.rotSpeed = 3.0
        self.rotAccel = 0.4
        self.transSpeed = 0.2
        self.transAccel = 0.3
        self.radius = 0.0
        self.workobject = ((0.015, -0.475, 0.257), (1,0,0,0)) #((971.03, 0, 100), (0, 0, 0, 1)) # [[1.090, 0, -0.070], [1, 0, 0, 0]] # values for printing station
        self.tool = (0, 0, 0, 1, 0, 0, 0) #(116.563, 2.09, 113.7, 0.707106781, 0, 0.707106781, 0)


class Robot:
    def __init__(self, robot_settings):

        # create a logger for the robot object
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(logging.INFO)
        fh = logging.StreamHandler()
        fh.setFormatter(logging.Formatter("%(levelname)s %(filename)s - %(message)s"))
        self.logger.addHandler(fh)
        self.robot_settings = RobotSettings()
        self.connection = connection.Connection(robot_settings["Address"])

        self.state = "STOPPED"
        self.live_mode = True
        self.count = 0

        self.set_unit_linear(self.robot_settings.lengthUnit)
        self.set_unit_angular(self.robot_settings.angleUnit)
        time.sleep(0.2)
        self.set_workobject(self.robot_settings.workobject)
        time.sleep(0.2)
        self.set_tool(self.robot_settings.tool)
        time.sleep(0.2)
        self.set_zone(zone_key='z1', point_motion=False)
        time.sleep(0.2)
        print("Python: Robot finished init")

        # Subscribe to Topics
        pub.subscribe(self.move_to, "MoveTo")
        pub.subscribe(self.move_through_to, "MoveThroughTo")
        pub.subscribe(self.dwell, "Dwell")
        pub.subscribe(self.send_status, "GetStatus")
        pub.subscribe(self.set_end_effector, "SetEndeffector")
        pub.subscribe(self.set_trans_accel, "SetTransAccel")
        pub.subscribe(self.set_trans_speed, "SetTransSpeed")
        pub.subscribe(self.set_length_units, "SetLengthUnits")
        pub.subscribe(self.stop_robot, "StopMotion")


    def move_to(self, data):
        pose = self.get_pose_from_crcl_position(data.EndPosition)
        if data.MoveStraight:
            self.set_cartesian(pose)
            self.logger.info(pose)
            self.compare_pose(pose[0], pose[1], pose[2])
            print("Command with is finished")
        else:
            self.logger.error("Not Implementet jet")

    def move_through_to(self, data):
        self.logger.info("Not Implementet")
        # x = 1
        # if move_straight:
        #     for waypoint in waypoints:
        #         pose = transform.get_pose_euler(waypoint)
        #         if x == num_positions:
        #             robot.rob.movel(command_id, pose, robot.transAccel, robot.transSpeed, 0)
        #         else:
        #             robot.rob.movel(command_id, pose, robot.robot_settings.transAccel, robot.robot_settings.transSpeed,
        #                             robot.robot_settings.radius)
        #         x += 1
        # else:
        #     for waypoint in waypoints:
        #         pose = transform.get_pose_euler(waypoint)
        #         if x == num_positions:
        #             robot.rob.movej_p(command_id, pose, robot.transAccel, robot.transSpeed, 0, 0)
        #         else:
        #             robot.rob.movej_p(command_id, pose, robot.robot_settings.transAccel, robot.robot_settings.transSpeed, 0,
        #                               robot.robot_settings.radius)
        #         x += 1

    def dwell(self, data):
        self.logger.info("Not Implementet")

    def send_status(self, data):
        self.logger.info("Not Implementet")

    def set_end_effector(self, data):
        if data.Setting.fraction > 0.0:
            self.set_do("do1", 1)
        else:
            self.set_do("do1", 0)
        time.sleep(1)

    def set_trans_accel(self, data):
        self.logger.info("Not Implementet")

    def set_trans_speed(self, data):
        if data.TransSpeed.switchField == 1:
            self.set_speed(data.TransSpeed.unionValue.setting)
            robot.robot_settings.transSpeed = data.TransSpeed.unionValue.setting
        else:
            self.logger.info("Setting transSpeed as fraction is not supported")

    def set_length_units(self, data):
        self.set_unit_linear(data.UnitName)

    def stop_robot(self, data):
        self.logger.info("Not Supported")

    # =========================================================
    #                   Helper Methods
    # =========================================================

    def get_pose_from_crcl_position(self, position):
        """
        Get CRCL pose and change its format to simple python list
        and use quaternions for rotation: (units are not changed)
        [x, y, z, r, i, j, k]
        """

        pose = []
        pose.append(position.point.x)
        pose.append(position.point.y)
        pose.append(position.point.z)
        r, i, j, k = transform.matrix_to_quaternion(position.xAxis, position.zAxis)
        pose.append(r)
        pose.append(i)
        pose.append(j)
        pose.append(k)
        return pose

    def get_state(self):
        return self.state
        pass

    def compare_pose(self, x, y, z):
        """
        Compares the goal pose with the current pose. Both have to be in meters.
        """
        if self.live_mode == False:
            return True

        dif_pose = [0.01, 0, 0]
        pose_reached = False
        print("ABB: comparing pose....")
        while not pose_reached:
            x_rob, y_rob, z_rob = self.get_cartesian() # Gets the pose from the robot. Retrun values are in meters
            dif_pose[0] = (abs(x_rob) - abs(x))
            dif_pose[1] = (abs(y_rob) - abs(y))
            dif_pose[2] = (abs(z_rob) - abs(z))
            print("Dif Pose:")
            print(dif_pose)
            if abs(dif_pose[0]) < 0.005 and abs(dif_pose[1]) < 0.005 and abs(dif_pose[2]) < 0.005:
                #print(dif_pose)
                pose_reached = True
                self.logger.info("ABB: Pose reached")
            time.sleep(0.1)
        return pose_reached

    def set_unit_linear(self, linear):
        units_l = {"millimeters": 1.0,
                   "meters": 1000.0,
                   "inches": 25.4}
        self.scale_linear = units_l[linear]

    def set_unit_angular(self, angular):
        units_a = {'degrees': 1.0,
                   'radians': 57.2957795}
        self.scale_angle = units_a[angular]

    def set_cartesian(self, pose):
        """
        Executes a move immediately from the current pose,
        to 'pose', with units of millimeters.
        """
        global move_finished
        x, y, z = 0.0, 0.0, 0.0
        msg = "01 " + self.format_pose(pose)
        print(msg)
        if not self.live_mode:
            return self.buffer_add(pose)
        print("Python: sending move command")
        self.connection.send_opcua(msg)

    def set_joints(self, joints):
        """
        Executes a move immediately, from current joint angles,
        to 'joints', in degrees.
        """
        if len(joints) != 6:
            return False
        msg = "02 "
        for joint in joints:
            msg += format(joint * self.scale_angle, "+08.2f") + " "
            msg += "#"
        return self.connection.send_opcua(msg)

    def get_cartesian(self):
        """
        Returns the current pose of the robot, in millimeters
        """
        pose_string = self.connection.opcua.currentTCP_node.get_value()
        tcp = ast.literal_eval(pose_string)
        return tcp[0][0] / self.scale_linear, tcp[0][1] / self.scale_linear, tcp[0][2] / self.scale_linear

    def get_joints(self):
        """
        Returns the current angles of the robots joints, in degrees.
        """
        msg = "04 #"
        data = self.send(msg).split()
        return [float(s) / self.scale_angle for s in data[2:8]]

    def get_external_axis(self):
        """
        If you have an external axis connected to your robot controller
        (such as a FlexLifter 600, google it), this returns the joint angles
        """
        msg = "05 #"
        data = self.send(msg).split()
        return [float(s) for s in data[2:8]]

    def get_robotinfo(self):
        """
        Returns a robot- unique string, with things such as the
        robot's model number.
        Example output from and IRB 2400:
        ['24-53243', 'ROBOTWARE_5.12.1021.01', '2400/16 Type B']
        """
        msg = "98 #"
        data = str(self.send(msg))[5:].split('*')
        self.logger.debug('get_robotinfo result: %s', str(data))
        return data

    def set_tool(self, tool):
        """
        Sets the tool centerpoint (TCP) of the robot.
        When you command a cartesian move,
        it aligns the TCP frame with the requested frame.

        Offsets are from tool0, which is defined at the intersection of the
        tool flange center axis and the flange face.
        """
        msg = "06 " + self.format_pose(tool)
        print("Python: sending set tool")
        self.connection.send_opcua(msg)

    def load_json_tool(self, file_name):
        # if file_obj.__class__.__name__ == 'str':
        #    file_obj = open(filename, 'rb')
        tool = self.check_coordinates(json.load(file_name))
        self.set_tool(tool)

    def get_tool(self):
        self.logger.debug('get_tool returning: %s', str(self.robot_settings.tool))
        return self.robot_settings.tool

    def set_workobject(self, work_obj):
        """
        The workobject is a local coordinate frame you can define on the robot,
        then subsequent cartesian moves will be in this coordinate frame.
        """
        msg = "07 " + self.format_pose(work_obj)
        print("Python: sending set workobject")
        self.connection.send_opcua(msg)

    def set_speed(self, speed):
        """
        speed: [robot TCP linear speed (mm/s), TCP orientation speed (deg/s),
                external axis linear, external axis orientation]
        """

        if len(speed) != 4: return False
        msg = "08 "
        msg += format(speed[0], "+08.1f") + " "
        msg += format(speed[1], "+08.2f") + " "
        msg += format(speed[2], "+08.1f") + " "
        msg += format(speed[3], "+08.2f") + " #"
        print("Python: sending set speed")
        self.connection.send_opcua(msg)

    def set_zone(self, zone_key='z1', point_motion=True, manual_zone=[]):
        """
        Sets the motion zone of the robot. This can also be thought of as
        the flyby zone, AKA if the robot is going from point A -> B -> C,
        how close do we have to pass by B to get to C

        zone_key: uses values from RAPID handbook (stored here in zone_dict)
        with keys 'z*', you should probably use these

        point_motion: go to point exactly, and stop briefly before moving on

        manual_zone = [pzone_tcp, pzone_ori, zone_ori]
        pzone_tcp: mm, radius from goal where robot tool centerpoint
                   is not rigidly constrained
        pzone_ori: mm, radius from goal where robot tool orientation
                   is not rigidly constrained
        zone_ori: degrees, zone size for the tool reorientation
        """
        zone_dict = {'z0': [.3, .3, .03],
                     'z1': [1, 1, .1],
                     'z5': [5, 8, .8],
                     'z10': [10, 15, 1.5],
                     'z15': [15, 23, 2.3],
                     'z20': [20, 30, 3],
                     'z30': [30, 45, 4.5],
                     'z50': [50, 75, 7.5],
                     'z100': [100, 150, 15],
                     'z200': [200, 300, 30]}
        if point_motion:
            zone = [0, 0, 0]
        elif len(manual_zone) == 3:
            zone = manual_zone
        elif zone_key in zone_dict.keys():
            zone = zone_dict[zone_key]
        else:
            return False

        msg = "09 "
        msg += str(int(point_motion)) + " "
        msg += format(zone[0], "+08.4f") + " "
        msg += format(zone[1], "+08.4f") + " "
        msg += format(zone[2], "+08.4f") + " #"
        print("Python: sending set zone")
        self.connection.send_opcua(msg)

    def buffer_add(self, pose):
        """
        Appends single pose to the remote buffer
        Move will execute at current speed (which you can change between buffer_add calls)
        """
        msg = "30 " + self.format_pose(pose)
        print("Python: sending buffer add")
        self.connection.send_opcua(msg)
        time.sleep(0.01)

    def buffer_set(self, pose_list):
        """
        Adds every pose in pose_list to the remote buffer
        """
        self.clear_buffer()
        for pose in pose_list:
            self.buffer_add(pose)
        if self.buffer_len == len(pose_list):
            self.logger.debug('Successfully added %i poses to remote buffer',
                      len(pose_list))
            return True
        else:
            self.logger.warn('Failed to add poses to remote buffer!')
            self.clear_buffer()
            return False

    def clear_buffer(self):
        msg = "31 #"
        print("Python: sending clear buffer")
        self.connection.send_opcua(msg)
        time.sleep(1)
        return

    def buffer_len(self):
        """
        Returns the length (number of poses stored) of the remote buffer
        """
        msg = "32 #"
        data = self.send(msg).split()
        return int(float(data[2]))

    def buffer_execute(self):
        """
        Immediately execute linear moves to every pose in the remote buffer.
        """
        global move_finished
        msg = "33 #"
        print("Python: sending buffer execute")
        self.connection.send_opcua(msg)
        time.sleep(1)
        command_done = self.opcua.command_done_node.get_value()
        print(command_done)
        print(type(command_done))
        while not command_done:
            command_done = self.opcua.command_done_node.get_value()
            print(command_done)
            print("Python: waiting for robot to finish buffer")
            time.sleep(1)
        print("Python: Buffered commands executed")

    def set_external_axis(self, axis_values):
        if len(axis_values) != 6: return False
        msg = "34 "
        for axis in axis_values:
            msg += format(axis, "+08.2f") + " "
        msg += "#"
        return self.connection.send_opcua(msg)

    def move_circular(self, pose_onarc, pose_end):
        """
        Executes a movement in a circular path from current position,
        through pose_onarc, to pose_end
        """
        msg_0 = "35 " + self.format_pose(pose_onarc)
        msg_1 = "36 " + self.format_pose(pose_end)

        self.connection.send_opcua(msg_0)
        #data = self.send(msg_0).split()
        #if data[1] != '1':
        #    self.logger.warning('move_circular incorrect response, bailing!')
        #    return False
        return self.connection.send_opcua(msg_1)

    def set_do(self, io_name, setting ):
        """
        Set a physical DIO line on the robot.
        For this to work you're going to need to edit the RAPID function
        and fill in the DIO you want this to switch.
        """
        msg = "10 " + io_name + " " + str(int(bool(setting))) + " #"
        self.logger.info(msg)
        return self.connection.send_opcua(msg)

    def format_pose(self, pose):
        """
        Change the format of the pose to the right unit and add the strings so
        RAPID can understand them.
        Input pose: [x, y, z, i, j, k]
        Output: " x+08.1f y+08.1f z+08.1f r+08.5f i+08.5f j+08.5f k+08.5f"
        """
        pose = self.check_coordinates(pose)
        msg = ""
        for cartesian in pose[0]:
            msg += format(cartesian * self.scale_linear, "+08.1f") + " "
        for quaternion in pose[1]:
            msg += format(quaternion, "+08.5f") + " "
        msg += "#"
        return msg

    def close(self):
        #self.sock.shutdown(socket.SHUT_RDWR)
        #self.sock.close()
        self.logger.info('Disconnected from ABB robot.')

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.close()

    def check_coordinates(self, coordinates):
        if (len(coordinates) == 2) and (len(coordinates[0]) == 3) and (len(coordinates[1]) == 4):
            return coordinates
        elif len(coordinates) == 7:
            return [coordinates[0:3], coordinates[3:7]]
        self.logger.warning('Recieved malformed coordinate: %s', str(coordinates))
        raise NameError('Malformed coordinate!')
