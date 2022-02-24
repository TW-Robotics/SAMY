docker run       --mount type=bind,source=$(pwd),target=/model/src       --entrypoint "/app/PublishModel.sh"       sailavid/ua-modelcompiler:opcua_rocks_tested        /model/src/CRCL CRCL /model/src/Published

echo "Removing administrator rights requeriments"
chmod -R 777 ..

echo "Copying the new compilated OPC UA model into ../model folder"
cp -R ./Published/CRCL ../all_models/Published
cp  ./CRCL.xml ../all_models
