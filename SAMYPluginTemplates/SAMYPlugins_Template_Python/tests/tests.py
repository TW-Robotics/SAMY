#from samyplugin import CRCL_DataTypes
import samyplugin.CRCL_DataTypes
import unittest
from testclient import TestClient
from opcua import ua

class TestCommunication(unittest.TestCase):
    def get_namespaces(self, client):
        namespaces = {}
        root = client.client.get_root_node()
        browse_path = ["0:Objects", "0:Server", "0:NamespaceArray"]
        namespaceArrayNode = root.get_child(browse_path)
        namespacesValue = namespaceArrayNode.get_value()
        for i, namespace in enumerate(namespacesValue):
            namespaces[namespace] = i
        return namespaces

    def get_skill_parameter_node_id(self, client, command_name):
        namespaces = self.get_namespaces(client)
        root = client.client.get_root_node()
        ns_robot = namespaces["TestRobot"]
        browse_path = ["0:Objects", "3:DeviceSet", "{}:TestRobot".format(ns_robot), "4:Controllers", "{}:TestRobot".format(ns_robot), "5:Skills"]
        browse_path.append("{}:{}".format(ns_robot, command_name + "Skill"))
        browse_path.append("3:ParameterSet")
        browse_path.append("7:{}".format("0_" + command_name + "Parameters"))
        node_id = root.get_child(browse_path)
        print("skill_parameter_node_id")
        print(node_id)
        return node_id

    def get_skill_id(self, client, command_name):
        namespaces = self.get_namespaces(client)
        root = client.client.get_root_node()
        ns_robot = namespaces["TestRobot"]
        browse_path = ["0:Objects", "3:DeviceSet", "{}:TestRobot".format(ns_robot), "4:Controllers", "{}:TestRobot".format(ns_robot), "5:Skills"]
        browse_path.append("{}:{}".format(ns_robot, command_name + "Skill"))
        node_id = root.get_child(browse_path)
        print("skill_id")
        print(node_id)
        return node_id

    def get_info_source_id(self, client, command_name):
        namespaces = self.get_namespaces(client)
        root = client.client.get_root_node()
        ns_robot = namespaces["TestRobot"]
        browse_path = ["0:Objects", "9:InformationSources", "9:{}".format(command_name), "9:{}".format(command_name + "_0")]
        node_id = root.get_child(browse_path)
        print("info_source_id")
        print(node_id)
        return node_id

