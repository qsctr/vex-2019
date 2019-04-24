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
            robot::lift::controller.movePosition(
            robot::lift::positions::initialGroundPickup,
            robot::lift::isDown, [&] {
                robot::lift::controller.movePosition(
                    robot::lift::positions::holdGroundPickup);
            });
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::groundPickup);
        } else if (controls::lowPoleDelivery.changedToPressed()) {
            robot::lift::controller.movePosition(
                robot::lift::positions::lowPoleDelivery);
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::lowPoleDelivery);
        } else if (controls::highPoleDelivery.changedToPressed()) {
            robot::lift::controller.movePosition(
                robot::lift::positions::highPoleDelivery);
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::highPoleDelivery);
        } else if (controls::lowPolePickup.changedToPressed()) {
            robot::lift::controller.movePosition(
                robot::lift::positions::lowPolePickup);
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::flat);
        } else if (controls::highPolePickup.changedToPressed()) {
            robot::lift::controller.movePosition(
                robot::lift::positions::highPolePickup);
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::flat);
        } else if (controls::flipCap.changedToPressed()) {
            auto liftTarget = robot::lift::controller.getTarget();
            if (liftTarget
            && liftTarget.value() == robot::lift::positions::lowPolePickup) {
                robot::lift::controller.movePosition(
                robot::lift::positions::lowPoleDelivery, [&] {
                    robot::capIntake::controller.movePosition(
                    robot::capIntake::positions::flip, [&] {
                        robot::capIntake::controller.movePosition(
                        robot::capIntake::positions::lowPoleDelivery, [&] {
                            robot::lift::controller.movePosition(
                                robot::lift::positions::lowPoleDelivery2);
                        });
                    });
                });
            } else if (liftTarget
            && liftTarget.value() == robot::lift::positions::highPolePickup) {
                robot::lift::controller.movePosition(
                robot::lift::positions::highPoleDelivery, [&] {
                    robot::capIntake::controller.movePosition(
                    robot::capIntake::positions::flip, [&] {
                        robot::capIntake::controller.movePosition(
                        robot::capIntake::positions::highPoleDelivery, [&] {
                            robot::lift::controller.movePosition(
                                robot::lift::positions::highPoleDelivery2);
                        });
                    });
                });
            } else {
                robot::capIntake::controller.movePosition(
                robot::capIntake::positions::flip, [&] {
                    robot::capIntake::controller.movePosition(
                        robot::capIntake::positions::flat);
                });
            }
        } else if (controls::capIntakeUp.changedToPressed()) {
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::flip);
        } else if (controls::capIntakeFlat.changedToPressed()) {
            robot::capIntake::controller.movePosition(
                robot::capIntake::positions::flat);
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
        robot::lift::controller.checkCallback();
        robot::capIntake::controller.checkCallback();
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
