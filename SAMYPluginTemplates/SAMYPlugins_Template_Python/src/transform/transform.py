import sys
from copy import deepcopy

sys.path.append('/home/felix/Desktop/SAMY/Git/SAMYPlugins_Templates/SAMYPlugins_Template_Python/src')

import numpy
from opcua import Client

from pytransform3d import rotations
from pytransform3d import transformations
from pytransform3d.transform_manager import TransformManager
import matplotlib.pyplot as plt

from samyplugin.CRCL_DataTypes import *

class Transform():
    def __init__(self):
        self.transform_manager = TransformManager()

    def set_transform_world2robot(self, world2robot_: CRCL_PoseDataType):
        # Convert CRCL pose to pytransform3d transform
        xaxis = numpy.array([world2robot_.xAxis.i, world2robot_.xAxis.j, world2robot_.xAxis.k])
        zaxis = numpy.array([world2robot_.zAxis.i, world2robot_.zAxis.j, world2robot_.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        rot = rotations.matrix_from_two_vectors(xaxis,yaxis)

        world2robot_trans = transformations.transform_from(rot, numpy.array([world2robot_.point.x, world2robot_.point.y, world2robot_.point.z]))
        self.transform_manager.add_transform("robot", "world", world2robot_trans)

    def set_transform_tool(self, trans: CRCL_PoseDataType):
        # TODO test if transformation is done correctly
        xaxis = numpy.array([trans.xAxis.i, trans.xAxis.j, trans.xAxis.k])
        zaxis = numpy.array([trans.zAxis.i, trans.zAxis.j, trans.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        rot = rotations.matrix_from_two_vectors(xaxis, yaxis)

        world2robot_trans = transformations.transform_from(rot, numpy.array(
            [trans.point.x, trans.point.y, trans.point.z]))
        self.transform_manager.add_transform("lastJoint", "tool", world2robot_trans)

    def adjust_pose_for_tool(self, crcl_pose: CRCL_PoseDataType):
        # TODO test if transformation is done correctly
        new_pose = deepcopy(crcl_pose)
        A2B = self.transform_manager.get_transform("lastJoint", "tool")
        new_point = transformations.transform(A2B, numpy.array([crcl_pose.point.x, crcl_pose.point.y, crcl_pose.point.z, 1]))
        new_pose.point.x = new_point[0].item()
        new_pose.point.y = new_point[1].item()
        new_pose.point.z = new_point[2].item()

        xaxis = numpy.array([crcl_pose.xAxis.i, crcl_pose.xAxis.j, crcl_pose.xAxis.k])
        zaxis = numpy.array([crcl_pose.zAxis.i, crcl_pose.zAxis.j, crcl_pose.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        rot_array = numpy.array([xaxis,yaxis,zaxis])
        new_rot_array = numpy.matmul(rot_array, A2B[:3, :3])
        xAxis = CRCL_VectorDataType()
        xAxis.i = new_rot_array[0, 0]
        xAxis.j = new_rot_array[0, 1]
        xAxis.k = new_rot_array[0, 2]
        zAxis = CRCL_VectorDataType()
        zAxis.i = new_rot_array[2, 0]
        zAxis.j = new_rot_array[2, 1]
        zAxis.k = new_rot_array[2, 2]
        new_pose.xAxis = xAxis
        new_pose.zAxis = zAxis

    def transform_crcl_pose(self, crcl_pose: CRCL_PoseDataType, from_c, to_c):
        new_pose = deepcopy(crcl_pose)
        A2B = self.transform_manager.get_transform(from_c, to_c)
        # print(A2B)
        new_point = transformations.transform(A2B, numpy.array([crcl_pose.point.x, crcl_pose.point.y, crcl_pose.point.z, 1]))
        new_pose.point.x = new_point[0].item()
        new_pose.point.y = new_point[1].item()
        new_pose.point.z = new_point[2].item()

        xaxis = numpy.array([crcl_pose.xAxis.i, crcl_pose.xAxis.j, crcl_pose.xAxis.k])
        zaxis = numpy.array([crcl_pose.zAxis.i, crcl_pose.zAxis.j, crcl_pose.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        rot_array = numpy.array([xaxis,yaxis,zaxis])
        new_rot_array = numpy.matmul(rot_array, A2B[:3, :3])
        xAxis = CRCL_VectorDataType()
        xAxis.i = new_rot_array[0, 0]
        xAxis.j = new_rot_array[0, 1]
        xAxis.k = new_rot_array[0, 2]
        zAxis = CRCL_VectorDataType()
        zAxis.i = new_rot_array[2, 0]
        zAxis.j = new_rot_array[2, 1]
        zAxis.k = new_rot_array[2, 2]
        new_pose.xAxis = xAxis
        new_pose.zAxis = zAxis
        return new_pose

    def add_transform(self, trans: CRCL_PoseDataType, from_c, to_c):
        # Convert CRCL pose to pytransform3d transform
        xaxis = numpy.array([trans.xAxis.i, trans.xAxis.j, trans.xAxis.k])
        zaxis = numpy.array([trans.zAxis.i, trans.zAxis.j, trans.zAxis.k])
        yaxis = numpy.cross(zaxis, xaxis)
        rot = rotations.matrix_from_two_vectors(xaxis,yaxis)

        trans_3d = transformations.transform_from(rot, numpy.array([trans.point.x, trans.point.y, trans.point.z]))
        self.transform_manager.add_transform(from_c, to_c, trans_3d)


def print_crcl_pose(pose: CRCL_PoseDataType):
    print("Name: " + str(pose.name) +"\nPoint: x: " + str(pose.point.x) + " y: " + str(pose.point.y) + " z: " + str(pose.point.z) +
          " \nxAxis: i: " + str(pose.xAxis.i) + " j: " + str(pose.xAxis.j) + " k: " + str(pose.xAxis.k) +
          " \nzAxis: i: " + str(pose.zAxis.i) + " j: " + str(pose.zAxis.j) + " k: " + str(pose.zAxis.k))


def plot_crcl_pose(ax, pose: CRCL_PoseDataType):
    xaxis = numpy.array([pose.xAxis.i, pose.xAxis.j, pose.xAxis.k])
    zaxis = numpy.array([pose.zAxis.i, pose.zAxis.j, pose.zAxis.k])
    yaxis = numpy.cross(zaxis, xaxis)
    rot = rotations.matrix_from_two_vectors(xaxis, yaxis)
    offset = numpy.array([pose.point.x, pose.point.y, pose.point.z])
    rotations.plot_basis(ax=ax, R=rot,p=offset, s=1.0)


Testing
if __name__ == "__main__":

    # Connect to SAMYCore to get CRCL DataTypes
    address = "opc.tcp://{}:{}".format("localhost", "4841")
    opcua_core_client = Client(address)
    opcua_core_client.connect()
    opcua_core_client.load_type_definitions()

    # Test Transform class
    world2robot = CRCL_PoseDataType()
    world2robot.name = "Transform"
    world2robot.point.x = 0.5
    world2robot.point.y = 0.3
    world2robot.point.z = 0.0
    world2robot.xAxis.i = 0
    world2robot.xAxis.j = -1
    world2robot.xAxis.k = 0
    world2robot.zAxis.i = 0
    world2robot.zAxis.j = 0
    world2robot.zAxis.k = 1

    grip_pose = CRCL_PoseDataType()
    grip_pose.name = "grip_pose"
    grip_pose.point.x = 0.8
    grip_pose.point.y = 0.6
    grip_pose.point.z = 0.0
    grip_pose.xAxis.i = 1
    grip_pose.xAxis.j = 0
    grip_pose.xAxis.k = 0
    grip_pose.zAxis.i = 0
    grip_pose.zAxis.j = 0
    grip_pose.zAxis.k = 1

    transform = Transform()
    transform.set_transform_world2robot(world2robot)
    grip_pose_robot = transform.transform_crcl_pose(grip_pose, "world", "robot")
    grip_pose_world = transform.transform_crcl_pose(grip_pose_robot, "robot", "world")
    ax = transform.transform_manager.plot_frames_in("robot", s=1.0)

    print_crcl_pose(grip_pose_robot)
    print_crcl_pose(grip_pose_world)
    plot_crcl_pose(ax,grip_pose_robot)
    plot_crcl_pose(ax,grip_pose_world)
    # ax.set_xlim((-0.25, 0.75))
    # ax.set_ylim((-0.5, 0.5))
    # ax.set_zlim((0.0, 1.0))
    plt.tight_layout()
    plt.show()

    opcua_core_client.disconnect()