##################################### Tests ################################################

    def test_init_canon(self):
        """
        Test if the InitCanon command is send and recived
        """
        data = ua.InitCanonParametersSetDataType()
        test_client = TestClient()
        data.Name = "TestInitCanon"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "InitCanon"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "InitCanon"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "InitCanon"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_end_canon(self):
        """
        Test if the EndCanon command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.EndCanonParametersSetDataType()
        test_client = TestClient()
        data.Name = "TestEndCanon"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "EndCanon"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "EndCanon"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "EndCanon"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_message(self):
        """
        Test if the Message command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.MessageParametersSetDataType()
        test_client = TestClient()
        data.Name = "Message"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "Message"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "Message"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "Message"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_move_to(self):
        """
        Test if the MoveTo command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.MoveToParametersSetDataType()
        test_client = TestClient()
        data.Name = "MoveTo"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "MoveTo"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "MoveTo"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "MoveTo"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_move_screw(self):
        """
        Test if the MoveScrew command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.MoveScrewParametersSetDataType()
        test_client = TestClient()
        data.Name = "MoveScrew"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "MoveScrew"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "MoveScrew"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "MoveScrew"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_move_through_to(self):
        """
        Test if the MoveThroughTo command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.MoveThroughToParametersSetDataType()
        test_client = TestClient()
        data.Name = "MoveThroughTo"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "MoveThroughTo"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "MoveThroughTo"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "MoveThroughTo"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_dwell(self):
        """
        Test if the Dwell command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.DwellParametersSetDataType()
        test_client = TestClient()
        data.Name = "Dwell"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "Dwell"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "Dwell"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "Dwell"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_actuate_joints(self):
        """
        Test if the ActuateJoints command is send and recived
        """
        data = ua.ActuateJointsParametersSetDataType()
        test_client = TestClient()
        data.Name = "ActuateJoints"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "ActuateJoints"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "ActuateJoints"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "ActuateJoints"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_configure_joint_reports(self):
        """
        Test if the ConfigureJointReports command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.ConfigureJointReportsParametersSetDataType()
        test_client = TestClient()
        data.Name = "ConfigureJointReports"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "ConfigureJointReports"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "ConfigureJointReports"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "ConfigureJointReports"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    # def test_configure_joint_report(self):
    #     """
    #     Test if the ConfigureJointReport command is send and recived
    #     """
    #     data = samyplugin.CRCL_DataTypes.ConfigureJointReportParametersSetDataType()
    #     test_client = TestClient()
    #     data.Name = "ConfigureJointReport"
    #     # Send command to Plugin
    #     test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "ConfigureJointReport"), data)
    #     test_client.call_start_method(skill_id=self.get_skill_id(test_client, "ConfigureJointReport"), method_id = ua.NodeId(15095, 5))
    #     # Wait for state is set to ready again
    #     test_client.check_state()
    #     # Read data from information source
    #     return_val = test_client.read_info_source(self.get_info_source_id(test_client, "ConfigureJointReport"))
    #     # Check if name is the same as in data
    #     self.assertEqual(return_val.Name, data.Name)
    #
    #     test_client.disconnect()

    def test_set_default_joint_positions_tolerances(self):
        """
        Test if the SetDefaultJointPositionsTolerances command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetDefaultJointPositionsTolerancesParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetDefaultJointPositionsTolerances"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetDefaultJointPositionsTolerances"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetDefaultJointPositionsTolerances"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetDefaultJointPositionsTolerances"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_get_status(self):
        """
        Test if the GetStatus command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.GetStatusParametersSetDataType()
        test_client = TestClient()
        data.Name = "GetStatus"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "GetStatus"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "GetStatus"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "GetStatus"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_close_tool_changer(self):
        """
        Test if the CloseToolChanger command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.CloseToolChangerParametersSetDataType()
        test_client = TestClient()
        data.Name = "CloseToolChanger"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "CloseToolChanger"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "CloseToolChanger"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "CloseToolChanger"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_open_tool_changer(self):
        """
        Test if the OpenToolChanger command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.OpenToolChangerParametersSetDataType()
        test_client = TestClient()
        data.Name = "OpenToolChanger"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "OpenToolChanger"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "OpenToolChanger"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "OpenToolChanger"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_robot_parameters(self):
        """
        Test if the SetRobotParameters command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetRobotParametersParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetRobotParameters"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetRobotParameters"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetRobotParameters"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetRobotParameters"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_endeffector_parameters(self):
        """
        Test if the SetEndeffectorParameters command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetEndeffectorParametersParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetEndeffectorParameters"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetEndeffectorParameters"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetEndeffectorParameters"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetEndeffectorParameters"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_endeffector(self):
        """
        Test if the SetEndeffector command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetEndeffectorParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetEndeffector"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetEndeffector"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetEndeffector"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetEndeffector"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_trans_accel(self):
        """
        Test if the SetTransAccel command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetTransAccelParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetTransAccel"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetTransAccel"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetTransAccel"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetTransAccel"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_trans_speed(self):
        """
        Test if the SetTransSpeed command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetTransSpeedParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetTransSpeed"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetTransSpeed"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetTransSpeed"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetTransSpeed"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_rot_accel(self):
        """
        Test if the SetRotAccel command is send and recived
        """
        data = ua.SetRotAccelParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetRotAccel"
        data.RotAccel.SwitchField = "CRCL_RotAccelAbsoluteDataType"
        #data.RotAccel.RotAccelAbsoluteDataType.name = "Absolute"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetRotAccel"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetRotAccel"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetRotAccel"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_rot_speed(self):
        """
        Test if the SetRotSpeed command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetRotSpeedParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetRotSpeed"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetRotSpeed"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetRotSpeed"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetRotSpeed"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_angle_units(self):
        """
        Test if the SetAngleUnits command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetAngleUnitsParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetAngleUnits"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetAngleUnits"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetAngleUnits"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetAngleUnits"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_end_pose_tolerance(self):
        """
        Test if the SetEndPoseTolerance command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetEndPoseToleranceParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetEndPoseTolerance"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetEndPoseTolerance"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetEndPoseTolerance"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetEndPoseTolerance"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_force_units(self):
        """
        Test if the SetForceUnits command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetForceUnitsParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetForceUnits"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetForceUnits"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetForceUnits"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetForceUnits"))
        # Check if name is the same as
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_intermediate_pose_tolerance(self):
        """
        Test if the SetIntermediatePoseTolerance command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetIntermediatePoseToleranceParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetIntermediatePoseTolerance"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetIntermediatePoseTolerance"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetIntermediatePoseTolerance"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetIntermediatePoseTolerance"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_length_units(self):
        """
        Test if the SetLengthUnits command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetLengthUnitsParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetLengthUnits"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetLengthUnits"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetLengthUnits"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetLengthUnits"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_motion_coordinationw(self):
        """
        Test if the SetMotionCoordination command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetMotionCoordinationParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetMotionCoordination"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetMotionCoordination"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetMotionCoordination"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetMotionCoordination"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_set_torque_units(self):
        """
        Test if the SetTorqueUnits command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.SetTorqueUnitsParametersSetDataType()
        test_client = TestClient()
        data.Name = "SetTorqueUnits"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "SetTorqueUnits"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "SetTorqueUnits"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "SetTorqueUnits"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_stop_motion(self):
        """
        Test if the StopMotion command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.StopMotionParametersSetDataType()
        test_client = TestClient()
        data.Name = "StopMotion"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "StopMotion"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "StopMotion"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "StopMotion"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_configure_status_report(self):
        """
        Test if the ConfigureStatusReport command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.ConfigureStatusReportParametersSetDataType()
        test_client = TestClient()
        data.Name = "ConfigureStatusReport"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "ConfigureStatusReport"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "ConfigureStatusReport"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "ConfigureStatusReport"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_enable_sensor(self):
        """
        Test if the EnableSensor command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.EnableSensorParametersSetDataType()
        test_client = TestClient()
        data.Name = "EnableSensor"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "EnableSensor"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "EnableSensor"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "EnableSensor"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_enable_gripper(self):
        """
        Test if the EnableGripper command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.EnableGripperParametersSetDataType()
        test_client = TestClient()
        data.Name = "EnableGripper"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "EnableGripper"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "EnableGripper"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "EnableGripper"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_disable_gripper(self):
        """
        Test if the DisableGripper command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.DisableGripperParametersSetDataType()
        test_client = TestClient()
        data.Name = "DisableGripper"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "DisableGripper"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "DisableGripper"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "DisableGripper"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_enable_robot_parameter_status(self):
        """
        Test if the EnableRobotParameterStatus command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.EnableRobotParameterStatusParametersSetDataType()
        test_client = TestClient()
        data.Name = "EnableRobotParameterStatus"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "EnableRobotParameterStatus"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "EnableRobotParameterStatus"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "EnableRobotParameterStatus"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_disable_sensor(self):
        """
        Test if the DisableSensor command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.DisableSensorParametersSetDataType()
        test_client = TestClient()
        data.Name = "DisableSensor"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "DisableSensor"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "DisableSensor"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "DisableSensor"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

    def test_disable_robot_parameter_status(self):
        """
        Test if the DisableRobotParameterStatus command is send and recived
        """
        data = samyplugin.CRCL_DataTypes.DisableRobotParameterStatusParametersSetDataType()
        test_client = TestClient()
        data.Name = "DisableRobotParameterStatus"
        # Send command to Plugin
        test_client.write_crcl_command(self.get_skill_parameter_node_id(test_client, "DisableRobotParameterStatus"), data)
        test_client.call_start_method(skill_id=self.get_skill_id(test_client, "DisableRobotParameterStatus"), method_id = ua.NodeId(15095, 5))
        # Wait for state is set to ready again
        test_client.check_state()
        # Read data from information source
        return_val = test_client.read_info_source(self.get_info_source_id(test_client, "DisableRobotParameterStatus"))
        # Check if name is the same as in data
        self.assertEqual(return_val.Name, data.Name)

        test_client.disconnect()

