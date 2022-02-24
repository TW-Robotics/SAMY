import sys
sys.path.insert(0, "..")
import logging
import time

from opcua import Client
from opcua import ua


def testSkill( nsIndex, nodeNumber ):
	# The give nodeid must be a parameter in the template. It is a node in the SAMYCore where I write the NodeId of the next skill to be executed. Monitorize it
        nextSkillNodeId_Node = client.get_node(ua.NodeId(nodeNumber, nsIndex))  # -> 2 Parameter of the SAMYPlugin template
        nextSkillNodeId = nextSkillNodeId_Node.get_value()

        myskillNode = client.get_node(nextSkillNodeId)
	# Array with the NodeIds of the methods (start, halt, resume...) of the next skill to be executed by the robot
        myskillMethodsNodesIds = myskillNode.get_methods()
        # Iterating over all the methods and calling them
        for myskillMethodNodeId in myskillMethodsNodesIds:
            try:
               print(myskillMethodNodeId.get_browse_name())
               res = myskillNode.call_method(myskillMethodNodeId)
               print(res)
               time.sleep(3)
            except:
               print("An exception occurred")



        parameterSetNode = myskillNode.get_child("3:ParameterSet")
	# Array with the NodeIds of the parameters of the next skill to be executed by the robot
        parameterSetVariableNodes = parameterSetNode.get_variables()
	# Iterator going through each variable node, getting the browse name of the parameter (you need this to know its order! number_parameterType naming convenction) and the value of the parameter
        for parameterSetVariableNode in parameterSetVariableNodes:
            parameterNode = client.get_node(parameterSetVariableNode)
            print(parameterNode.get_browse_name())
            print(parameterNode.get_value())

def readSystemStatus( ):
       rootNode = client.get_root_node()
       objectNode = rootNode.get_child("0:Objects")
       childrenNodes = objectNode.get_children()
       systemStatusNode = None
       for child in childrenNodes:
          if child.get_browse_name().Name == 'SystemStatus':
             systemStatusNode = child 
       print( systemStatusNode )

       statusVariablesNodes = systemStatusNode.get_children()
       for var in statusVariablesNodes:
           print( var.get_browse_name().NamespaceIndex, "  ", var.get_browse_name().Name )
           print( var.get_value() )
           print( '\n' )
       


if __name__ == "__main__":
    # Address of the SAMYCore -> 1 Parameter of the SAMYPlugin template
    client = Client("opc.tcp://localhost:4840/")
    try:
        client.connect()
        client.load_type_definitions()
 #       testSkill( 8, 56949 )
 #       testSkill( 9, 57384 )
        readSystemStatus()
    finally:
        client.disconnect()
