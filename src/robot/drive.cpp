#include "main.h"
#include "robot/drive.hpp"

namespace robot::drive {

    MotorGroup left = {3, 20};
    MotorGroup right = {-2, -12};
    std::shared_ptr<ChassisControllerIntegrated> controller;

    void initialize() {
        controller = ChassisControllerFactory::createPtr(left, right,
            AbstractMotor::gearset::green, {4.25_in, 14_in});
        controller->setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
