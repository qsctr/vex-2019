#pragma once

#include "main.h"

namespace robot {

    extern MotorGroup baseLeft;
    extern MotorGroup baseRight;
    extern ChassisControllerIntegrated drive;
    extern MotorGroup lift;
    extern Motor intake;

    void setup();

}
