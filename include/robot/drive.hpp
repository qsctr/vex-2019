#pragma once

#include "main.h"

namespace robot::drive {

    extern MotorGroup left;
    extern MotorGroup right;
    extern std::shared_ptr<ChassisControllerIntegrated> controller;

    void initialize();

}
