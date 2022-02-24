Content of the folder:

Basic_Test_Servers: Contains two basic servers with a simple union variable based on the custom_types example of the Open62541 stack. One of them uses the files, in the other one the files are generated from the .bsd (OPC UA Binary Schema) description.

FreeOPCUA_fixed_stack: Modified version of https://github.com/FreeOpcUa/python-opcua that supports unions.

CRCL_DataTypes.py: Automatically generated CRCL classes that allow directly interacting with the SAMYCore. They are rather a reference, since when connecting to the SAMYCore, they are automatically created when invoking the load_type_definitions()

structuresGenerator.py: Generates from a .bsd file (OPC UA Binary Schema) python classes.

client_example.py: Contains a simple client that shows a basic interaction with some CRCL specific classes. The classes can be found in CRCL_DataTypes.py. Nevertheless all the CRCL classes in this example are directly made available in the client reading the OPC UA server root->Types->DataTypes->OPC Binary variable, with the function client.load_type_definitions().
In particular, the current variables used/accesed in the Python example requires to use the test Server that is built together with the SAMYCore, and use the test client to write automatically values in the variables (if we don't write them, we will just get empty values, but it will work).
For this purpose, one runs:
./testsServer [ServerTest]   (built along with the SAMYCore)
./testsClient     (built along with the SAMYCore)

and finally:
python3 client_example.py
