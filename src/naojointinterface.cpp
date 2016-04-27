// Author: Florian Lier [flier AT techfak.uni-bielefeld DOT de]

/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#include "naojointinterface.hpp"

using std::cout;
using std::cerr;

using humotion::Timestamp;

// WARNING: DO NOT CHANGE THIS; VELOCITYMODE IS NOT YET IMPLEMENTED
#define POSITION_CONTROL 1

NaoJointInterface::NaoJointInterface(std::string _robot_ip, std::string _robot_port) : humotion::server::JointInterface() {
    robot_ip = _robot_ip;
    robot_port = _robot_port;
    nji = new NaoQiWrapper(robot_ip, robot_port);
    init_joints();
}

NaoJointInterface::~NaoJointInterface(){
    delete nji;
}

void NaoJointInterface::incoming_jointstates() {

    //fetch current timestamp
    humotion::Timestamp timestamp = humotion::Timestamp::now();

    JointInterface::store_incoming_position(ID_NECK_TILT, nji->getHeadPitch(), timestamp);
    // std::cout << ">>> NAO PITCH: " << nji->getHeadPitch() << std::endl;
    JointInterface::store_incoming_velocity(ID_NECK_TILT, 0.1, timestamp);

    JointInterface::store_incoming_position(ID_NECK_PAN, nji->getHeadYaw(), timestamp);
    // std::cout << ">>> NAO YAW: " << nji->getHeadYaw() << std::endl;
    JointInterface::store_incoming_velocity(ID_NECK_PAN, 0.1, timestamp);

    store_dummy_data(ID_LIP_LEFT_UPPER, timestamp);
    store_dummy_data(ID_LIP_LEFT_LOWER, timestamp);
    store_dummy_data(ID_LIP_CENTER_UPPER, timestamp);
    store_dummy_data(ID_LIP_CENTER_LOWER, timestamp);
    store_dummy_data(ID_LIP_RIGHT_UPPER, timestamp);
    store_dummy_data(ID_LIP_RIGHT_LOWER, timestamp);
    store_dummy_data(ID_NECK_ROLL, timestamp);
    store_dummy_data(ID_EYES_BOTH_UD, timestamp);
    store_dummy_data(ID_EYES_LEFT_LR, timestamp);
    store_dummy_data(ID_EYES_RIGHT_LR, timestamp);
    store_dummy_data(ID_EYES_LEFT_LID_LOWER, timestamp);
    store_dummy_data(ID_EYES_LEFT_LID_UPPER, timestamp);
    store_dummy_data(ID_EYES_LEFT_BROW, timestamp);
    store_dummy_data(ID_EYES_RIGHT_LID_LOWER, timestamp);
    store_dummy_data(ID_EYES_RIGHT_LID_UPPER, timestamp);
    store_dummy_data(ID_EYES_RIGHT_BROW, timestamp);
}

void NaoJointInterface::store_dummy_data(int id, humotion::Timestamp timestamp){
    JointInterface::store_incoming_position(id, 0.0, timestamp);
    JointInterface::store_incoming_velocity(id, 0.0, timestamp);
}

void NaoJointInterface::run(){
    std::cout << ">>> NAO Joint Interface Running" << std::endl;
}

void NaoJointInterface::publish_target(int e, float position, float velocity){
    // We do this in execute motion for all joints at once...
}

void NaoJointInterface::execute_motion(){
    // In Degree, this is converted to RAD automatically within nji!
    nji->setHeadPitch(-get_target_position(ID_NECK_TILT));
    nji->setHeadYaw(get_target_position(ID_NECK_PAN));
    nji->executeMotion();
}

void NaoJointInterface::enable_joint(int e){
    // NAO does not support this, joints are always enabled
}

void NaoJointInterface::disable_joint(int e){
    //NAO does not support this, joints are always enabled
}

void NaoJointInterface::store_min_max(int id, float min, float max){
    joint_min[id] = min;
    joint_max[id] = max;
}

void NaoJointInterface::init_joints(){
    store_min_max(ID_NECK_TILT, -30, 25);
    store_min_max(ID_NECK_PAN, -110, 110);
    store_min_max(ID_NECK_ROLL, -1, 1);
    store_min_max(ID_EYES_BOTH_UD, -1, 1);
    store_min_max(ID_EYES_LEFT_LR, -1, 1);
    store_min_max(ID_EYES_RIGHT_LR, -1, 1);
    store_min_max(ID_EYES_LEFT_LID_UPPER, -1, 1);
    store_min_max(ID_EYES_LEFT_LID_LOWER, -1, 1);
    store_min_max(ID_EYES_RIGHT_LID_UPPER, -1, 1);
    store_min_max(ID_EYES_RIGHT_LID_LOWER, -1, 1);
    store_min_max(ID_EYES_LEFT_BROW, -1, 1);
    store_min_max(ID_EYES_RIGHT_BROW, -1, 1);
    store_min_max(ID_LIP_CENTER_UPPER, -1, 1);
    store_min_max(ID_LIP_CENTER_LOWER, -1, 1);
    store_min_max(ID_LIP_LEFT_UPPER, -1, 1);
    store_min_max(ID_LIP_LEFT_LOWER, -1, 1);
    store_min_max(ID_LIP_RIGHT_UPPER, -1, 1);
    store_min_max(ID_LIP_RIGHT_LOWER, -1, 1);
}

void NaoJointInterface::shutdown() {
    nji->shutdown();
}

