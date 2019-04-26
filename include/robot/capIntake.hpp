#pragma once

#include "main.h"
#include "controller/multiController.hpp"

namespace robot::capIntake {
 
    namespace positions {
        constexpr double groundPickup = -60;
        constexpr double flat = -25;
        constexpr double vertical = 235;
        constexpr double flip = 270;
        constexpr double lowPoleDelivery = -60;
        constexpr double highPoleDelivery = 40;
    }

    extern std::shared_ptr<MultiController> controller;
    extern Potentiometer potentiometer;

    void resetPosition();

}
