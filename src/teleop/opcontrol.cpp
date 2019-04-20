#include "main.h"
#include "constants.hpp"
#include "robot.hpp"
#include "teleop/multiController.hpp"

#include <cstdio>

namespace teleop {

    constexpr auto CAP_CONTROLLER_ID {ControllerId::master};
    constexpr auto BALL_CONTROLLER_ID {ControllerId::partner};

    constexpr float ANALOG_DEADBAND {0.05};

    Controller capController {CAP_CONTROLLER_ID};
    Controller ballController {BALL_CONTROLLER_ID};

    namespace buttons {
        ControllerButton
            manualLiftUp {CAP_CONTROLLER_ID, ControllerDigital::R1},
            manualLiftDown {CAP_CONTROLLER_ID, ControllerDigital::R2},
            manualCapIntakeIn {CAP_CONTROLLER_ID, ControllerDigital::L1},
            manualCapIntakeOut {CAP_CONTROLLER_ID, ControllerDigital::L2},
            groundPickup {CAP_CONTROLLER_ID, ControllerDigital::B},
            lowPoleDelivery {CAP_CONTROLLER_ID, ControllerDigital::A},
            highPoleDelivery {CAP_CONTROLLER_ID, ControllerDigital::X},
            lowPolePickup {CAP_CONTROLLER_ID, ControllerDigital::left},
            highPolePickup {CAP_CONTROLLER_ID, ControllerDigital::up},
            capFlip {CAP_CONTROLLER_ID, ControllerDigital::right},
            capIntakeUp {CAP_CONTROLLER_ID, ControllerDigital::Y},
            capIntakeFlat {CAP_CONTROLLER_ID, ControllerDigital::down},
            ballRightDriveAdjustForward
                {BALL_CONTROLLER_ID, ControllerDigital::X},
            ballRightDriveAdjustBackward
                {BALL_CONTROLLER_ID, ControllerDigital::B},
            ballLeftDriveAdjustForward
                {BALL_CONTROLLER_ID, ControllerDigital::up},
            ballLeftDriveAdjustBackward
                {BALL_CONTROLLER_ID, ControllerDigital::down},
            shoot {BALL_CONTROLLER_ID, ControllerDigital::R1},
            ballIntakeIn {BALL_CONTROLLER_ID, ControllerDigital::L1},
            ballIntakeOut {BALL_CONTROLLER_ID, ControllerDigital::L2};
    }

    namespace multiControllers {
        MultiController lift {robot::lift::motor, robot::lift::controller};
        MultiController capIntake {robot::capIntake::motor,
            robot::capIntake::controller};
    }

    constexpr bool analogActive(float leftAnalog, float rightAnalog) {
        return abs(leftAnalog) > ANALOG_DEADBAND
            || abs(rightAnalog) > ANALOG_DEADBAND;
    }

    void lowPoleFlip3() { multiControllers::lift.movePreset(400); }
    void lowPoleFlip2() { multiControllers::capIntake.movePreset(-10, 0.5, lowPoleFlip3); }
    void lowPoleFlip() { multiControllers::capIntake.movePreset(300, lowPoleFlip2); }

    void highPoleFlip3() { multiControllers::lift.movePreset(500); }
    void highPoleFlip2() { multiControllers::capIntake.movePreset(70, 0.5, highPoleFlip3); }
    void highPoleFlip() { multiControllers::capIntake.movePreset(300, highPoleFlip2); }

    std::optional<double> getSideDrivePower(float analog,
    ControllerButton adjustForward, ControllerButton adjustBackward) {
        if (abs(analog) > ANALOG_DEADBAND)
            return analog;
        if (adjustForward.isPressed())
            return 0.2;
        if (adjustBackward.isPressed())
            return -0.2;
        return std::nullopt;
    }

    std::pair<double, double> getDrivePower() {
        float capLeft = capController.getAnalog(ControllerAnalog::leftY);
        float capRight = capController.getAnalog(ControllerAnalog::rightY);
        float ballLeft = ballController.getAnalog(ControllerAnalog::leftY);
        float ballRight = ballController.getAnalog(ControllerAnalog::rightY);
        if (!analogActive(capLeft, capRight)) {
            auto leftPower = getSideDrivePower(ballLeft,
                buttons::ballLeftDriveAdjustForward,
                buttons::ballLeftDriveAdjustBackward);
            auto rightPower = getSideDrivePower(ballRight,
                buttons::ballRightDriveAdjustForward,
                buttons::ballRightDriveAdjustBackward);
            if (leftPower || rightPower)
                return {-rightPower.value_or(0), -leftPower.value_or(0)};
        }
        return {capLeft, capRight};
    }

}

