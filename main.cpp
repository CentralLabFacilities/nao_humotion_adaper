// Author: Florian Lier [flier AT techfak.uni-bielefeld DOT de]

/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#include "naojointinterface.hpp"
#include <unistd.h>

int main(int argc, char *argv[]){

    if (argc != 4){
        printf("> ERROR: Invalid number of parameters passed to server!\n\n");
        printf("USAGE   : %s <humotion base topic> <robot_ip> <robot_port> \n\n",argv[0]);
        printf("EXAMPLE : %s /nao 192.168.1.2 1234 \n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    std::string humotion_scope = argv[1];

    NaoJointInterface *jointinterface = new NaoJointInterface(argv[2], argv[3]);
    jointinterface->incoming_jointstates();
    humotion::server::Server *humotion_server = new humotion::server::Server(humotion_scope, "ROS", jointinterface);

    jointinterface->run();

    while(humotion_server->ok()){
        jointinterface->incoming_jointstates();
        usleep(1000*15);
    }

    jointinterface->shutdown();

    printf(">>> ROS Connection closed, exiting now.\n");

    return 0;
}

