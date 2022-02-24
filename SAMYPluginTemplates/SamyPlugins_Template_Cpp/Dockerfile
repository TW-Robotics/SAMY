FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="leber@technikum-wien.at"
LABEL version="0.1"
LABEL description="This is custom Docker Image for \
running SAMY C++ Plugins"

ARG DEBIAN_FRONTEND=noninteractive

## installing dependencies
RUN apt update && apt upgrade -y
RUN apt install -y libboost-python1.71.0 build-essential \
 cmake nano libyaml-cpp-dev libboost-all-dev git libspdlog-dev
 
RUN mkdir /usr/src/samy
WORKDIR /usr/src/samy
# Install open62541 with the fix for unions
WORKDIR open62541_v1.2_unions_fixed/build
RUN cmake -DUA_NAMESPACE_ZERO=FULL \
  -DUA_ENABLE_SUBSCRIPTIONS=ON \
  -DUA_ENABLE_SUBSCRIPTIONS_EVENTS=ON \
	-DUA_ENABLE_DISCOVERY=ON \
	-DUA_ENABLE_DISCOVERY_MULTICAST=ON \
	-DUA_ENABLE_DA=ON \
	-DUA_ENABLE_METHODCALLS=ON \
	-DUA_ENABLE_NODEMANAGEMENT=ON \
	-DUA_ENABLE_MICRO_EMB_DEV_PROFILE=OFF \
	-DUA_ENABLE_PUBSUB=ON \
	-DUA_ENABLE_PUBSUB_ETH_UADP=ON \
	-DUA_ENABLE_PUBSUB_ETH_UADP_ETF=ON \
	-DUA_ENABLE_PUBSUB_FILE_CONFIG=ON \
	-DUA_ENABLE_PUBSUB_INFORMATIONMODEL=ON \
	-DUA_ENABLE_PUBSUB_INFORMATIONMODEL_METHODS=ON \
	-DUA_ENABLE_PUBSUB_MONITORING=ON \
	-DUA_ENABLE_PUBSUB_MQTT=ON \
	-DUA_ENABLE_JSON_ENCODING=ON \
	..
RUN make -j
RUN make install

# build and install the plugin library
