FROM ubuntu:20.04

# LABEL about the custom image
LABEL maintainer="leber@technikum-wien.at"
LABEL version="0.1"
LABEL description="This is custom Docker Image for \
running the SAMY Python Template"

ARG DEBIAN_FRONTEND=noninteractive
ENV IP_ADDRESS=172.0.0.2

## installing dependencies
RUN apt update
RUN apt install -y python3 build-essential python3-pip
RUN pip3 install ipython python-dateutil pytz lxml cryptography pypubsub numpy

## copy files into image
RUN mkdir /usr/src/samy
WORKDIR /usr/src/samy
COPY . ./
RUN pip3 install samyplugin-0.0.2-py3-none-any.whl

## start plugin (get ip address from docker)

EXPOSE 4840

#ENTRYPOINT ["tail"]
#CMD ["-f","/dev/null"]
CMD python3 /usr/src/samy/main.py core
