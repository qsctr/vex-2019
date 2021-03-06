#include "controller/voltageController.hpp"
#include <memory>
#include "main.h"

VoltageController::VoltageController(std::shared_ptr<AbstractMotor> motor,
AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode)
: motor {motor} {
    motor->setGearing(gearing);
    motor->setBrakeMode(brakeMode);
}

const std::shared_ptr<AbstractMotor> VoltageController::getMotor() {
    return motor;
}

void VoltageController::moveVoltage(double voltageScale) {
    motor->moveVoltage(maxVoltage * voltageScale);
}
