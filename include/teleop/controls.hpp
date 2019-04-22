#pragma once

#include "main.h"

namespace teleop {

    namespace controllerIds {
        constexpr auto cap {ControllerId::master};
        constexpr auto ball {ControllerId::partner};
    }

    namespace controls {
        constexpr auto capDriveLeft {ControllerAnalog::leftY};
        constexpr auto capDriveRight {ControllerAnalog::rightY};
        constexpr auto ballDriveForward {ControllerAnalog::leftY};
        constexpr auto ballDriveYaw {ControllerAnalog::rightX};
        extern ControllerButton manualLiftUp;
        extern ControllerButton manualLiftDown;
        extern ControllerButton manualCapIntakeIn;
        extern ControllerButton manualCapIntakeOut;
        extern ControllerButton groundPickup;
        extern ControllerButton lowPoleDelivery;
        extern ControllerButton highPoleDelivery;
        extern ControllerButton lowPolePickup;
        extern ControllerButton highPolePickup;
        extern ControllerButton flipCap;
        extern ControllerButton capIntakeUp;
        extern ControllerButton capIntakeFlat;
        extern ControllerButton ballDriveAdjustForward;
        extern ControllerButton ballDriveAdjustBackward;
        extern ControllerButton ballDriveAdjustLeft;
        extern ControllerButton ballDriveAdjustRight;
        extern ControllerButton shoot;
        extern ControllerButton ballIntakeIn;
        extern ControllerButton ballIntakeOut;
    }

}
