/*
 * Copyright (c) 2012-2016 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#include "naojointinterface.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
    NaoJointInterface nji(argv[1], argv[2]);
    int idx = 0;

    nji.setHeadPitch(0.0f);
    nji.setHeadYaw(0.0f);
    nji.executeMotion();
    qi::os::sleep(5.0f);

    while(idx<4) {
        qi::os::sleep(5.0f);
        nji.setHeadPitch(nji.getRandom(-35.0f, 28.0f));
        nji.setHeadYaw(nji.getRandom(-50.0f, 50.0f));
        nji.executeMotion();
        idx++;
    }

    return 0;

}
