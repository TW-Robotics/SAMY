
from opcua import Client
from samyplugin import CRCL_DataTypes

import logging
import time

move_finished = False

class SubHandler(object):

    """
    Subscription Handler. To receive events from server for a subscription
    data_change and event methods are called directly from receiving thread.
    Do not do expensive, slow or network operation there. Create another
    thread if you need to do such a thing
    """

    def datachange_notification(self, node, val, data):
        global move_finished
        print("Python: New data change event", node, val)
        if val:
            move_finished = True

    def event_notification(self, event):
        print("Python: New event", event)


class OPCUA:
    def __init__(self, ip):
        link = ("opc.tcp://{}:61510/ABB.IRC5.OPCUA.Server").format(ip)
        self.client = Client(link) #"opc.tcp://192.168.178.21:61510/ABB.IRC5.OPCUA.Server"
        print(link)
        self.client.set_security_string("Basic256Sha256,SignAndEncrypt,key/certificate.der,key/key.pem")
        self.client.application_uri = "urn:example.org:FreeOpcUa:python-opcua"
        self.client.secure_channel_timeout = 100000
        self.client.session_timeout = 100000
        #self.client.open_secure_channel()
        self.client.connect()
        self.client.load_type_definitions()  # load definition of server specific structures/extension objects
        print("Python: OPC UA connected")
        # Create nodes
        self.root = self.client.get_root_node()
        self.objects = self.client.get_objects_node()
        self.namespaces = self.get_namespaces(self.client)
        ns_controller = self.namespaces["https://abb.com/Robotics/UA/Controller/"]
        ns_objects = self.namespaces["http://abb.com/Robotics/UA/Controller/Objects"]
        ns_di = self.namespaces["http://opcfoundation.org/UA/DI/"]
        #alias_name = "IRB2400_1"
        alias_name = "IRB120"
        #alias_name = "Robot_SIM"

        path = ["0:Objects", "{}:Robots".format(ns_controller),
                "{}:{}".format(ns_objects, alias_name), "{}:RAPID".format(ns_controller),
                "{}:T_ROB1".format(ns_objects), "{}:SERVER".format(ns_objects),
                "{}:receivedString".format(ns_objects)]
        print(path)
        self.string_node = self.root.get_child(path)
        self.wait_for_command_node = self.root.get_child(["0:Objects", "{}:Robots".format(ns_controller),
                                                "{}:{}".format(ns_objects, alias_name), "{}:RAPID".format(ns_controller),
                                                "{}:T_ROB1".format(ns_objects), "{}:SERVER".format(ns_objects),
                                                "{}:wait_for_command".format(ns_objects)])
        self.command_done_node = self.root.get_child(["0:Objects", "{}:Robots".format(ns_controller),
                                                "{}:{}".format(ns_objects, alias_name), "{}:RAPID".format(ns_controller),
                                                "{}:T_ROB1".format(ns_objects), "{}:SERVER".format(ns_objects),
                                                "{}:command_done".format(ns_objects)])
        self.currentTCP_node = self.root.get_child(["0:Objects", "{}:Robots".format(ns_controller),
                                                "{}:{}".format(ns_objects, alias_name), "{}:RAPID".format(ns_controller),
                                                "{}:T_ROB1".format(ns_objects), "{}:SERVER".format(ns_objects),
                                                "{}:currentTCP".format(ns_objects)])
        print("Python: OPC UA Nodes created")
        #except:
        #    print("Python: OPC UA connection failed")

    def subscription(self, client):
        handler = SubHandler()
        sub = client.create_subscription(500, handler)
        handle = sub.subscribe_data_change(self.command_done_node)

    def get_namespaces(self, client):
        namespaces = {}
        root_node = client.get_root_node()
        browse_path = ["0:Objects", "0:Server", "0:NamespaceArray"]
        namespaceArrayNode = root_node.get_child(browse_path)
        namespacesValue = namespaceArrayNode.get_value()
        for i, namespace in enumerate(namespacesValue):
            namespaces[namespace] = i
        return namespaces

class Connection():
    def __init__(self, ipAddress):
        # create a logger for the robot object
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(logging.INFO)
        fh = logging.StreamHandler()
        fh.setFormatter(logging.Formatter("%(levelname)s %(filename)s - %(message)s"))
        self.logger.addHandler(fh)
        self.count = 0

        self.opcua = OPCUA(ipAddress)

    def send_opcua(self, msg):
        # Send the message as string over opcua
        send = False
        self.count = self.count + 1
        print(self.count)
        while not send:
            while not self.opcua.wait_for_command_node.get_value():
                time.sleep(0.001)
            try:
                self.opcua.string_node.set_value(msg)
                self.opcua.wait_for_command_node.set_value(False)
                send = True
            except:
                print("Sending Failed -> trying again")
        print("Python: Command send over OPC UA")
