
import logging
import os
import sys
import time
PACKAGE_PARENT = '..'
SCRIPT_DIR = os.path.dirname(os.path.realpath(os.path.join(os.getcwd(), os.path.expanduser(__file__))))
sys.path.append(os.path.normpath(os.path.join(SCRIPT_DIR, PACKAGE_PARENT)))

from pubsub import pub
import samyplugin.CRCL_DataTypes

from opcua import Client


class SubHandler(object):
    """
    Subscription Handler. To receive events from server for a subscription
    """

    def datachange_notification(self, node, val, data):
        print("Python: New data change event", node, val)


    def event_notification(self, event):
        print("Python: New event", event)


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
        self.opcua_plc_client = None
        self.idx = None
        self.cylinder_node = None
        self.conveyor_parts_node = None
        self.conveyor_holder_node = None
        self.sensor_node = None
        self.handler = None
        # Subscribe to the CRCL command topics
        pub.subscribe(self.enable_device, "EnableGripper")
        pub.subscribe(self.disable_device, "DisableGripper")

    # Add robot specific methodes here:

    def connect_to_plc(self):
        while True:
            try:
                # Create opcua client connection with PLC OPCUA Server
                self.logger.info("Connecting to PLC OPCUA Server")
                address = ("opc.tcp://{}:{}/PLC/)").format(self.host, 4842)
                self.logger.info(address)
                self.opcua_plc_client = Client(address)
                self.opcua_plc_client.connect()
                self.logger.info("Connected to PLC")
                break
            except:
                self.logger.info("Connection with PLC failed!!!!!\n Retry in 3 seconds....")
                self.logger.error("Error:", exc_info=True)
                time.sleep(3)
        self.opcua_plc_client.load_type_definitions()

    def get_nodes(self):
        root = self.opcua_plc_client.get_root_node()
        objects = self.opcua_plc_client.get_objects_node()

        self.conveyor_holder_node = objects.get_child(["3:PLC_Nodes", "3:ConveyorHolder"])
        self.conveyor_parts_node = objects.get_child(["3:PLC_Nodes", "3:ConveyorParts"])
        self.cylinder_node = objects.get_child(["3:PLC_Nodes", "3:Cylinder"])
        self.sensor_node = objects.get_child(["3:PLC_Nodes", "3:Sensor"])

    def subscribe_to_sensor(self):
        self.handler = SubHandler()
        sub = self.opcua_plc_client.create_subscription(100, self.handler)
        handle = sub.subscribe_data_change(self.sensor_node)

    def enable_device(self, data):
        self.logger.info("GripperName = {}".format(data.GripperName))
        if data.GripperName == "cylinder":
            self.logger.info("Setting Cylinder to TRUE")
            self.cylinder_node.set_value(True)
        elif data.GripperName == "conveyor_parts":
            self.logger.info("Setting conveyor parts to TRUE")
            self.conveyor_parts_node.set_value(True)
        elif data.GripperName == "conveyor_holder":
            self.logger.info("Setting conveyor holder to TRUE")
            self.conveyor_holder_node.set_value(True)
        else:
            self.logger.info("No device with this name")
            #pub.sendMessage("command_error")
        #time.sleep(0.5)
        self.logger.info("Enable device finished")

    def disable_device(self, data):
        self.logger.info("GripperName = {}".format(data.GripperName))
        if data.GripperName == "cylinder":
            self.logger.info("Setting Cylinder to FALSE")
            self.cylinder_node.set_value(False)
        elif data.GripperName == "conveyor_parts":
            self.logger.info("Setting conveyor parts to FALSE")
            self.conveyor_parts_node.set_value(False)
        elif data.GripperName == "conveyor_holder":
            self.conveyor_holder_node.set_value(False)
        else:
            self.logger.info("No device with this name")
            #pub.sendMessage("command_error")
