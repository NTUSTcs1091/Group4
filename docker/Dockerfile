# Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# to build the image, should use " sudo docker build --no-cache -t unittest -f docker/Dockerfile ." in the directory " Group4 "
FROM ubuntu:18.04

WORKDIR /UnitTest

COPY CMakeLists.txt LICENSE README /UnitTest/
COPY /docker/unitTest.sh  /UnitTest/
RUN chmod +x /UnitTest/unitTest.sh
COPY src/ /UnitTest/src

RUN apt-get update \
    && apt -y install software-properties-common \
    && apt-get -y install gcc \
    && apt-get install -y build-essential \
    && apt-get install -y wget \
    && apt -y install cmake \
    && apt-get -y install git

RUN git clone https://github.com/google/googletest.git -b release-1.10.0 \
    && cd googletest \
    && mkdir build \
    && cd build \
    && cmake .. -DBUILD_GMOCK=ON \
    && make \
    && make install
    
