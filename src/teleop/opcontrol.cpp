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

    void capFlipSequence(double capIntakeDownPosition) {
        robot::capIntake::controller->movePosition(
        robot::capIntake::positions::flip, [=] {
            robot::capIntake::controller->movePosition(
                capIntakeDownPosition);
        });
    }

    void poleFlipSequence(double liftUpPosition, double capIntakeDownPosition,
    double liftDownPosition) {
        robot::lift::controller->movePosition(liftUpPosition, [=] {
            robot::capIntake::controller->movePosition(
            robot::capIntake::positions::flip, [=] {
                if (capIntakeDownPosition >
                robot::capIntake::positions::flat) {
                    robot::capIntake::controller->movePosition(
                    robot::capIntake::positions::flat, [=] {
                        robot::capIntake::controller->movePosition(
                        capIntakeDownPosition, [=] {
                            robot::lift::controller->movePosition(
                                liftDownPosition);
                        });
                    });
                } else {
                    robot::capIntake::controller->movePosition(
                    capIntakeDownPosition, [=] {
                        robot::lift::controller->movePosition(liftDownPosition);
                    });
                }
            });
        });
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
                controllers::ball.getAnalog(controls::ballDriveYaw);
            std::optional<double> forwardPower;
            if (abs(ballForward) > ANALOG_DEADBAND) {
                forwardPower = ballForward;
            } else if (controls::ballDriveAdjustForward.isPressed()) {
                forwardPower = 0.2;
            } else if (controls::ballDriveAdjustBackward.isPressed()) {
                forwardPower = -0.2;
            }
            std::optional<double> yawPower;
            if (abs(ballYaw) > ANALOG_DEADBAND) {
                yawPower = ballYaw;
            } else if (controls::ballDriveAdjustLeft.isPressed()) {
                yawPower = 0.3;
            } else if (controls::ballDriveAdjustRight.isPressed()) {
                yawPower = -0.3;
            }
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
    puts("hi");
    using namespace teleop;
    // robot::lift::reset();
    // robot::drive::left.setReversed(false);
    // robot::drive::right.setReversed(true);
    int i = 0;
    while (true) {
        drive();
        if (controls::groundPickup.changedToPressed()) {
            robot::lift::controller->movePosition(
            robot::lift::positions::initialGroundPickup,
            robot::lift::isDown, [&] {
                robot::lift::controller->movePosition(
                    robot::lift::positions::holdGroundPickup);
            });
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::groundPickup);
        } else if (controls::lowPoleDelivery.changedToPressed()) {
            robot::lift::controller->movePosition(
            robot::lift::positions::lowPoleDelivery, [] {
                robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flat, [] {
                    robot::capIntake::controller->movePosition(
                        robot::capIntake::positions::lowPoleDelivery);
                });
            });
        } else if (controls::highPoleDelivery.changedToPressed()) {
            if (robot::capIntake::controller->getPosition() >
            robot::capIntake::positions::highPoleDelivery) {
                robot::lift::controller->movePosition(
                robot::lift::positions::highPoleDelivery, [] {
                    robot::capIntake::controller->movePosition(
                    robot::capIntake::positions::flat, [] {
                        robot::capIntake::controller->movePosition(
                            robot::capIntake::positions::highPoleDelivery);
                    });
                });
            } else {
                robot::lift::controller->movePosition(
                robot::lift::positions::highPoleDelivery, [] {
                    robot::capIntake::controller->movePosition(
                        robot::capIntake::positions::highPoleDelivery);
                });
            }
        } else if (controls::lowPolePickup.changedToPressed()) {
            robot::lift::controller->movePosition(
                robot::lift::positions::lowPolePickup);
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flat);
        } else if (controls::highPolePickup.changedToPressed()) {
            robot::lift::controller->movePosition(
                robot::lift::positions::highPolePickup);
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flat);
        } else if (controls::flipCap.changedToPressed()) {
            auto liftTarget = robot::lift::controller->getTarget();
            if (liftTarget
            && liftTarget.value() == robot::lift::positions::lowPolePickup) {
                poleFlipSequence(robot::lift::positions::lowPoleDelivery,
                    robot::capIntake::positions::lowPoleDelivery,
                    robot::lift::positions::lowPoleDelivery2);
            } else if (liftTarget
            && liftTarget.value() == robot::lift::positions::highPolePickup) {
                poleFlipSequence(robot::lift::positions::highPoleDelivery,
                    robot::capIntake::positions::highPoleDelivery,
                    robot::lift::positions::highPoleDelivery2);
            } else {
                capFlipSequence(robot::capIntake::positions::flat);
            }
        } else if (controls::capIntakeUp.changedToPressed()) {
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flip);
        } else if (controls::capIntakeFlat.changedToPressed()) {
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flat);
        } else {
            if (controls::manualLiftUp.isPressed()) {
                robot::lift::controller->moveVoltage(1);
            } else if (controls::manualLiftDown.isPressed()) {
                robot::lift::controller->moveVoltage(-1);
            } else {
                robot::lift::controller->moveVoltageDefault(0);
            }
            if (controls::manualCapIntakeIn.isPressed()) {
                robot::capIntake::controller->moveVoltage(1);
            } else if (controls::manualCapIntakeOut.isPressed()) {
                robot::capIntake::controller->moveVoltage(-1);
            } else {
                robot::capIntake::controller->moveVoltageDefault(0);
            }
        }
        if (controls::shoot.isPressed()) {
            robot::shooter::controller->moveVoltage(1);
        } else {
            robot::shooter::controller->moveVoltage(0);
        }
        if (controls::ballIntakeIn.isPressed()) {
            robot::ballIntake::controller->moveVoltage(1);
        } else if (controls::ballIntakeOut.isPressed()) {
            robot::ballIntake::controller->moveVoltage(-1);
        } else {
            robot::ballIntake::controller->moveVoltage(0);
        }
        if (robot::lift::isDown()) {
            robot::lift::controller->getMotor()->tarePosition();
        }
        robot::lift::controller->checkCallback();
        robot::capIntake::controller->checkCallback();
        if (robot::guide::limitSwitch.changedToPressed()) {
            controllers::cap.rumble(".");
        }
        printf("%f %f\n", robot::capIntake::controller->getPosition(), robot::capIntake::potentiometer.get());
        if (i == 100) {
            controllers::cap.setText(0, 0, std::to_string(robot::lift::controller->getPosition()));
            i = 0;
        }
        pros::Task::delay(10);
        i++;
    }
}
