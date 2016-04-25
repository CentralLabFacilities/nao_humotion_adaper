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
#include <qi/os.hpp>

class NaoJointInterface {

public:
    NaoJointInterface(std::string robot_ip, std::string _robot_port);
    ~NaoJointInterface();
    void setHeadYaw(float);
    void setHeadPitch(float);
    void setFractionSpeed(float speed);
    float getRandom(float min, float max);
    void executeMotion();
private:
    void setStiff(float stiff);
    float degreeToRad(float angle);
    float fractionMaxSpeed;
    std::string robot_ip;
    AL::ALMotionProxy *motion;
    AL::ALValue joints;
    AL::ALValue angles;
    AL::ALValue stiff;
};