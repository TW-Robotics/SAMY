import sys
import time
from IPython import embed
import threading
import logging

from samyplugin.CRCL_DataTypes import *
from samyplugin.settings import Settings

from opcua.common.xmlexporter import XmlExporter
from opcua.common.type_dictionary_buider import DataTypeDictionaryBuilder, get_ua_class
from opcua import Client
from opcua import ua

from pubsub import pub
from pubsub.utils import useNotifyByWriteFile
import inspect
import collections
from pprint import pprint

# Interface python3 main.py -IP SAMYCore- -Plugin Port- -IP Robot- -PluginName-

class ErrorHandler(pub.IListenerExcHandler):
    def __call__(self, listenerID, topicObj):
        print("Error while processing {} Topic.".format(topicObj))
        pub.sendMessage("command_error")

class Plugin():
    def __init__(self):
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(logging.INFO)
        log_handler = logging.StreamHandler()
        log_handler.setFormatter(logging.Formatter("%(levelname)s %(filename)s - %(message)s"))
        self.logger.addHandler(log_handler)

        self.robot_node = None
        self.thread = None
        self.opcua_core_client = None
        self.my_skill_node = None
        self.control_methodes = {}
        self.start_method_id = None # TODO create a dict
        self.resume_method_id = None
        self.suspend_method_id = None
        self.halt_method_id = None
        self.reset_method_id = None
        self.log_file = open("message_log.txt", "w")
        self.crcl_command_dict = None
        self.information_source_nodes = None
        self.information_source_nodes_dict = {}
        self.skill_error = False
        self.Settings = Settings()
        #self.transform = Transform()
        pub.setListenerExcHandler(ErrorHandler())
        self.log_all_messages()
        self.create_subscribers()

######################### OPCUA CLIENT SECTION #################################

    def datachange_notification(self, node, val, data):
        self.logger.info("Got datachange_notification", data)

    def event_notification(self, event):
        self.logger.debug("Python: New event {} {}".format(event, event.SourceNode))
        text = event.Message.Text
        words = text.split(" ")
        if words[len(words)-1] == "Running":
            self.my_skill_node = self.opcua_core_client.get_node(event.SourceNode)
            self.thread = threading.Thread(target=self.command_thread, args=())
            self.thread.start()

