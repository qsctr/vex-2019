#pragma once

#include "main.h"
#include "controller/multiController.hpp"

namespace robot::lift {

    namespace positions {
        constexpr double initialGroundPickup = -50;
        constexpr double holdGroundPickup = 0;
        constexpr double lowPoleDelivery = 650;
        constexpr double highPoleDelivery = 750;
        constexpr double lowPolePickup = 350;
        constexpr double highPolePickup = 500;
    }

    extern MultiController controller;
    extern ADIButton leftLimitSwitch;
    extern ADIButton rightLimitSwitch;

    void reset();

}
