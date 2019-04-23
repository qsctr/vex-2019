#pragma once

#include "main.h"
#include "controller/multiController.hpp"

namespace robot::capIntake {

    namespace positions {
        constexpr double groundPickup = -30;
        constexpr double flat = 0;
        constexpr double vertical = 265;
        constexpr double flip = 300;
        constexpr double lowPoleDelivery = -10;
        constexpr double highPoleDelivery = 70;
    }

    extern MultiController controller;
    extern Potentiometer potentiometer;

    void resetPosition();

}
