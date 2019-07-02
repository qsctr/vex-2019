#include "robot/drive.hpp"
#include "main.h"
#include <memory>

namespace robot::drive {

    std::shared_ptr<ChassisControllerIntegrated> controller;

    void initialize() {
        controller = ChassisControllerFactory::createPtr(
            {3, 20}, {-2, -12},
            AbstractMotor::gearset::green,
            {4.25_in, 14_in});
        controller->setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
