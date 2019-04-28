#pragma once

#include "main.h"

namespace robot::drive {

    extern MotorGroup left;
    extern MotorGroup right;
    extern ChassisControllerIntegrated controller;

    void initialize();

}
