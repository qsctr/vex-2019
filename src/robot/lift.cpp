#include "main.h"
#include "constants.hpp"
#include "robot/lift.hpp"

namespace robot::lift {

    std::shared_ptr<MultiController> controller;
    ADIButton leftLimitSwitch {'G'};
    ADIButton rightLimitSwitch {'H'};

    void initialize() {
        controller = std::make_shared<MultiController>(
            std::make_shared<Motor>(11),
            AbstractMotor::gearset::red,
            AbstractMotor::brakeMode::brake);
    }

    bool isDown() {
        // return leftLimitSwitch.isPressed() && rightLimitSwitch.isPressed();
        return rightLimitSwitch.isPressed();
    }

    void reset() {
        auto startingTime = pros::millis();
        controller->moveVoltage(-1);
        while (!isDown() && pros::millis() < startingTime + 1000) {
            pros::Task::delay(10);
        }
        controller->getMotor()->tarePosition();
        controller->moveVoltage(0);
    }

}
