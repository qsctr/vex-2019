#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

namespace {

    constexpr float analogDeadband = 0.05;

    namespace controllerIds {
        constexpr auto cap = ControllerId::master;
        constexpr auto ball = ControllerId::partner;
    }

    namespace controllers {
        Controller cap {controllerIds::cap};
        Controller ball {controllerIds::ball};
    }

    namespace controls {
        constexpr auto capDriveLeft = ControllerAnalog::leftY;
        constexpr auto capDriveRight = ControllerAnalog::rightY;
        constexpr auto ballDriveForward = ControllerAnalog::leftY;
        constexpr auto ballDriveYaw = ControllerAnalog::rightX;
        ControllerButton manualLiftUp
            {controllerIds::cap, ControllerDigital::R1};
        ControllerButton manualLiftDown
            {controllerIds::cap, ControllerDigital::R2};
        ControllerButton manualCapIntakeIn
            {controllerIds::cap, ControllerDigital::L1};
        ControllerButton manualCapIntakeOut
            {controllerIds::cap, ControllerDigital::L2};
        ControllerButton groundPickup
            {controllerIds::cap, ControllerDigital::B};
        ControllerButton lowPoleDelivery
            {controllerIds::cap, ControllerDigital::A};
        ControllerButton highPoleDelivery
            {controllerIds::cap, ControllerDigital::X};
        ControllerButton lowPolePickup
            {controllerIds::cap, ControllerDigital::left};
        ControllerButton highPolePickup
            {controllerIds::cap, ControllerDigital::up};
        ControllerButton flipCap
            {controllerIds::cap, ControllerDigital::right};
        ControllerButton capIntakeUp
            {controllerIds::cap, ControllerDigital::Y};
        ControllerButton capIntakeFlat
            {controllerIds::cap, ControllerDigital::down};
        ControllerButton ballDriveAdjustForward
            {controllerIds::ball, ControllerDigital::up};
        ControllerButton ballDriveAdjustBackward
            {controllerIds::ball, ControllerDigital::down};
        ControllerButton ballDriveAdjustLeft
            {controllerIds::ball, ControllerDigital::A};
        ControllerButton ballDriveAdjustRight
            {controllerIds::ball, ControllerDigital::Y};
        ControllerButton shoot
            {controllerIds::ball, ControllerDigital::R1};
        ControllerButton ballIntakeIn
            {controllerIds::ball, ControllerDigital::L1};
        ControllerButton ballIntakeOut
            {controllerIds::ball, ControllerDigital::L2};
    }

    std::optional<double> ballControl(ControllerAnalog analog,
    ControllerButton& positiveAdjust, ControllerButton& negativeAdjust,
    double adjustPower) {
        auto analogValue = controllers::ball.getAnalog(analog);
        if (abs(analogValue) > analogDeadband) {
            return analogValue;
        }
        if (positiveAdjust.isPressed()) {
            return adjustPower;
        }
        if (negativeAdjust.isPressed()) {
            return -adjustPower;
        }
        return std::nullopt;
    }

    void drive() {
        float capLeft = controllers::cap.getAnalog(controls::capDriveLeft);
        float capRight = controllers::cap.getAnalog(controls::capDriveRight);
        if (abs(capLeft) < analogDeadband && abs(capRight) < analogDeadband) {
            auto forwardPower = ballControl(
                controls::ballDriveForward,
                controls::ballDriveAdjustForward,
                controls::ballDriveAdjustBackward,
                0.2);
            auto yawPower = ballControl(
                controls::ballDriveYaw,
                controls::ballDriveAdjustLeft,
                controls::ballDriveAdjustRight,
                0.3);
            if (forwardPower || yawPower) {
                robot::drive::controller->arcade(
                    -forwardPower.value_or(0), yawPower.value_or(0));
                return;
            }
        }
        robot::drive::controller->tank(capLeft, capRight);
    }

    void poleFlip(double liftUpPosition, double capIntakeDownPosition,
    double liftDownPosition) {
        robot::lift::controller->movePosition(liftUpPosition, [=] {
            robot::capIntake::controller->movePosition(
            robot::capIntake::positions::flip, [=] {
                auto placeAndLiftDown = [=] {
                    robot::capIntake::controller->movePosition(
                    capIntakeDownPosition, [=] {
                        robot::lift::controller->movePosition(liftDownPosition);
                    });
                };
                if (capIntakeDownPosition >
                robot::capIntake::positions::flat) {
                    robot::capIntake::controller->movePosition(
                        robot::capIntake::positions::flat, placeAndLiftDown);
                } else {
                    placeAndLiftDown();
                }
            });
        });
    }

}

void opcontrol() {
    while (true) {
        drive();
        if (controls::groundPickup.changedToPressed()) {
            robot::lift::controller->movePosition(
            robot::lift::positions::initialGroundPickup,
            robot::lift::isDown, [] {
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
            bool capIntakeAboveDelivery =
                robot::capIntake::controller->getPosition() >
                robot::capIntake::positions::highPoleDelivery;
            robot::lift::controller->movePosition(
            robot::lift::positions::highPoleDelivery, [=] {
                if (capIntakeAboveDelivery) {
                    robot::capIntake::controller->movePosition(
                    robot::capIntake::positions::flat, [] {
                        robot::capIntake::controller->movePosition(
                            robot::capIntake::positions::highPoleDelivery);
                    });
                } else {
                    robot::capIntake::controller->movePosition(
                        robot::capIntake::positions::highPoleDelivery);
                }
            });
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
                poleFlip(robot::lift::positions::lowPoleDelivery,
                    robot::capIntake::positions::lowPoleDelivery,
                    robot::lift::positions::lowPoleDelivery2);
            } else if (liftTarget
            && liftTarget.value() == robot::lift::positions::highPolePickup) {
                poleFlip(robot::lift::positions::highPoleDelivery,
                    robot::capIntake::positions::highPoleDelivery,
                    robot::lift::positions::highPoleDelivery2);
            } else {
                robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flip, [] {
                    robot::capIntake::controller->movePosition(
                        robot::capIntake::positions::flat);
                });
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
        pros::Task::delay(loopCycleTime);
    }
}
