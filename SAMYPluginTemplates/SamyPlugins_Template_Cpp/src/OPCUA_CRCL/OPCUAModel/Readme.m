This folder contains the xml ModelDesign file modelling CRCL in OPC UA

In order to compile the xml ModelDesign file into a xml NodeSet that can be used by the different OPC UA Stacks (for example Open62541), execute the following command:

sudo docker run       --mount type=bind,source=$(pwd),target=/model/src       --entrypoint "/app/PublishModel.sh"       sailavid/ua-modelcompiler:opcua_rocks_tested        /model/src/CRCL_OPCUA CRCL_OPCUA /model/src/Published


In order to directly update the model and make it available in the open62541 server/clients, just use sudo ./CompileModel.sh


