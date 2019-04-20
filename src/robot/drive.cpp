#include "main.h"
#include "robot/drive.hpp"

namespace robot::drive {

    ChassisControllerIntegrated controller = ChassisControllerFactory::create(
        {3, 20}, {-2, -12}, AbstractMotor::gearset::green, {4.25_in, 14_in});

    void initialize() {
        controller.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
