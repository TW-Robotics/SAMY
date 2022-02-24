import sys
sys.path.insert(0, "..")
import logging
import time

from opcua import Client
from opcua import ua

from CRCL_DataTypes import *

if __name__ == "__main__":

    client = Client("opc.tcp://localhost:4567/")
    try:
        # Connect to the server
        client.connect()
        # Load  data types in the server (in this case the CRCL data types)
        client.load_type_definitions()  # scan server for custom structures and import them
        # Get a node
        myvar = client.get_node(ua.NodeId(1007, 1))
        # Get the value of the node. The variable already contains the matching structure
        aux = myvar.get_value()
        # Prints some fields of the data type (the DataType is ActuateJointsDataType). The DataTypes can be found in the file CRCL_DataTypes.py
        print(aux)
        # Access and prints different fields
        print( "id    ", aux.id, "\n" )
        print( "name    ", aux.name, "\n" )
        print( "commandID    ", aux.commandID, "\n" )
        print( "RealTimeCommand    ", aux.RealTimeCommand, "\n" )
        print( "RealTimeParameterNode    ", aux.RealTimeParameterNode, "\n" )
        print( "Guard    ", aux.Guard, "\n" )
        print( "ActuateJoint    ", aux.ActuateJoint, "\n" )
        print( "ActuateJoint 1    ", aux.ActuateJoint[1], "\n" )
        print( "JointTolerances    ", aux.JointTolerances, "\n" )
        print( "JointTolerances Setting 0    ", aux.JointTolerances.Setting[0], "\n" )
        print( "JointTolerances Setting 1    ", aux.JointTolerances.Setting[1], "\n" )

        print( "\n\n\n\n\n\n\n" )

        # Get a node containing a variable of SetTransSpeedDataType
        myvar2 = client.get_node(ua.NodeId(1017, 1))
        # Creates a SetTransSpeedDataType command
        aux2 = SetTransSpeedDataType()
        # Fills some of the fields, including union
        aux2.id = 999
        aux2.name = "testing Name"
        aux2.commandID = 834
        aux2.TransSpeed.switchField = 2
        aux2.TransSpeed.unionValue = CRCL_TransSpeedRelativeDataType()
        print(aux2)
        print( "\n\n\n" )
        # Set the variable node
        myvar2.set_value(aux2)
        # Read the variable node that just wrote
        aux3 = myvar2.get_value()
        print( aux3 )

        print( "\n\n\n\n\n\n\n" )
        # Modifies the previous SetTransSpeedDataType variable, changing the union
        aux2.TransSpeed.switchField = 1
        aux2.TransSpeed.unionValue = CRCL_TransSpeedAbsoluteDataType()
        aux2.TransSpeed.unionValue.name = "name test!"
        aux2.TransSpeed.unionValue.setting = 987.654
        print(aux2)
        print( "\n\n\n" )
        # Set the variable in the server
        myvar2.set_value(aux2)
        # Reads the variable
        aux3 = myvar2.get_value()
        print( aux3 )
        print( "\n\n\n\n\n\n\n" )

        # Gets command parameters for a SetEndPoseToleranceCommand and prints it
        setEndPoseToleranceParameters = client.get_node(ua.NodeId(1521, 1))
        val2 = setEndPoseToleranceParameters.get_value()
        print(val2)
        print( "\n\n\n\n\n\n\n" )

        # Gets the test SAMYRobot node (which is the most complex structure including all commands, etc.), and prints it
        robotNode = client.get_node(ua.NodeId(1400, 1))
        val = robotNode.get_value()
        print(val)
    finally:
        client.disconnect()
