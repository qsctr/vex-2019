#include "robot/ballIntake.hpp"
#include <memory>
#include "main.h"
#include "controller/voltageController.hpp"

namespace robot::ballIntake {

    std::shared_ptr<VoltageController> controller;

    void initialize() {
        controller = std::make_shared<VoltageController>(
            std::make_shared<Motor>(4),
            AbstractMotor::gearset::green,
            AbstractMotor::brakeMode::brake);
    }

}
