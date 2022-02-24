import sys
sys.path.insert(0, "..")
import logging
import time

from opcua import Client
from opcua import ua
import yaml
import random

from CRCL_DataTypes import *

def generateDataBaseFile():
        dataBase = {}
        dataBase['DataBase'] = []
        for i in range(100):
           if(i%2 == 1):
               aux = CRCL_PoseDataType()
               aux.name = "NameTesting_" + str(i)
               aux.id = i
               aux.point.x = random.random() 
               aux.point.y = random.random() 
               aux.point.z = random.random() 
               aux.xAxis.i = random.random() 
               aux.xAxis.j = random.random() 
               aux.xAxis.k = random.random() 
               aux.zAxis.i = random.random() 
               aux.zAxis.j = random.random() 
               aux.zAxis.k = random.random() 
               dataBase['DataBase'].append(aux)
           else:
               aux = CRCL_WrenchDataType()
               aux.name = "NameTesting_" + str(i)
               aux.id = i
               dataBase['DataBase'].append(aux)
        return dataBase


def loadDataBaseFile( nameFile ):
        data2 = None
        with open(nameFile) as f:
            data2 = yaml.load(f, yaml.Loader)
     #       print(data)
            print(data2['DataBase'][0])
            print('\n')
            print(data2['DataBase'][1])
            print('\n')
            print(data2['DataBase'][2])
            print('\n')
            print(data2['DataBase'][3])

        with open('test2.yaml', 'w') as f:
           data3 = yaml.dump(data2, f, sort_keys=False)


if __name__ == "__main__":
    # Address of the SAMYCore -> 1 Parameter of the SAMYPlugin template
    client = Client("opc.tcp://localhost:4840/")
    try:
        client.connect()
        client.load_type_definitions()
        
        dataBase = generateDataBaseFile()
        dataBaseDump = yaml.dump(dataBase, sort_keys=False)
        correctedDataBase = dataBaseDump.replace("builtins", "CRCL_DataTypes")
        with open('test.yaml', 'w') as f:
           f.write(correctedDataBase)

# Open the file and load the file
        loadDataBase( 'test.yaml' )
    finally:
        client.disconnect()
