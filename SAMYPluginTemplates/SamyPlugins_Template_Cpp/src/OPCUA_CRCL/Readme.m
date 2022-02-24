This folder contains the OPCUA/open62541 (v1.1.3) related files.

Both PlugIns and SAMYCore share this code, since both have a Publisher and a Subscriber managed by Open62541 luvrary.
- model folder contains the CRCL-OPC UA NodeSet that will be used by the nodeset_compiler for generetaing the CRCL model information in Open62541 code. These files are copied from folders in OPCUAModel
- nodeset_compiler folder contains the files required for compiling into Open62541 code the xml NodeSet generated in OPCUAModel.
- OPCUAModel contains the modelling of CRCL in OPCUA and the instructions for compiling the NodeSet that is loaded into the OPCUA Server. The required files are directly copied into model folder when running the shell script provided there
- plugins contains certain files required for compilation of the Open62541 entities that can be user-defined
- PubSub contains the files required for PubSub, including the files in case we wanted to use MQTT broker


