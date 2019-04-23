#include "main.h"
#include "controller/multiController.hpp"

MultiController::MultiController(std::shared_ptr<AbstractMotor> motor,
AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode)
: VoltageController(motor, gearing, brakeMode),
maxVelocity {toUnderlyingType(gearing)},
posController {std::make_unique<AsyncPosIntegratedController>(
    std::shared_ptr(motor), maxVelocity, TimeUtilFactory::create())}
{
    posController->flipDisable(true);
}

double MultiController::getPosition() {
    return motor->getPosition();
}

void MultiController::setPosition(double position, double velocityScale) {
    posController->setMaxVelocity(maxVelocity * velocityScale);
    posController->setTarget(position);
    if (posController->isDisabled()) {
        posController->flipDisable(false);
    }
}

void MultiController::movePosition(double position, double velocityScale) {
    setPosition(position, velocityScale);
    onSettled = std::nullopt;
}

void MultiController::movePosition(double position,
std::function<void()> settledCb) {
    movePosition(position, defaultVelocityScale, settledCb);
}

void MultiController::movePosition(double position, double velocityScale,
std::function<void()> settledCb) {
    setPosition(position, velocityScale);
    onSettled = settledCb;
}

void MultiController::moveVoltage(double voltageScale) {
    if (!posController->isDisabled()) {
        posController->flipDisable(true);
    }
    VoltageController::moveVoltage(voltageScale);
}

void MultiController::moveVoltageDefault(double voltageScale) {
    if (posController->isDisabled()) {
        VoltageController::moveVoltage(voltageScale);
    }
}

void MultiController::checkSettled() {
    if (!posController->isDisabled() && onSettled
    && posController->isSettled()) {
        auto settledCb = onSettled.value();
        onSettled = std::nullopt;
        settledCb();
    }
}

void MultiController::waitUntilSettled() {
    if (!posController->isDisabled()) {
        posController->waitUntilSettled();
    }
}
