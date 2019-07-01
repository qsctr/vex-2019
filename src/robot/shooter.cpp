#include "main.h"
#include "robot/shooter.hpp"

namespace robot::shooter {

    std::shared_ptr<VoltageController> controller;

    void initialize() {
        controller = std::make_shared<VoltageController>(
            std::make_shared<Motor>(-1),
            AbstractMotor::gearset::red,
            AbstractMotor::brakeMode::brake);
    }

}
