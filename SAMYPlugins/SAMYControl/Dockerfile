FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="leber@technikum-wien.at"
LABEL version="0.1"
LABEL description="This is custom Docker Image for \
the SAMYController based on DTControl"

ARG DEBIAN_FRONTEND=noninteractive
RUN apt update && apt upgrade -y
RUN apt install -y build-essential python3-pip
RUN pip3 install numpy dtcontrol lxml pyyaml
RUN mkdir /usr/src/samy
WORKDIR /usr/src/samy

COPY . ./
RUN pip3 install samyplugin-0.0.2-py3-none-any.whl
