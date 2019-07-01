#pragma once

#include "main.h"
#include "controller/multiController.hpp"

namespace robot::lift {

    namespace positions {
        constexpr double initialGroundPickup = -50;
        constexpr double holdGroundPickup = 0;
        constexpr double lowPoleDelivery = 650;
        constexpr double highPoleDelivery = 800;
        constexpr double lowPoleDelivery2 = 400;
        constexpr double highPoleDelivery2 = 500;
        constexpr double lowPolePickup = 400;
        constexpr double highPolePickup = 550;
    }

    extern std::shared_ptr<MultiController> controller;
    extern ADIButton leftLimitSwitch;
    extern ADIButton rightLimitSwitch;

    void initialize();
    bool isDown();
    void reset();

}
