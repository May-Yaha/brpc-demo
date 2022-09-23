FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LC_ALL C.UTF-8

RUN sed -i "s@http://.*archive.ubuntu.com@https://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list && \
    sed -i "s@http://.*security.ubuntu.com@https://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list

RUN apt-get update && apt-get install -y --no-install-recommends \
        curl \
        apt-utils \
        openssl \
        ca-certificates \
        ssh \
        openssh-server \
        build-essential \
        git \
        net-tools \
        tar \
        rsync \
        python3 \
        python3-pip

# install deps
RUN apt-get update -y && apt-get install -y --no-install-recommends \
        git \
        g++ \
        make \
        cmake \
        libgtest-dev \
        libssl-dev \
        libgflags-dev \
        libprotobuf-dev \
        libprotoc-dev \
        protobuf-compiler \
        libleveldb-dev \
        libgoogle-perftools-dev \
        libsnappy-dev && \
        apt-get clean -y

ARG WORK_DIR=/home/work/workspace
ARG DOWNLOAD_DIR=/tmp
# 创建目录及打包目录
ADD ./ ${WORK_DIR}

CMD ["/usr/sbin/sshd", "-D"]