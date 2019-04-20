#pragma once

#include "main.h"

namespace robot::capIntake {

    extern Motor motor;
    extern AsyncPosIntegratedController controller;
    extern Potentiometer potentiometer;

    void initialize();
    void resetPosition();

}
