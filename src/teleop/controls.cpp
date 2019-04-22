#include "main.h"
#include "teleop/controls.hpp"

namespace teleop::controls {
    ControllerButton manualLiftUp {controllerIds::cap, ControllerDigital::R1};
    ControllerButton manualLiftDown {controllerIds::cap, ControllerDigital::R2};
    ControllerButton manualCapIntakeIn
        {controllerIds::cap, ControllerDigital::L1};
    ControllerButton manualCapIntakeOut
        {controllerIds::cap, ControllerDigital::L2};
    ControllerButton groundPickup {controllerIds::cap, ControllerDigital::B};
    ControllerButton lowPoleDelivery {controllerIds::cap, ControllerDigital::A};
    ControllerButton highPoleDelivery
        {controllerIds::cap, ControllerDigital::X};
    ControllerButton lowPolePickup
        {controllerIds::cap, ControllerDigital::left};
    ControllerButton highPolePickup {controllerIds::cap, ControllerDigital::up};
    ControllerButton flipCap {controllerIds::cap, ControllerDigital::right};
    ControllerButton capIntakeUp {controllerIds::cap, ControllerDigital::Y};
    ControllerButton capIntakeFlat
        {controllerIds::cap, ControllerDigital::down};
    ControllerButton ballDriveAdjustForward
        {controllerIds::ball, ControllerDigital::up};
    ControllerButton ballDriveAdjustBackward
        {controllerIds::ball, ControllerDigital::down};
    ControllerButton ballDriveAdjustLeft
        {controllerIds::ball, ControllerDigital::A};
    ControllerButton ballDriveAdjustRight
        {controllerIds::ball, ControllerDigital::Y};
    ControllerButton shoot {controllerIds::ball, ControllerDigital::R1};
    ControllerButton ballIntakeIn {controllerIds::ball, ControllerDigital::L1};
    ControllerButton ballIntakeOut {controllerIds::ball, ControllerDigital::L2};
}
