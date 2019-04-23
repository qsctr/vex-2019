#include "main.h"
#include "constants.hpp"
#include "robot/lift.hpp"

constexpr auto gearing = AbstractMotor::gearset::red;

namespace robot::lift {

    MultiController controller {std::make_shared<Motor>(11),
        AbstractMotor::gearset::red, AbstractMotor::brakeMode::brake};
    ADIButton leftLimitSwitch {'G'};
    ADIButton rightLimitSwitch {'H'};

    void reset() {
        controller.moveVoltage(-1);
        while (!(leftLimitSwitch.isPressed() && rightLimitSwitch.isPressed())) {
            pros::Task::delay(10);
        }
        controller.getMotor()->tarePosition();
        controller.moveVoltage(0);
    }

}
