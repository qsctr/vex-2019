#include "main.h"
#include "constants.hpp"
#include "robot.hpp"
#include "teleop/controls.hpp"
#include "teleop/multiController.hpp"

#include <cstdio>

namespace teleop {

    constexpr float ANALOG_DEADBAND {0.05};

    namespace controllers {
        Controller cap {controllerIds::cap};
        Controller ball {controllerIds::ball};
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
    ControllerButton adjustPositive, ControllerButton adjustNegative) {
        if (abs(analog) > ANALOG_DEADBAND)
            return analog;
        if (adjustPositive.isPressed())
            return 0.2;
        if (adjustNegative.isPressed())
            return -0.2;
        return std::nullopt;
    }

    std::pair<double, double> getDrivePower() {
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
            if (forwardPower || yawPower)
                return {-forwardPower.value_or(0), yawPower.value_or(0)};
        }
        return {capLeft, capRight};
    }

}

void opcontrol() {
    using namespace teleop;
    robot::lift::reset();
    int i = 0;
    while (true) {
        auto [leftDrivePower, rightDrivePower] = getDrivePower();
        robot::drive::controller.tank(leftDrivePower, rightDrivePower);
        if (controls::groundPickup.changedToPressed()) {
            multiControllers::lift.movePreset(-50);
            multiControllers::capIntake.movePreset(-30);
        } else if (controls::lowPoleDelivery.changedToPressed()) {
            multiControllers::lift.movePreset(650);
            multiControllers::capIntake.movePreset(-10);
        } else if (controls::highPoleDelivery.changedToPressed()) {
            multiControllers::lift.movePreset(750);
            multiControllers::capIntake.movePreset(70);
        } else if (controls::lowPolePickup.changedToPressed()) {
            multiControllers::lift.movePreset(350);
            multiControllers::capIntake.movePreset(0);
        } else if (controls::highPolePickup.changedToPressed()) {
            multiControllers::lift.movePreset(500);
            multiControllers::capIntake.movePreset(0);
        } else if (controls::flipCap.changedToPressed()) {
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
        } else if (controls::capIntakeUp.changedToPressed()) {
            multiControllers::capIntake.movePreset(300);
        } else if (controls::capIntakeFlat.changedToPressed()) {
            multiControllers::capIntake.movePreset(0);
        } else {
            if (controls::manualLiftUp.isPressed()) {
                multiControllers::lift.moveManualOverride(1);
            } else if (controls::manualLiftDown.isPressed()) {
                multiControllers::lift.moveManualOverride(-1);
            } else {
                multiControllers::lift.moveManualDefault(0);
            }
            if (controls::manualCapIntakeIn.isPressed()) {
                multiControllers::capIntake.moveManualOverride(1);
            } else if (controls::manualCapIntakeOut.isPressed()) {
                multiControllers::capIntake.moveManualOverride(-1);
            } else {
                multiControllers::capIntake.moveManualDefault(0);
            }
        }
        if (controls::shoot.isPressed()) {
            robot::shooter::motor.moveVoltage(MAX_VOLTAGE);
        } else {
            robot::shooter::motor.moveVoltage(0);
        }
        if (controls::ballIntakeIn.isPressed()) {
            robot::ballIntake::motor.moveVoltage(MAX_VOLTAGE);
        } else if (controls::ballIntakeOut.isPressed()) {
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
            controllers::cap.setText(0, 0, std::to_string(robot::capIntake::motor.getPosition()));
            i = 0;
        }
        pros::Task::delay(10);
        i++;
    }
}
