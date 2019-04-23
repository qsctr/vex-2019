#include "main.h"
#include "constants.hpp"
#include "robot.hpp"
#include "teleop/controls.hpp"

#include <cstdio>

namespace teleop {

    constexpr float ANALOG_DEADBAND {0.05};

    namespace controllers {
        Controller cap {controllerIds::cap};
        Controller ball {controllerIds::ball};
    }

    constexpr bool analogActive(float leftAnalog, float rightAnalog) {
        return abs(leftAnalog) > ANALOG_DEADBAND
            || abs(rightAnalog) > ANALOG_DEADBAND;
    }

    void lowPoleFlip3() { robot::lift::controller.movePosition(400); }
    void lowPoleFlip2() { robot::capIntake::controller.movePosition(-10, 0.5, lowPoleFlip3); }
    void lowPoleFlip() { robot::capIntake::controller.movePosition(300, lowPoleFlip2); }

    void highPoleFlip3() { robot::lift::controller.movePosition(500); }
    void highPoleFlip2() { robot::capIntake::controller.movePosition(70, 0.5, highPoleFlip3); }
    void highPoleFlip() { robot::capIntake::controller.movePosition(300, highPoleFlip2); }

    std::optional<double> getSideDrivePower(float analog,
    ControllerButton adjustPositive, ControllerButton adjustNegative) {
        if (abs(analog) > ANALOG_DEADBAND)
            return analog;
        if (adjustPositive.isPressed())
            return 0.2;
        if (adjustNegative.isPressed())
            return -0.2;
        return std::nullopt;
    }

    void drive() {
        float capLeft = controllers::cap.getAnalog(controls::capDriveLeft);
        float capRight = controllers::cap.getAnalog(controls::capDriveRight);
        if (!analogActive(capLeft, capRight)) {
            float ballForward =
                controllers::ball.getAnalog(controls::ballDriveForward);
            float ballYaw =
                controllers::ball.getAnalog(controls::ballDriveForward);
            auto forwardPower = getSideDrivePower(ballForward,
                controls::ballDriveAdjustForward,
                controls::ballDriveAdjustBackward);
            auto yawPower = getSideDrivePower(ballYaw,
                controls::ballDriveAdjustRight,
                controls::ballDriveAdjustLeft);
            if (forwardPower || yawPower) {
                robot::drive::controller.arcade(-forwardPower.value_or(0),
                    yawPower.value_or(0));
                return;
            }
        }
        robot::drive::controller.tank(capLeft, capRight);
    }

}

void opcontrol() {
    using namespace teleop;
    robot::lift::reset();
    int i = 0;
    while (true) {
        drive();
        if (controls::groundPickup.changedToPressed()) {
            robot::lift::controller.movePosition(-50);
            robot::capIntake::controller.movePosition(-30);
        } else if (controls::lowPoleDelivery.changedToPressed()) {
            robot::lift::controller.movePosition(650);
            robot::capIntake::controller.movePosition(-10);
        } else if (controls::highPoleDelivery.changedToPressed()) {
            robot::lift::controller.movePosition(750);
            robot::capIntake::controller.movePosition(70);
        } else if (controls::lowPolePickup.changedToPressed()) {
            robot::lift::controller.movePosition(350);
            robot::capIntake::controller.movePosition(0);
        } else if (controls::highPolePickup.changedToPressed()) {
            robot::lift::controller.movePosition(500);
            robot::capIntake::controller.movePosition(0);
        } else if (controls::flipCap.changedToPressed()) {
            // auto liftTarget = robot::lift::controller.getTarget();
            // if (!robot::lift::controller.isDisabled() && liftTarget == 350) {
            //     robot::lift::controller.movePosition(650, lowPoleFlip);
            // } else if (!robot::lift::controller.isDisabled() && liftTarget == 500) {
            //     robot::lift::controller.movePosition(750, highPoleFlip);
            // } else {
            //     robot::capIntake::controller.movePosition(300, [&] {
            //         robot::capIntake::controller.movePosition(0, 0.5);
            //     });
            // }
        } else if (controls::capIntakeUp.changedToPressed()) {
            robot::capIntake::controller.movePosition(300);
        } else if (controls::capIntakeFlat.changedToPressed()) {
            robot::capIntake::controller.movePosition(0);
        } else {
            if (controls::manualLiftUp.isPressed()) {
                robot::lift::controller.moveVoltage(1);
            } else if (controls::manualLiftDown.isPressed()) {
                robot::lift::controller.moveVoltage(-1);
            } else {
                robot::lift::controller.moveVoltageDefault(0);
            }
            if (controls::manualCapIntakeIn.isPressed()) {
                robot::capIntake::controller.moveVoltage(1);
            } else if (controls::manualCapIntakeOut.isPressed()) {
                robot::capIntake::controller.moveVoltage(-1);
            } else {
                robot::capIntake::controller.moveVoltageDefault(0);
            }
        }
        if (controls::shoot.isPressed()) {
            robot::shooter::controller.moveVoltage(1);
        } else {
            robot::shooter::controller.moveVoltage(0);
        }
        if (controls::ballIntakeIn.isPressed()) {
            robot::ballIntake::controller.moveVoltage(1);
        } else if (controls::ballIntakeOut.isPressed()) {
            robot::ballIntake::controller.moveVoltage(-1);
        } else {
            robot::ballIntake::controller.moveVoltage(0);
        }
        robot::lift::controller.checkSettled();
        robot::capIntake::controller.checkSettled();
        if (robot::lift::leftLimitSwitch.isPressed() && robot::lift::rightLimitSwitch.isPressed()) {
            robot::lift::controller.getMotor()->tarePosition();
        }
        printf("%f %f\n", robot::capIntake::controller.getPosition(), robot::capIntake::potentiometer.get());
        if (i == 100) {
            controllers::cap.setText(0, 0, std::to_string(robot::capIntake::controller.getPosition()));
            i = 0;
        }
        pros::Task::delay(10);
        i++;
    }
}
