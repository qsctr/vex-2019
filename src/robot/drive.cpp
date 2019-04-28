#include "main.h"
#include "robot/drive.hpp"

namespace robot::drive {

    MotorGroup left = {3, 20};
    MotorGroup right = {-2, -12};
    ChassisControllerIntegrated controller = ChassisControllerFactory::create(
        left, right, AbstractMotor::gearset::green, {4.25_in, 14_in});

    void initialize() {
        controller.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
