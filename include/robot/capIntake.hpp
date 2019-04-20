#pragma once

#include "main.h"

namespace robot::capIntake {

    namespace positions {
        constexpr double groundPickup = -30;
        constexpr double flat = 0;
        constexpr double vertical = 265;
        constexpr double flip = 300;
        constexpr double lowPoleDelivery = -10;
        constexpr double highPoleDelivery = 70;
    }

    extern Motor motor;
    extern AsyncPosIntegratedController controller;
    extern Potentiometer potentiometer;

    void initialize();
    void resetPosition();

}
