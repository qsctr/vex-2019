#include "controller/multiController.hpp"
#include <functional>
#include <memory>
#include <optional>
#include <variant>
#include "main.h"
#include "util/overload.hpp"

MultiController::MultiController(std::shared_ptr<AbstractMotor> motor,
AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode) :
    VoltageController(motor, gearing, brakeMode),
    maxVelocity {toUnderlyingType(gearing)},
    posController {std::make_unique<AsyncPosIntegratedController>(
        std::shared_ptr(motor), maxVelocity, TimeUtilFactory::create())}
{
    posController->flipDisable(true);
}

std::optional<double> MultiController::getTarget() {
    if (std::holds_alternative<PositionMode>(state)) {
        return posController->getTarget();
    }
    return std::nullopt;
}

double MultiController::getPosition() {
    return motor->getPosition();
}

void MultiController::setPosition(double position, double velocityScale) {
    posController->setMaxVelocity(maxVelocity * velocityScale);
    posController->setTarget(position);
    if (!std::holds_alternative<PositionMode>(state)) {
        posController->flipDisable(false);
    }
}

void MultiController::movePosition(double position, double velocityScale) {
    setPosition(position, velocityScale);
    state = PositionMode {std::nullopt};
}

void MultiController::movePosition(double position,
std::function<void ()> settledCallback) {
    movePosition(position, defaultVelocityScale, settledCallback);
}

void MultiController::movePosition(double position, double velocityScale,
std::function<void ()> settledCallback) {
    setPosition(position, velocityScale);
    state = PositionMode {PositionMode::SettledCallback {settledCallback}};
}

void MultiController::movePosition(double position,
std::function<bool ()> condition, std::function<void ()> customCallback) {
    movePosition(position, defaultVelocityScale, condition, customCallback);
}

void MultiController::movePosition(double position, double velocityScale,
std::function<bool ()> condition, std::function<void ()> customCallback) {
    setPosition(position, velocityScale);
    state = PositionMode {PositionMode::CustomCallback
        {condition, customCallback}};
}

void MultiController::moveVoltage(double voltageScale) {
    if (std::holds_alternative<PositionMode>(state)) {
        posController->flipDisable(true);
    }
    state = VoltageMode {};
    VoltageController::moveVoltage(voltageScale);
}

void MultiController::moveVoltageDefault(double voltageScale) {
    if (std::holds_alternative<VoltageMode>(state)) {
        VoltageController::moveVoltage(voltageScale);
    }
}

void MultiController::checkCallback() {
    std::visit(overload(
        [&](PositionMode positionState) {
            if (positionState.callback) {
                std::visit(overload(
                    [&](PositionMode::SettledCallback sc) {
                        if (posController->isSettled()) {
                            state = PositionMode {std::nullopt};
                            sc.callback();
                        }
                    },
                    [&](PositionMode::CustomCallback cc) {
                        if (cc.condition()) {
                            state = PositionMode {std::nullopt};
                            cc.callback();
                        }
                    }
                ), positionState.callback.value());
            }
        },
        [](auto&&) {}
    ), state);
}

void MultiController::waitUntilSettled() {
    if (std::holds_alternative<PositionMode>(state)) {
        posController->waitUntilSettled();
    }
}
