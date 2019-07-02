#include "robot/lift.hpp"
#include <memory>
#include "main.h"
#include "constants.hpp"
#include "controller/multiController.hpp"
#include "util.hpp"

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
        util::delayUntil([=] {
            return isDown() || pros::millis() > startingTime + 1000;
        });
        controller->getMotor()->tarePosition();
        controller->moveVoltage(0);
    }

}
