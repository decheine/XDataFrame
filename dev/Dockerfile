# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
# docker build -t xdataframe-docker -f dev/Dockerfile .
FROM ubuntu:20.04

# env var for timezone skipping during build 
ENV TZ=US/Central
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN DEBIAN_FRONTEND=noninteractive \
    TZ=US/Chicago \
    apt-get update && apt-get -y dist-upgrade &&  \
    apt-get install -y dpkg-dev && \
    apt-get install -y cmake wget && \
    apt-get install -y g++ && \
    apt-get install -y gcc && apt-get install -y git &&\
    apt-get install -y binutils && \
    apt-get install -y libx11-dev libxpm-dev && \
    apt-get install -y libxft-dev libxext-dev python libssl-dev && \
    apt-get install -y libcurl4-openssl-dev && \
    apt-get install -y libboost-all-dev


# shell
SHELL ["/bin/bash","-c","-l"]

# Getting and installing ROOT
RUN wget https://root.cern/download/root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz
RUN tar -xzvf root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz
RUN /bin/bash -c 'source root/bin/thisroot.sh'




# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/xdataframe
WORKDIR /usr/src/xdataframe

RUN rm -r build

RUN mkdir build && cd build && cmake ..

RUN cd build && cmake -DBUILD_ONLY="s3" --build .



# This command runs your application, comment out this line to compile only
# CMD["./usr/src/xdataframe/build/bin/Demo"]
CMD ["ls","-l", "build"]

LABEL Name=xdataframe Version=0.0.1
