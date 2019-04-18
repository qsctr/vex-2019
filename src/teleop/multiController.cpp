#include "main.h"
#include "constants.hpp"
#include "teleop/multiController.hpp"

namespace teleop {

    MultiController::MultiController(AbstractMotor& motor,
    AsyncPosIntegratedController posController) :
        motor {motor},
        posController {posController},
        maxVelocity {toUnderlyingType(motor.getGearing())}
        {}

    void MultiController::movePreset(double position, double velocityScale) {
        posController.setMaxVelocity(maxVelocity * velocityScale);
        state = std::make_pair(position, std::nullopt);
    }

    void MultiController::moveManual(double voltageScale) {
        state = MAX_VOLTAGE * voltageScale;
    }

    void MultiController::update() {
        std::visit((struct {

        } {}), state);
    }

}
