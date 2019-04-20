#include "main.h"
#include "constants.hpp"
#include "teleop/multiController.hpp"

namespace teleop {

    MultiController::MultiController(AbstractMotor& motor,
    AsyncPosIntegratedController& posController) :
        motor {motor},
        posController {posController},
        maxVelocity {toUnderlyingType(motor.getGearing())}
    {
        posController.flipDisable(true);
    }

    void MultiController::setPreset(double position, double velocityScale) {
        posController.setMaxVelocity(maxVelocity * velocityScale);
        posController.setTarget(position);
        if (posController.isDisabled()) {
            posController.flipDisable(false);
        }
    }

    void MultiController::movePreset(double position, double velocityScale) {
        setPreset(position, velocityScale);
        onSettled = std::nullopt;
    }

    void MultiController::movePreset(double position,
    std::function<void()> cb) {
        movePreset(position, 1, cb);
    }

    void MultiController::movePreset(double position, double velocityScale,
    std::function<void()> cb) {
        setPreset(position, velocityScale);
        onSettled = cb;
    }

    void MultiController::moveManualOverride(double voltageScale) {
        if (!posController.isDisabled()) {
            posController.flipDisable(true);
        }
        motor.moveVoltage(MAX_VOLTAGE * voltageScale);
    }

    void MultiController::moveManualDefault(double voltageScale) {
        if (posController.isDisabled()) {
            moveManualOverride(voltageScale);
        }
    }

    void MultiController::update() {
        if (!posController.isDisabled() && onSettled && posController.isSettled()) {
            auto cb = onSettled.value();
            onSettled = std::nullopt;
            cb();
        }
    }

}
