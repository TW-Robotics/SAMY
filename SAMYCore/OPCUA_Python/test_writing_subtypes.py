import sys
sys.path.insert(0, "..")
import logging
import time

from opcua import Client
from opcua import ua

from CRCL_DataTypes import *

if __name__ == "__main__":

    client = Client("opc.tcp://localhost:4840/")
    try:
        client.connect()
        client.load_type_definitions()

        moveToParamodeN = client.get_node(ua.NodeId(56362, 10))
        
        aux2 = CRCL_PoseDataType()
        # Fills some of the fields, including union
        aux2.id = 999
        aux2.name = "testing Name"
        # Set the variable node
        moveToParamodeN.set_value(aux2)
        # Read the variable node that just wrote
    finally:
        client.disconnect()
