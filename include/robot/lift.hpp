#pragma once

#include "main.h"

namespace robot::lift {

    extern Motor motor;
    extern AsyncPosIntegratedController controller;
    extern ADIButton leftLimitSwitch;
    extern ADIButton rightLimitSwitch;

    void initialize();

}
