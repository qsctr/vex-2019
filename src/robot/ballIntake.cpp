#include "main.h"
#include "robot/ballIntake.hpp"

namespace robot::ballIntake {

    std::shared_ptr<VoltageController> controller;

    void initialize() {
        controller = std::make_shared<VoltageController>(
            std::make_shared<Motor>(4),
            AbstractMotor::gearset::green,
            AbstractMotor::brakeMode::brake);
    }

}
