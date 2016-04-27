// Author: Florian Lier [flier AT techfak.uni-bielefeld DOT de]

/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#pragma once

// HUMOTION
#include <humotion/server/joint_interface.h>
#include <humotion/server/server.h>
#include <humotion/timestamp.h>

// STD
#include <boost/bimap.hpp>

// NAO
#include "naoqiwrapper.hpp"

// ROS
#include "ros/ros.h"

class NaoJointInterface : public humotion::server::JointInterface {

public:
    NaoJointInterface(std::string _robot_ip, std::string _robot_port);
    ~NaoJointInterface();
    void run();
    void incoming_jointstates();
    void shutdown();
    static const int MAIN_LOOP_FREQUENCY = 50;

protected:
    void disable_joint(int n);
    void publish_target(int n, float position, float velocity);
    void enable_joint(int n);
    void execute_motion();

private:
    void store_dummy_data(int id, humotion::Timestamp timestamp);
    void store_min_max(int id, float min, float max);
    void set_eyelid_angle(double angle);
    void set_eyebrow_angle(int id);
    void set_mouth();
    void init_joints();

    NaoQiWrapper *nji;

    double lid_angle;

    std::string robot_ip;
    std::string robot_port;

    int lid_opening_previous;
    int previous_mouth_state;

    float last_pos_eye_vergence;
    float last_pos_eye_pan;
    float last_vel_eye_vergence;
    float last_vel_eye_pan;

    void store_joint(int id, float value);
    void set_target_in_positionmode(int id, double value);
    void set_target_in_velocitymode(int id, double value);

    int convert_enum_to_motorid(int e);
    int convert_motorid_to_enum(int id);

    typedef boost::bimap<int, int> enum_id_bimap_t;
    typedef enum_id_bimap_t::value_type enum_id_bimap_entry_t;
    enum_id_bimap_t enum_id_bimap;
};
