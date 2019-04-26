#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

namespace {
    enum class Color {
        Red, Blue
    };
    constexpr Color color = Color::Red;
    enum class Tile {
        Front, Back
    };
    constexpr Tile tile = Tile::Back;
}

void autonomous() {
    robot::drive::controller.setTurnsMirrored(color == Color::Red);
    robot::lift::reset();
    robot::lift::controller->movePosition(100);
    robot::lift::controller->waitUntilSettled();
    if constexpr (tile == Tile::Back) {
        // if constexpr (color == Color::Blue) {
        //     robot::ballIntake::controller->moveVoltage(-1);
        //     robot::shooter::controller->moveVoltage(1);
        //     pros::delay(700);
        //     robot::ballIntake::controller->moveVoltage(0);
        //     robot::shooter::controller->moveVoltage(0);
        //     robot::ballIntake::controller->moveVoltage(1);
        //     robot::drive::controller.turnAngle(-92_deg);
        //     robot::drive::controller.moveDistance(-90_cm);
        //     robot::lift::controller->movePosition(0);
        //     robot::capIntake::controller->movePosition(robot::capIntake::positions::groundPickup);
        //     // pros::Task::delay(200);
        //     robot::drive::controller.moveDistance(40_cm);
        //     robot::drive::controller.turnAngle(color == Color::Blue ? 131_deg : 138_deg);
        //     robot::capIntake::controller->waitUntilSettled();
        //     robot::drive::controller.moveDistance(color == Color::Blue ? 60_cm : 57_cm);
        //     robot::capIntake::controller->movePosition(robot::capIntake::positions::flip);
        //     while (robot::capIntake::controller->getPosition() < 50) {
        //         pros::Task::delay(10);
        //     }
        //     robot::lift::controller->movePosition(650);
        //     robot::drive::controller.moveDistance(color == Color::Blue ? -32_cm : -29_cm);
        //     robot::drive::controller.turnAngle(-62_deg);
        //     robot::capIntake::controller->movePosition(robot::capIntake::positions::flat);
        //     // robot::lift::controller->waitUntilSettled();
        //     robot::capIntake::controller->waitUntilSettled();
        //     // robot::drive::controller.forward(1);
        //     // while (!robot::guide::limitSwitch.isPressed()) {
        //     //     pros::Task::delay(10);
        //     // }
        //     // robot::drive::controller.stop();
        //     robot::drive::controller.moveDistance(33_cm);
        //     robot::capIntake::controller->movePosition(robot::capIntake::positions::lowPoleDelivery);
        //     robot::capIntake::controller->waitUntilSettled();
        //     robot::shooter::controller->moveVoltage(1);
        //     // robot::capIntake::controller->waitUntilSettled();
        //     // robot::capIntake::controller->movePosition(-20);
        //     // robot::capIntake::controller->waitUntilSettled();
        //     // robot::capIntake::controller->setMaxVelocity(RED_RPM / 2);
        //     // robot::lift::controller->setMaxVelocity(RED_RPM / 2);
        //     robot::lift::controller->movePosition(400, 0.5);
        //     robot::lift::controller->waitUntilSettled();
        //     robot::shooter::controller->moveVoltage(0);
        //     robot::ballIntake::controller->moveVoltage(0);
        //     robot::drive::controller.moveDistance(-30_cm);
        // } else if constexpr (color == Color::Red) {
            // robot::shooter::controller->moveVoltage(1);
            robot::ballIntake::controller->moveVoltage(-1);
            pros::delay(700);
            robot::ballIntake::controller->moveVoltage(0);
            // robot::shooter::controller->moveVoltage(0);
            robot::drive::controller.moveDistance(5_in);
            robot::shooter::controller->moveVoltage(1);
            pros::delay(700);
            robot::shooter::controller->moveVoltage(0);
            // pros::delay(5000);
            robot::drive::controller.moveDistance(-30.5_in);
            // robot::drive::controller.turnAngle(-38_deg);
            // // robot::drive::controller.turnAngle(-57_deg);
            // robot::shooter::controller->moveVoltage(1);
            // pros::delay(700);
            // robot::shooter::controller->moveVoltage(0);
            // robot::drive::controller.turnAngle(-52_deg);
            // robot::drive::controller.turnAngle(-33_deg);
            robot::drive::controller.turnAngle(-90_deg);
            robot::drive::controller.moveDistance(-46_in);
            // robot::drive::controller.turnAngle(-90_deg);
            // robot::drive::controller.moveDistance(-45_in);
            // robot::drive::controller.turnAngle(50_deg);
            // robot::shooter::controller->moveVoltage(1);
            // pros::delay(700);
            // robot::shooter::controller->moveVoltage(0);
        // }
    } else if constexpr (tile == Tile::Front) {
        robot::drive::controller.moveDistance(-40_in);
        robot::drive::controller.moveDistance(20_in);
    }

}
