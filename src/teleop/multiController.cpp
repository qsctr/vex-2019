#include "main.h"
#include "constants.hpp"
#include "teleop/multiController.hpp"

namespace teleop {

    MultiController::MultiController(AbstractMotor& motor,
    AsyncPosIntegratedController& posController) :
        motor {motor},
        posController {posController},
        maxVelocity {toUnderlyingType(motor.getGearing())},
        presetActive {false}
        {}

    void MultiController::setPreset(double position, double velocityScale) {
        posController.setMaxVelocity(maxVelocity * velocityScale);
        posController.setTarget(position);
        if (!presetActive) {
            posController.flipDisable(false);
        }
        presetActive = true;
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
        if (presetActive) {
            posController.flipDisable(true);
        }
        motor.moveVoltage(MAX_VOLTAGE * voltageScale);
        presetActive = false;
    }

    void MultiController::moveManualDefault(double voltageScale) {
        if (!presetActive) {
            moveManualOverride(voltageScale);
        }
    }

    void MultiController::update() {
        if (presetActive && onSettled && posController.isSettled()) {
            auto onSettledCopy = onSettled.value();
            onSettledCopy();
        }
    }

}
