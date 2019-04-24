#include "main.h"
#include "constants.hpp"
#include "robot/lift.hpp"

namespace robot::lift {

    std::shared_ptr<MultiController> controller;
    // MultiController controller {std::make_shared<Motor>(11),
    //     AbstractMotor::gearset::red, AbstractMotor::brakeMode::brake};
    ADIButton leftLimitSwitch {'G'};
    ADIButton rightLimitSwitch {'H'};

    bool isDown() {
        return leftLimitSwitch.isPressed() && rightLimitSwitch.isPressed();
    }

    void reset() {
        controller->moveVoltage(-1);
        while (!(leftLimitSwitch.isPressed() && rightLimitSwitch.isPressed())) {
            pros::Task::delay(10);
        }
        controller->getMotor()->tarePosition();
        controller->moveVoltage(0);
    }

}
