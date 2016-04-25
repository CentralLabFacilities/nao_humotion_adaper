## Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
## Use of this source code is governed by a BSD-style license that can be
## found in the COPYING file.

cmake_minimum_required(VERSION 2.8)

project(nao_humotion_adapter)

# Define this via command line!
# SET(QI_SDK_DIR "/home/nao/naosystems/nao-object-detection-nightly/opt/naoqi-sdk-2.1.2.17-linux64/")
# -DQI_SDK_DIR=$something

find_package(qibuild)

qi_create_bin(nao_humotion_adapter "naojointinterface.cpp" "naojointinterface.hpp" "main.cpp")
qi_create_lib(nao_humotion_adapter_lib SHARED SRC "naojointinterface.cpp" "naojointinterface.hpp")
qi_stage_lib(nao_humotion_adapter_lib)
qi_use_lib(nao_humotion_adapter ALCOMMON ALPROXIES)
qi_install_header("naojointinterface.hpp")
