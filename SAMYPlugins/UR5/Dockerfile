# Download base image ubuntu 14.04
FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="leber@technikum-wien.at"
LABEL version="0.1"
LABEL description="This is custom Docker Image for \
running the SAMY UR5 Plugin"

ARG DEBIAN_FRONTEND=noninteractive

## installing dependencies
RUN apt update -y
RUN apt upgrade -y
RUN apt install -y build-essential python3-pip
RUN pip3 install numpy math3d scipy ipython pypubsub python-dateutil pytz lxml cryptography pyyaml

## copy files into image
RUN mkdir /usr/src/samy
WORKDIR /usr/src/samy
COPY . ./
RUN pip3 install samyplugin-0.0.2-py3-none-any.whl
