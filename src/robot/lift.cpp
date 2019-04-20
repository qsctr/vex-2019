#include "main.h"
#include "constants.hpp"
#include "robot/lift.hpp"

constexpr auto gearing = AbstractMotor::gearset::red;

namespace robot::lift {

    Motor motor {11};
    AsyncPosIntegratedController controller =
        AsyncControllerFactory::posIntegrated(motor, toUnderlyingType(gearing));
    ADIButton leftLimitSwitch {'G'};
    ADIButton rightLimitSwitch {'H'};

    void initialize() {
        motor.setGearing(gearing);
        motor.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

    void reset() {
        motor.moveVoltage(-MAX_VOLTAGE);
        while (!(leftLimitSwitch.isPressed() && rightLimitSwitch.isPressed())) {
            pros::Task::delay(10);
        }
        motor.tarePosition();
        motor.moveVoltage(0);
    }

}
