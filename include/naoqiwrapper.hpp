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
#include <qi/os.hpp>


class NaoQiWrapper {

public:
    NaoQiWrapper(std::string robot_ip, std::string _robot_port);
    ~NaoQiWrapper();
    void setHeadYaw(float _yaw);
    void setHeadPitch(float _pitch);
    float getHeadPitch();
    float getHeadYaw();
    void setFractionSpeed(float _speed);
    float getRandom(float _min, float _max);
    void executeMotion();
    void shutdown();
    void wake();
    void rest();
private:
    void setStiff(float _stiff);
    float degreeToRad(float _angle);
    float fractionMaxSpeed;
    bool useSensors = true;
    bool skip = true;
    int divider = 0;
    std::vector<float> sensor_angles;
    std::string robot_ip;
    AL::ALMotionProxy *motion;
    AL::ALRobotPostureProxy *robot_posture;
    AL::ALValue joints;
    AL::ALValue angles;
    AL::ALValue stiff;
};
