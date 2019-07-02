#include "robot/shooter.hpp"
#include <memory>
#include "main.h"
#include "controller/voltageController.hpp"

namespace robot::shooter {

    std::shared_ptr<VoltageController> controller;

    void initialize() {
        controller = std::make_shared<VoltageController>(
            std::make_shared<Motor>(-1),
            AbstractMotor::gearset::red,
            AbstractMotor::brakeMode::brake);
    }

}
