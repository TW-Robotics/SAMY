import sys
sys.path.insert(0, "..")
import logging
import time

from opcua import Client
from opcua import ua
import yaml
import random

from CRCL_DataTypes import *

import DTbasedController.DTbasedController as DTbasedController
import DTbasedController.DTControlDotFileParser as DTControlDotFileParser
import SAMYControlInterface


def loadDataBaseFile( nameFile ):
    data2 = None
    with open(nameFile) as f:
        data2 = yaml.load(f, yaml.Loader)
    return data2

def getDataBaseNode( client ):
    rootNode = client.get_root_node()
    objectNode = rootNode.get_child("0:Objects")
    childrenNodes = objectNode.get_children()
    for child in childrenNodes:
      if child.get_browse_name().Name == 'DataBase':
         return child

def start_controller():
    dtDotFileParser = DTControlDotFileParser.DTControlDotFileParser('./configFiles/dtController.dot')
    controller = DTbasedController.DTbasedController(dtDotFileParser.root, dtDotFileParser.x_metadata, dtDotFileParser.y_metadata )
    controlInterface = SAMYControlInterface.SAMYControlInterface( 'opc.tcp://core:4840/', controller.controlStateVariables, controller.standardControlCallback)
    controlInterface.startSystemControl(100)


if __name__ == "__main__":
    client = Client("opc.tcp://core:4840/")
    while True:
        try:
            client.connect()
            break
        except:
            print("Connection to SamyCore failed. \nRetry in 3 seconds ...")

    try:
        client.load_type_definitions()

    # Open the file and load the database
        dataBase = loadDataBaseFile("./configFiles/DataBaseFile.yaml")
        dataBaseNode = getDataBaseNode( client )
        dataBaseNS = dataBaseNode.get_browse_name().NamespaceIndex

        elementsCounter = 0
        for elem in dataBase['DataBase']:
            auxStr = None
            if hasattr(elem, 'name'):
                auxStr = str(dataBaseNS) + ':' + elem.name
            elif hasattr(elem, 'Name'):
                auxStr = str(dataBaseNS) + ':' + elem.Name

            print(auxStr)
            serverDataBaseNode = dataBaseNode.get_child(auxStr)
            serverDataBaseNode.set_value(elem)
            elementsCounter = elementsCounter + 1

    finally:
        client.disconnect()

    #input("Press any kay to start the controller")
    start_controller()
