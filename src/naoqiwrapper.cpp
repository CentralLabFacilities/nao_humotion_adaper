// Author: Florian Lier [flier AT techfak.uni-bielefeld DOT de]

/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#include "naoqiwrapper.hpp"

NaoQiWrapper::NaoQiWrapper(std::string _robot_ip, std::string _robot_port) {
    robot_ip = _robot_ip;
    std::cout << ">>> Using Robot " << _robot_ip << ":" << std::atoi(_robot_port.c_str()) << std::endl;
    motion = new AL::ALMotionProxy(_robot_ip, std::atoi(_robot_port.c_str()));
    fractionMaxSpeed = 0.3f;
    joints = AL::ALValue::array("HeadYaw", "HeadPitch");
    angles = AL::ALValue::array(0.0f, 0.0f);
    stiff = AL::ALValue::array(1.0f, 1.0f);
    setStiff(1.0f);
    motion->setStiffnesses(joints, stiff);
    std::cout << ">>> Setting Stiffness to 1.0" << std::endl;
}

NaoQiWrapper::~NaoQiWrapper(){}

float NaoQiWrapper::getHeadPitch(){
    return motion->getAngles("HeadPitch", useSensors)[0];
}

float NaoQiWrapper::getHeadYaw(){
    return motion->getAngles("HeadYaw", useSensors)[0];
}

void NaoQiWrapper::setHeadYaw(float _yaw) {
    angles[0] = degreeToRad(_yaw);
}

void NaoQiWrapper::setHeadPitch(float _pitch) {
    angles[1] = degreeToRad(_pitch);
}

void NaoQiWrapper::setFractionSpeed(float _speed) {
    fractionMaxSpeed = _speed;
}

void NaoQiWrapper::setStiff(float _stiff) {
    for (int i=0; i < joints.getSize(); i++) {
        stiff[i] = _stiff;
    }
}

void NaoQiWrapper::executeMotion() {
    motion->setAngles(joints, angles, fractionMaxSpeed);
    // std::cout << "Executing Motion" << std::endl;
}

float NaoQiWrapper::degreeToRad(float _angle){
    return (_angle * M_PI) / 180;
}

float NaoQiWrapper::getRandom(float min, float max) {
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

void NaoQiWrapper::shutdown(){
    std::cout << ">>> Setting Stiffness to 0.0" << std::endl;
    setStiff(1.0f);
    motion->setStiffnesses(joints, stiff);
}
