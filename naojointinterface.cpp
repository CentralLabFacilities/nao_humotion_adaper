/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#include "naojointinterface.hpp"

NaoJointInterface::NaoJointInterface(std::string _robot_ip, std::string _robot_port) {
    robot_ip = _robot_ip;
    std::cout << ">>> Using Robot " << _robot_ip << ":" << std::atoi(_robot_port.c_str()) << std::endl;
    motion = new AL::ALMotionProxy(_robot_ip, std::atoi(_robot_port.c_str()));
    fractionMaxSpeed = 0.2f;
    joints = AL::ALValue::array("HeadYaw", "HeadPitch");
    angles = AL::ALValue::array(0.0f, 0.0f);
    stiff = AL::ALValue::array(1.0f, 1.0f);
}

NaoJointInterface::~NaoJointInterface(){ }

void NaoJointInterface::setHeadYaw(float _value) {
    angles[0] = degreeToRad(_value);
}

void NaoJointInterface::setHeadPitch(float _value) {
    angles[1] = degreeToRad(_value);
}

void NaoJointInterface::setFractionSpeed(float _speed) {
    fractionMaxSpeed = _speed;
}

void NaoJointInterface::setStiff(float _stiff) {
    for (int i=0; i < joints.getSize(); i++) {
        stiff[i] = _stiff;
    }
}

void NaoJointInterface::executeMotion() {
    setStiff(1.0f);
    motion->setStiffnesses(joints, stiff);
    qi::os::sleep(2.0f);
    motion->setAngles(joints, angles, fractionMaxSpeed);
    qi::os::sleep(2.0f);
    setStiff(0.0f);
    motion->setStiffnesses(joints, stiff);
}

float NaoJointInterface::degreeToRad(float _angle){
    return (_angle * M_PI) / 180;
}

float NaoJointInterface::getRandom(float min, float max) {
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}