if __name__=="__main__":
    unittest.main()




# class SamyClient():
#     def __init__(self, robot_name_):
#         self.client = self.connect_to_core("localhost", "4840")
#         self.robot_name = robot_name_
#         # self.test_set_endeffector()
#         # self.test_enable_gripper("cylinder")
#         # self.test_enable_gripper("conveyor_parts")
#         #self.test_disable_gripper("cylinder")
#
#     def get_namespaces(self, client):
#         namespaces = {}
#         root_node = client.get_root_node()
#         browse_path = ["0:Objects", "0:Server", "0:NamespaceArray"]
#         namespaceArrayNode = root_node.get_child(browse_path)
#         namespacesValue = namespaceArrayNode.get_value()
#         for i, namespace in enumerate(namespacesValue):
#             namespaces[namespace] = i
#         return namespaces
#
#     def connect_to_core(self, address_, port_):
#         # Connect to SAMYCore opcua server
#         while True:
#             try:
#                 # Create opcua client connection with SAMYCore
#                 print("Connecting to SAMYCore")
#                 address = ("opc.tcp://{}:{}").format(address_, port_)
#                 opcua_core_client = Client(address)
#                 opcua_core_client.connect()
#                 print("Connected to SAMYCore")
#                 break
#             except:
#                 print("Connection with SAMYCore failed!!!!!\n Retry in 3 seconds....")
#                 time.sleep(3)
#         # Get information about all nodes of SAMYCore opcua server
#         opcua_core_client.load_type_definitions()
#         return opcua_core_client
#
#     def test_simple_move(self):
#         root = self.client.get_root_node()
#         objects = self.client.get_objects_node()
#         namespaces = self.get_namespaces(self.client)
#         skills_ns = namespaces["https://fortiss.org/UA/DI/"]
#         robot_ns = namespaces[self.robot_name]
#         fortis_ns = namespaces["https://fortiss.org/UA/DI/"]
#         robotics_ns = namespaces["http://opcfoundation.org/UA/Robotics/"]
#         skills_node_id = objects.get_child(["3:DeviceSet",
#         "{}:{}".format(robot_ns, self.robot_name),
#         "4:Controllers",
#         "{}:{}".format(robot_ns, self.robot_name),
#         "5:Skills"])
#         skill_node_id = skills_node_id.get_child(["{}:SimpleMove".format(robot_ns)])
#         paramters_node = skill_node_id.get_child(["3:ParameterSet","7:0_MoveToParameters"])
#         parameters = CRCL_DataTypes.MoveToParametersSetDataType()
#         parameters.MoveStraight = True
#         paramters_node.set_value(parameters)
#         skill_node_id.call_method("Start")
#         last_transition_id = skill_node_id.get_child(["0:LastTransition"])
#         time.sleep(1)
#         if last_transition_id.get_value().Text == "Running to Ready":
#             return 1
#         else:
#             skill_node_id.call_method("Reset")
#             return 0
#
#     def test_set_endeffector(self):
#         root = self.client.get_root_node()
#         objects = self.client.get_objects_node()
#         namespaces = self.get_namespaces(self.client)
#         skills_ns = namespaces["https://fortiss.org/UA/DI/"]
#         robot_ns = namespaces[self.robot_name]
#         fortis_ns = namespaces["https://fortiss.org/UA/DI/"]
#         robotics_ns = namespaces["http://opcfoundation.org/UA/Robotics/"]
#         skills_node_id = objects.get_child(["3:DeviceSet",
#         "{}:{}".format(robot_ns, self.robot_name),
#         "4:Controllers",
#         "{}:{}".format(robot_ns, self.robot_name),
#         "5:Skills"])
#         skill_node_id = skills_node_id.get_child(["{}:SetEndEffectorSkill".format(robot_ns)])
#         paramters_node = skill_node_id.get_child(["3:ParameterSet","7:0_SetEndeffectorParameters"])
#         parameters = CRCL_DataTypes.SetEndeffectorParametersSetDataType()
#         #parameters.Settings.fraction = 0
#         paramters_node.set_value(parameters)
#         skill_node_id.call_method("Start")
#         last_transition_id = skill_node_id.get_child(["0:LastTransition"])
#         time.sleep(1)
#         if last_transition_id.get_value().Text == "Running to Ready":
#             return 1
#         else:
#             skill_node_id.call_method("Reset")
#             return 0
#
#
# client = SamyClient("RobotABB")
#
# def test_simple_move():
#     assert client.test_simple_move() == 1
#
# def test_set_endeffector():
#     assert client.test_set_endeffector() == 1
