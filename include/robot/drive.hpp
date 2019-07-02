#pragma once

#include "main.h"

namespace robot::drive {

    extern std::shared_ptr<ChassisControllerIntegrated> controller;

    void initialize();

}
