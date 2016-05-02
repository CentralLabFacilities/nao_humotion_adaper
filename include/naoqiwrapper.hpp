// Author: Florian Lier [flier AT techfak.uni-bielefeld DOT de]

/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#pragma once

// STD
#include <vector>
#include <time.h>
#include <string>
#include <iostream>
#include <math.h>

// NAO
#include <iostream>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alproxies/almemoryproxy.h>
#include <qi/os.hpp>


class NaoQiWrapper {

public:
    NaoQiWrapper(std::string robot_ip, std::string _robot_port);
    ~NaoQiWrapper();
    void setHeadYaw(float _yaw);
    void setHeadPitch(float _pitch);
    void printDataList();
    void setFractionSpeed(float _speed);
    void executeMotion();
    void shutdown();
    void wake();
    void rest();
    float getHeadPitch();
    float getHeadYaw();
    float getHeadPitchVelocity();
    float getHeadYawVelocity();
    float getRandom(float _min, float _max);
private:
    void setStiff(float _stiff);
    float degreeToRad(float _angle);
    float fractionMaxSpeed;
    bool useSensors = true;
    bool skip = true;
    int divider = 0;
    int robot_port;
    std::vector<float> sensor_angles;
    std::string robot_ip;
    AL::ALMotionProxy *motion;
    AL::ALRobotPostureProxy *robot_posture;
    AL::ALMemoryProxy *memory_proxy;
    AL::ALValue joints;
    AL::ALValue angles;
    AL::ALValue stiff;
};
