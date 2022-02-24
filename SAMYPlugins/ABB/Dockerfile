# Download base image ubuntu 14.04
FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="leber@technikum-wien.at"
LABEL version="0.1"
LABEL description="This is custom Docker Image for \
running the SAMY UR5 Plugin"

ARG DEBIAN_FRONTEND=noninteractive
#ENV IP_ADDRESS=172.0.0.2

## installing dependencies
RUN apt update
RUN apt install -y build-essential python3-pip
RUN pip3 install numpy math3d scipy ipython pubsub pypubsub python-dateutil pytz lxml cryptography

## copy files into image
RUN mkdir /usr/src/samy
WORKDIR /usr/src/samy
COPY . ./
RUN pip3 install samyplugin-0.0.2-py3-none-any.whl

## start plugin (get ip address from docker)

#ENTRYPOINT ["tail"]
#CMD ["-f","/dev/null"]