######################### OPCUA CLIENT SECTION END #############################

    def sort_by_number(self, elem):
        try:
            return int(elem[0][:2])
        except:
            return int(elem[0][:1])

    def command_thread(self):
        self.logger.info("Command Thread started\n")
        # Get the node id for each method of the skill
        my_skill_method_node_ids = self.my_skill_node.get_methods()
        # Connect methodes of skill to the signals of the plugin
        for i, node_id in enumerate(my_skill_method_node_ids):
            browse_name = node_id.get_browse_name()
            if browse_name.Name == "Halt":
                self.halt_method_id = node_id
            elif browse_name.Name == "Reset":
                self.reset_method_id = node_id
            elif browse_name.Name == "Start":
                self.start_method_id = node_id
            elif browse_name.Name == "Resume":
                self.resume_method_id = node_id
            elif browse_name.Name == "Suspend":
                self.suspend_method_id = node_id

        ns = self.my_skill_node.nodeid.NamespaceIndex
        self.logger.debug("my_skill_node = {}".format(self.my_skill_node))
        self.logger.debug("Robot NamespaceIndex = {}".format(ns))
        parameter_set_node = self.my_skill_node.get_child("3:ParameterSet") #3
        self.logger.debug("parameter_set_node = {}".format(parameter_set_node))
        parameter_set_variable_node_ids = parameter_set_node.get_variables()
        parameter_nodes = {}

        for parameter_node_id in parameter_set_variable_node_ids:
            parameter_node = self.opcua_core_client.get_node(parameter_node_id)
            parameter_nodes[parameter_node.get_browse_name().Name] = parameter_node

        parameter_nodes_sorted = sorted(parameter_nodes.items(), key=self.sort_by_number)
        # Reset skill error
        self.skill_error = False
        for i in range(len(parameter_nodes_sorted)):
            if not self.skill_error:
                val = parameter_nodes_sorted[i][1].get_value()
                topic = self.crcl_command_dict[type(val)]
                self.logger.debug(topic)
                pub.sendMessage(topic, data=val)
            else:
                break
        if not self.skill_error:
            pub.sendMessage("command_reset")

    def connect_to_core(self, address_, port_):
        # Connect to SAMYCore opcua server
        while True:
            try:
                # Create opcua client connection with SAMYCore
                self.logger.info("Connecting to SAMYCore")
                address = ("opc.tcp://{}:{}").format(address_, port_)
                self.opcua_core_client = Client(address)
                self.opcua_core_client.connect()
                self.logger.info("Connected to SAMYCore")
                break
            except:
                self.logger.info("Connection with SAMYCore failed!!!!!\n Retry in 3 seconds....")
                time.sleep(2)
        # Get information about all nodes of SAMYCore opcua server
        self.opcua_core_client.load_type_definitions()
        self.crcl_command_dict = {
            ua.InitCanonParametersSetDataType: "InitCanon",
            ua.EndCanonParametersSetDataType: "EndCanon",
            ua.MessageParametersSetDataType: "Message",
            ua.MoveToParametersSetDataType: "MoveTo",
            ua.MoveScrewParametersSetDataType: "MoveScrew",
            ua.MoveThroughToParametersSetDataType: "MoveThroughTo",
            ua.DwellParametersSetDataType: "Dwell",
            ua.ActuateJointsParametersSetDataType: "ActuateJoints",
            ua.ConfigureJointReportsParametersSetDataType: "ConfigureJointReports",
            #ua.ConfigureJointReportParametersSetDataType: "ConfigureJointReport",
            ua.SetDefaultJointPositionsTolerancesParametersSetDataType: "SetDefaultJointPositionsTolerances",
            ua.GetStatusParametersSetDataType: "GetStatus",
            ua.CloseToolChangerParametersSetDataType: "CloseToolChanger",
            ua.OpenToolChangerParametersSetDataType: "OpenToolChanger",
            ua.SetRobotParametersParametersSetDataType: "SetRobotParameters",
            ua.SetEndeffectorParametersParametersSetDataType: "SetEndeffectorParameters",
            ua.SetEndeffectorParametersSetDataType: "SetEndeffector",
            ua.SetTransAccelParametersSetDataType: "SetTransAccel",
            ua.SetTransSpeedParametersSetDataType: "SetTransSpeed",
            ua.SetRotAccelParametersSetDataType: "SetRotAccel",
            ua.SetRotSpeedParametersSetDataType: "SetRotSpeed",
            ua.SetAngleUnitsParametersSetDataType: "SetAngleUnits",
            ua.SetEndPoseToleranceParametersSetDataType: "SetEndPoseTolerance",
            ua.SetForceUnitsParametersSetDataType: "SetForceUnits",
            ua.SetIntermediatePoseToleranceParametersSetDataType: "SetIntermediatePoseTolerance",
            ua.SetLengthUnitsParametersSetDataType: "SetLengthUnits",
            ua.SetMotionCoordinationParametersSetDataType: "SetMotionCoordination",
            ua.SetTorqueUnitsParametersSetDataType: "SetTorqueUnits",
            ua.StopMotionParametersSetDataType: "StopMotion",
            ua.ConfigureStatusReportParametersSetDataType: "ConfigureStatusReport",
            ua.EnableSensorParametersSetDataType: "EnableSensor",
            ua.DisableSensorParametersSetDataType: "DisableSensor",
            ua.EnableGripperParametersSetDataType: "EnableGripper",
            ua.DisableGripperParametersSetDataType: "DisableGripper",
            ua.EnableRobotParameterStatusParametersSetDataType: "EnableRobotParameterStatus",
            ua.DisableRobotParameterStatusParametersSetDataType: "DisableRobotParameterStatus"
        }

    def disconnect_core(self):
        self.logger.info("Stopping plugin")
        for skill_node in self.skill_list:
            skill_node.call_method("0:Halt")
            self.logger.info("Halt called for {}".format(skill_node))
        self.opcua_core_client.disconnect()

    def subscribe_to_core(self, robot_name):
        try:
            # Getting the root node is not stricly neccessary but recomended
            root = self.opcua_core_client.get_root_node()
            objects = self.opcua_core_client.get_objects_node()
            nodes = objects.get_child(["3:DeviceSet"])
            namespaces = self.get_namespaces(self.opcua_core_client)
            nsFortissDI = namespaces["https://fortiss.org/UA/DI/"]
            skillTransitionEventBrowsePath = str(nsFortissDI) + ':SkillTransitionEventType'
            samy_event = root.get_child(["0:Types","0:EventTypes","0:BaseEventType","0:TransitionEventType","0:ProgramTransitionEventType", skillTransitionEventBrowsePath])
            found_robot = False
            for object in nodes.get_children():
                if object.get_browse_name().Name == robot_name:
                    ns = object.nodeid.NamespaceIndex
                    robot_node = object
                    skills_node = object.get_child(["4:Controllers", "{}:{}".format(ns, robot_name), "5:Skills"])
                    found_robot = True
            if not found_robot:
                self.logger.error("No robot with name: " + robot_name + " in SAMYCore found")
                exit()
            # Get all skill node ids and reset them
            self.skill_list = skills_node.get_children()
            self.logger.debug("\n\n\n\n")
            self.logger.debug("robot_node = ", robot_node)
            self.logger.debug("skills_node = {}".format(skills_node))
            self.logger.debug("skill_list= {}".format(self.skill_list))
            for skill_node in self.skill_list:
                skill_node.call_method("0:Reset")
                self.logger.info("Reset called for skill {} {}".format(skill_node.get_browse_name().Name, skill_node))
            # Subscribe to robot node
            sub = self.opcua_core_client.create_subscription(100, self)
            handle = sub.subscribe_events(robot_node, samy_event)
            self.logger.info("Subscription started")
            embed()
        except Exception as e:
            self.logger.error(e)
        finally:
            self.logger.info("Subscription closed")

    def get_namespaces(self, client):
        namespaces = {}
        root_node = client.get_root_node()
        browse_path = ["0:Objects", "0:Server", "0:NamespaceArray"]
        namespaceArrayNode = root_node.get_child(browse_path)
        namespacesValue = namespaceArrayNode.get_value()
        for i, namespace in enumerate(namespacesValue):
            namespaces[namespace] = i
        return namespaces

    def init_settings(self):
        self.Settings

    def send_command_reset(self):
        self.logger.info("Command is finished")
        self.logger.info(self.reset_method_id)
        self.skill_error = True
        # Call methode finished in oocua server
        self.my_skill_node.call_method(self.reset_method_id)

    def send_command_halt(self):
        self.logger.info("Command is on hald")
        self.logger.info(self.halt_method_id)
        self.skill_error = True
        # Call methode halt in opcua server
        #self.thread.exit()
        self.my_skill_node.call_method(self.halt_method_id)
        time.sleep(0.2)
        #val = self.robot_state_node.get_value()
        #val.Text = "Ready"
        #self.logger.info("Writing to RobotState Node: {}".format(self.robot_state_node))
        #self.robot_state_node.set_value(val)

    def send_command_error(self):
        self.logger.error("Command faild to execute")
        self.logger.error("Error:", exc_info=True)
        # Call methode error in opcua
        #self.my_skill_node.call_method(self.)

    def send_command_suspend(self):
        self.logger.info("Command suspended")
        self.logger.info(self.suspend_method_id)
        # Call methode error in opcua
        self.my_skill_node.call_method(self.suspend_method_id)

    def get_information_source_nodes(self):
        root = self.opcua_core_client.get_root_node()
        objects = self.opcua_core_client.get_objects_node()
        namespaces = self.get_namespaces(self.opcua_core_client)
        ns_id = namespaces["http://SAMY.org/InformationSources"]
        information_source_node = objects.get_child(["{}:InformationSources".format(ns_id)])
        self.information_source_nodes = information_source_node.get_children()
        for node in self.information_source_nodes:
            self.information_source_nodes_dict[node.get_browse_name().Name] = node.get_child(["{}:{}_0".format(ns_id, node.get_browse_name().Name)])
        self.logger.debug("Dict: {}".format(self.information_source_nodes_dict))

    def write_information_source(self, name, data):
        self.logger.info("Writing Iformation source")
        self.logger.info("Information Source info : Name: {}  Data: {}".format(name, data))
        self.information_source_nodes_dict[name].set_value(data)
        self.logger.info("Information Source {} set to {}".format(name, data))

    def log_all_messages(self):
        useNotifyByWriteFile(self.log_file)

    def create_subscribers(self):
        pub.subscribe(self.send_command_reset, "command_reset")
        pub.subscribe(self.send_command_halt, "command_halt")
        pub.subscribe(self.send_command_error, "command_error")
        pub.subscribe(self.send_command_suspend, "command_suspend")
        pub.subscribe(self.write_information_source, "write_information_source")

    def get_robot_settings(self, robot_name):
        return self.Settings.load_robot_settings(robot_name)

    def set_settings_path(self, path):
        self.Settings.set_settings_path(path)
