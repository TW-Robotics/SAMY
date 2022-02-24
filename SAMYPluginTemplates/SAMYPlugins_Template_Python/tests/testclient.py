from opcua import Client
from opcua import ua
import time

class TestClient:
    def __init__(self):
        address = ("opc.tcp://{}:{}").format("localhost", "4840")
        self.client = Client(address)
        self.client.connect()
        self.client.load_type_definitions()

    def write_crcl_command(self, id: ua.NodeId, data):
        node = self.client.get_node(id)
        node.set_value(data)

    def call_start_method(self, skill_id: ua.NodeId, method_id: ua.NodeId):
        skill_node = self.client.get_node(skill_id)
        skill_node.call_method(method_id)

    def check_state(self):
        node = self.client.get_node(ua.NodeId(55770, 8))
        val = node.get_value()
        while val.Text != "Running to Ready":
            val = node.get_value()
            #print(val.Text)

    def read_info_source(self, id: ua.NodeId):
        node = self.client.get_node(id)
        return node.get_value()

    def disconnect(self):
        self.client.disconnect()
