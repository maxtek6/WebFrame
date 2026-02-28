
#!/usr/bin/env bash
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


#
# The Azure provided machines typically have the following disk allocation:
# Total space: 85GB
# Allocated: 67 GB
# Free: 17 GB
# This script frees up 28 GB of disk space by deleting unneeded packages and 
# large directories.
# The Flink end to end tests download and generate more than 17 GB of files,
# causing unpredictable behavior and build failures.
#
echo "=============================================================================="
echo "Installing Ubuntu dependencies"
echo "=============================================================================="

df -h
sudo apt-get update
sudo apt-get install -y \
  autoconf \
  autoconf-archive \
  automake \
  libtool \
  libltdl-dev \
  '^libxcb.*-dev' \
  libdbus-1-dev \
  libegl1-mesa-dev \
  libglu1-mesa-dev \
  libice-dev \
  libsctp-dev \
  libsm-dev \
  libx11-dev \
  libx11-xcb-dev \
  libxcb-icccm4-dev \
  libxcb-image0-dev \
  libxcb-keysyms1-dev \
  libxcb-render-util0-dev \
  libxcb-render0-dev \
  libxcb-shape0-dev \
  libxcb-shm0-dev \
  libxcb-sync-dev \
  libxcb-xfixes0-dev \
  libxcb-xinerama0-dev \
  libxcb-xkb-dev \
  libxi-dev \
  libxtst-dev \
  libxkbcommon-dev \
  libxkbcommon-x11-dev \
  libxrender-dev \
  libxrandr-dev
  df -h