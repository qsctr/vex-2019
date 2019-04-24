#include "main.h"
#include "controller/multiController.hpp"
#include "util/overload.hpp"

MultiController::MultiController(std::shared_ptr<AbstractMotor> motor,
AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode)
: VoltageController(motor, gearing, brakeMode),
maxVelocity {toUnderlyingType(gearing)},
posController {std::make_unique<AsyncPosIntegratedController>(
    std::shared_ptr(motor), maxVelocity, TimeUtilFactory::create())}
{
    posController->flipDisable(true);
}

std::optional<double> MultiController::getTarget() {
    if (posController->isDisabled()) {
        return std::nullopt;
    }
    return posController->getTarget();
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
    callback = std::nullopt;
}

void MultiController::movePosition(double position,
std::function<void ()> settledCallback) {
    movePosition(position, defaultVelocityScale, settledCallback);
}

void MultiController::movePosition(double position, double velocityScale,
std::function<void ()> settledCallback) {
    setPosition(position, velocityScale);
    callback = SettledCallback {settledCallback};
}

void MultiController::movePosition(double position,
std::function<bool ()> condition, std::function<void ()> customCallback) {
    movePosition(position, defaultVelocityScale, condition, customCallback);
}

void MultiController::movePosition(double position, double velocityScale,
std::function<bool ()> condition, std::function<void ()> customCallback) {
    setPosition(position, velocityScale);
    callback = CustomCallback {condition, customCallback};
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

void MultiController::execCallback(std::function<void ()> f) {
    callback = std::nullopt;
    f();
}

void MultiController::checkCallback() {
    if (!posController->isDisabled() && callback) {
        std::visit(overload(
            [&](SettledCallback sc) {
                if (posController->isSettled()) {
                    execCallback(sc.callback);
                }
            },
            [&](CustomCallback cc) {
                if (cc.condition()) {
                    execCallback(cc.callback);
                }
            }
        ), callback.value());
    }
}

void MultiController::waitUntilSettled() {
    if (!posController->isDisabled()) {
        posController->waitUntilSettled();
    }
}
