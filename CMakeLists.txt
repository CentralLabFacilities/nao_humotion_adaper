## Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
## Use of this source code is governed by a BSD-style license that can be
## found in the COPYING file.

cmake_minimum_required(VERSION 2.8)

PROJECT(nao_humotion_server)
SET(MAIN ${PROJECT_NAME})

# Define this via command line!
# SET(QI_SDK_DIR "/home/nao/naosystems/nao-object-detection-nightly/opt/naoqi-sdk-2.1.2.17-linux64/")
# -DQI_SDK_DIR=$something

SET(ROS_BUILD_TYPE Debug)

FIND_PACKAGE(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs message_generation genmsg)
IF (catkin_FOUND)
    SET(ROS_FOUND 1)
    MESSAGE(STATUS "ROS Support is ON")
    ADD_DEFINITIONS(-DROS_SUPPORT=1)
ENDIF (catkin_FOUND)

IF (NOT catkin_FOUND)
  MESSAGE(FATAL_ERROR "Error: Where is ROS?")
ENDIF ()

FIND_PACKAGE(qibuild)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread)
FIND_PACKAGE(humotion)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

CATKIN_PACKAGE(
    INCLUDE_DIRS include
    LIBRARIES humotion
)

INCLUDE_DIRECTORIES(include ${humotion_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${humotion_LIBRARY_DIRS})

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
FILE(GLOB DUMMY_HEADER_LIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.hpp)

qi_create_bin(${MAIN} main.cpp src/naoqiwrapper.cpp src/naojointinterface.cpp ${DUMMY_HEADER_LIST})

qi_use_lib(${MAIN} ALCOMMON ALPROXIES)
TARGET_LINK_LIBRARIES(${MAIN} ${catkin_LIBRARIES} ${humotion_LIBRARIES})


SET_PROPERTY(TARGET ${MAIN} PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

INSTALL(TARGETS ${MAIN}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION bin
)
