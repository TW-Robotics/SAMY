from pubsub import pub
import samyplugin.CRCL_DataTypes

class Tests():
    def __init__(self):
        self.test_move_to()
        self.test_set_endeffector()
        self.test_enable_gripper("cylinder")
        self.test_enable_gripper("conveyor_parts")
        #self.test_disable_gripper("cylinder")


    def test_move_to(self):
        data = CRCL_DataTypes.MoveToDataType()
        data.MoveStraight = True
        pub.sendMessage("MoveToCommand", data=data)

    def test_set_endeffector(self):
        data = CRCL_DataTypes.SetEndeffectorDataType()
        data.Setting = 1
        pub.sendMessage("SetEndeffectorCommand", data=data)

    def test_enable_gripper(self, name:str):
        data = CRCL_DataTypes.EnableGripperDataType()
        data.GripperName = name
        pub.sendMessage("EnableGripperCommand", data=data)

    def test_disable_gripper(self, name:str):
        data = CRCL_DataTypes.DisableGripperDataType()
        data.GripperName = name
        pub.sendMessage("DisableGripperCommand", data=data)
