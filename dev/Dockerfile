# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
# docker build -t decheine/xdataframe-demo-image -f dev/Dockerfile .
FROM ubuntu:20.04

# env var for timezone skipping during build 
ENV TZ=US/Central
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone


# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/xdataframe
WORKDIR /usr/src/xdataframe

# shell
SHELL ["/bin/bash","-c","-l"]

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
    apt-get install -y libboost-all-dev && \
    wget https://root.cern/download/root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz && \
    tar -xzvf root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz && \
    echo /usr/src/xdataframe/root/lib >> /etc/ld.so.conf && \
    ldconfig && \
    /bin/bash -c 'source root/bin/thisroot.sh'

ENV ROOTSYS /usr/src/xdataframe/root
ENV PATH="$ROOTSYS/bin:$PATH"
ENV LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"

RUN rm -r build && \
    mkdir build && \
    /bin/bash -c 'source root/bin/thisroot.sh' && cd build && cmake -DBUILD_ONLY="s3" .. && cmake --build .

# Getting and installing ROOT
# RUN wget https://root.cern/download/root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz
# RUN tar -xzvf root_v6.24.02.Linux-ubuntu20-x86_64-gcc9.3.tar.gz
# RUN /bin/bash -c 'source root/bin/thisroot.sh'

# ENTRYPOINT [ "/entrypoint.sh" ]

# This command runs your application, comment out this line to compile only
CMD ["./build/bin/Demo"]
# CMD [""]

LABEL Name=xdataframe Version=1.0.0