void opcontrol() {
    using namespace teleop;
    multiControllers::lift.moveManualOverride(-1);
    while (!(robot::lift::leftLimitSwitch.isPressed() &&
    robot::lift::rightLimitSwitch.isPressed())) {
        pros::Task::delay(10);
    }
    robot::lift::motor.tarePosition();
    multiControllers::lift.moveManualDefault(0);
    int i = 0;
    while (true) {
        auto [leftDrivePower, rightDrivePower] = getDrivePower();
        robot::drive::controller.tank(leftDrivePower, rightDrivePower);
        if (buttons::groundPickup.changedToPressed()) {
            multiControllers::lift.movePreset(-50);
            multiControllers::capIntake.movePreset(-30);
        } else if (buttons::lowPoleDelivery.changedToPressed()) {
            multiControllers::lift.movePreset(650);
            multiControllers::capIntake.movePreset(-10);
        } else if (buttons::highPoleDelivery.changedToPressed()) {
            multiControllers::lift.movePreset(750);
            multiControllers::capIntake.movePreset(70);
        } else if (buttons::lowPolePickup.changedToPressed()) {
            multiControllers::lift.movePreset(350);
            multiControllers::capIntake.movePreset(0);
        } else if (buttons::highPolePickup.changedToPressed()) {
            multiControllers::lift.movePreset(500);
            multiControllers::capIntake.movePreset(0);
        } else if (buttons::capFlip.changedToPressed()) {
            auto liftTarget = robot::lift::controller.getTarget();
            if (!robot::lift::controller.isDisabled() && liftTarget == 350) {
                multiControllers::lift.movePreset(650, lowPoleFlip);
            } else if (!robot::lift::controller.isDisabled() && liftTarget == 500) {
                multiControllers::lift.movePreset(750, highPoleFlip);
            } else {
                multiControllers::capIntake.movePreset(300, [&] {
                    multiControllers::capIntake.movePreset(0, 0.5);
                });
            }
        } else if (buttons::capIntakeUp.changedToPressed()) {
            multiControllers::capIntake.movePreset(300);
        } else if (buttons::capIntakeFlat.changedToPressed()) {
            multiControllers::capIntake.movePreset(0);
        } else {
            if (buttons::manualLiftUp.isPressed()) {
                multiControllers::lift.moveManualOverride(1);
            } else if (buttons::manualLiftDown.isPressed()) {
                multiControllers::lift.moveManualOverride(-1);
            } else {
                multiControllers::lift.moveManualDefault(0);
            }
            if (buttons::manualCapIntakeIn.isPressed()) {
                multiControllers::capIntake.moveManualOverride(1);
            } else if (buttons::manualCapIntakeOut.isPressed()) {
                multiControllers::capIntake.moveManualOverride(-1);
            } else {
                multiControllers::capIntake.moveManualDefault(0);
            }
        }
        if (buttons::shoot.isPressed()) {
            robot::shooter::motor.moveVoltage(MAX_VOLTAGE);
        } else {
            robot::shooter::motor.moveVoltage(0);
        }
        if (buttons::ballIntakeIn.isPressed()) {
            robot::ballIntake::motor.moveVoltage(MAX_VOLTAGE);
        } else if (buttons::ballIntakeOut.isPressed()) {
            robot::ballIntake::motor.moveVoltage(-MAX_VOLTAGE);
        } else {
            robot::ballIntake::motor.moveVoltage(0);
        }
        multiControllers::lift.update();
        multiControllers::capIntake.update();
        if (robot::lift::leftLimitSwitch.isPressed() && robot::lift::rightLimitSwitch.isPressed()) {
            robot::lift::motor.tarePosition();
        }
        printf("%f %f\n", robot::capIntake::motor.getPosition(), robot::capIntake::potentiometer.get());
        if (i == 100) {
            capController.setText(0, 0, std::to_string(robot::capIntake::motor.getPosition()));
            i = 0;
        }
        pros::Task::delay(10);
        i++;
    }
}
