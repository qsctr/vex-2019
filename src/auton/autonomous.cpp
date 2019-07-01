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
    constexpr int side = color == Color::Blue ? 1 : -1;
}

void autonomous() {
    uint32_t startingTime = pros::millis();
    robot::drive::controller->setTurnsMirrored(color == Color::Red);
    robot::lift::reset();
    robot::lift::controller->movePosition(100);
    robot::lift::controller->waitUntilSettled();
    if constexpr (tile == Tile::Back) {
        AsyncMotionProfileController profileController = AsyncControllerFactory::motionProfile(0.6, 3, 6, *robot::drive::controller);
        ChassisControllerIntegrated chassisController2 = ChassisControllerFactory::create(robot::drive::right, robot::drive::left, AbstractMotor::gearset::green);
        AsyncMotionProfileController profileController2 = AsyncControllerFactory::motionProfile(0.5, 1, 5, chassisController2);
        profileController.generatePath({
            Point {0_in, 0_in, 0_deg},
            Point {29_in, side * 5_in, side * 45_deg},
            Point {40_in, side * 16_in, side * 45_deg}
        }, "to-waffle");
        // // robot::ballIntake::controller->moveVoltage(-1);
        // // robot::shooter::controller->moveVoltage(1);
        // // pros::delay(700);
        // // robot::ballIntake::controller->moveVoltage(0);
        // // robot::shooter::controller->moveVoltage(0);
        // auto profileController = AsyncControllerFactory::motionProfile(0.5, 1, 5, robot::drive::controller);
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {19_in, -22_in, -100_deg},
        //     // Point {20.75_in, -30_in, -90_deg}
        //     // Point {24_in, 20.75_in, 20_deg},
        //     // Point {30_in, 20.75_in, 0_deg}
        // }, "to-waffle");
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {-21_in, -20_in, 90_deg}
        // }, "back");
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {20_in, 11.75_in, 0_deg},
        //     Point {24_in, 11.75_in, 0_deg}
        // }, "to-pole");
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {-18.633_in, side * -11.75_in, 0_deg},
        //     Point {-42.133_in, side * -11.75_in, 0_deg}
        // }, "to-climb");
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {29_in, side * 5_in, side * 45_deg},
        //     Point {40_in, side * 16_in, side * 45_deg}
        // }, "to-waffle");
        // // profileController.generatePath({
        // //     Point {38_in, side * 14_in, side * 45_deg},
        // //     Point {9_in, 0_in, side * 30_deg}
        // // }, "back");
        // profileController.generatePath({
        //     Point {0_in, 0_in, 0_deg},
        //     Point {20_in, side * -11.75_in, 0_deg},
        //     Point {42.133_in, side * -11.75_in, 0_deg}
        // }, "to-climb");
        // // profileController.generatePath({
        // //     Point {20.75_in, side * }
        // // })
        profileController.setTarget("to-waffle");
        robot::capIntake::controller->movePosition(robot::capIntake::positions::groundPickup);
        robot::ballIntake::controller->moveVoltage(-1);
        robot::lift::controller->movePosition(-10);
        pros::delay(200);
        robot::ballIntake::controller->moveVoltage(1);
        profileController2.generatePath({
            Point {0_in, 0_in, 0_deg},
            Point {20_in, side * 11.75_in, 0_deg},
            Point {42.133_in, side * 11.75_in, 0_deg}
        }, "to-climb");
        robot::capIntake::controller->waitUntilSettled();
        profileController.waitUntilSettled();
        robot::capIntake::controller->movePosition(robot::capIntake::positions::flat);
        robot::lift::controller->movePosition(300);
        // while (robot::capIntake::controller->getPosition() < robot::capIntake::positions::flat) { pros::delay(10);}
        robot::capIntake::controller->waitUntilSettled();
        // robot::capIntake::controller->movePosition(robot::capIntake::positions::groundPickup);
        // robot::capIntake::controller->waitUntilSettled();
        // robot::capIntake::controller->movePosition(robot::capIntake::positions::flip);
        // robot::capIntake::controller->waitUntilSettled();
        // profileController.setTarget("back");
        // profileController.waitUntilSettled();
        // robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery);
        // robot::lift::controller->waitUntilSettled();
        // robot::capIntake::controller->movePosition(robot::capIntake::positions::flat);
        // robot::capIntake::controller->waitUntilSettled();
        // profileController.setTarget("to-pole");
        // profileController.waitUntilSettled();
        // robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery2, 0.5);
        // robot::lift::controller->waitUntilSettled();
        // robot::lift::controller->movePosition(robot::lift::positions::holdGroundPickup, 0.5);
        // profileController.setTarget("to-climb");
        // profileController.waitUntilSettled();
        robot::lift::controller->waitUntilSettled();
        robot::drive::controller->setMaxVelocity(100);
        // robot::drive::controller->moveDistance(-25_in);
        // robot::drive::controller->turnAngle(-50_deg);
        robot::drive::controller->moveDistance(-24_in);
        robot::drive::controller->turnAngle(-46_deg);
        // // profileController.setTarget("back");
        // // profileController.waitUntilSettled();
        // robot::capIntake::controller->movePosition(robot::capIntake::positions::flat);
        // robot::capIntake::controller->waitUntilSettled();
        robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery);
        robot::drive::controller->moveDistanceAsync(10_in);
        robot::lift::controller->waitUntilSettled();
        robot::drive::controller->waitUntilSettled();
        // robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery);
        // robot::lift::controller->waitUntilSettled();
        robot::drive::controller->moveDistance(12.5_in);
        robot::capIntake::controller->movePosition(robot::capIntake::positions::flip);
        robot::capIntake::controller->waitUntilSettled();
        // robot::capIntake::controller->movePosition(0);
        // robot::capIntake::controller->waitUntilSettled();
        robot::capIntake::controller->movePosition(robot::capIntake::positions::lowPoleDelivery);
        robot::capIntake::controller->waitUntilSettled();
        robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery2);
        while (robot::lift::controller->getPosition() > 500) {
            pros::delay(10);
        }
        // robot::lift::controller->waitUntilSettled();
        robot::drive::controller->moveDistance(-9_in);
        robot::drive::controller->turnAngle(-12_deg);
        robot::shooter::controller->moveVoltage(1);
        pros::delay(700);
        robot::shooter::controller->moveVoltage(0);
        // robot::drive::left.setReversed(true);
        // robot::drive::right.setReversed(false);
        // profileController.reset();
        // profileController.setTarget("to-climb");
        // pros::delay(1000);
        // robot::lift::controller->movePosition(robot::lift::positions::holdGroundPickup);
        // profileController.waitUntilSettled();
        // profileController2.setTarget("to-climb");
        // pros::delay(1000);
        // robot::lift::controller->movePosition(robot::lift::positions::holdGroundPickup, 0.5);
        // profileController2.waitUntilSettled();
        // if constexpr (color == Color::Blue) {
            // // robot::ballIntake::controller->moveVoltage(-1);
            // // robot::shooter::controller->moveVoltage(1);
            // // pros::delay(700);
            // // robot::ballIntake::controller->moveVoltage(0);
            // // robot::shooter::controller->moveVoltage(0);
            // // robot::ballIntake::controller->moveVoltage(1);
            // // robot::drive::controller->turnAngle(-92_deg);
            // // robot::drive::controller->moveDistance(-90_cm);
            // robot::drive::controller->moveDistanceAsync(-90_cm);
            // robot::ballIntake::controller->moveVoltage(-1);
            // pros::delay(200);
            // robot::ballIntake::controller->moveVoltage(1);
            // robot::drive::controller->waitUntilSettled();
            // robot::lift::controller->movePosition(0);
            // robot::capIntake::controller->movePosition(robot::capIntake::positions::groundPickup);
            // // pros::Task::delay(500);
            // robot::drive::controller->moveDistance(40_cm);
            // robot::drive::controller->turnAngle(color == Color::Blue ? 133_deg : 138_deg);
            // robot::capIntake::controller->waitUntilSettled();
            // robot::drive::controller->moveDistance(color == Color::Blue ? 60_cm : 57_cm);
            // robot::capIntake::controller->movePosition(robot::capIntake::positions::flip);
            // while (robot::capIntake::controller->getPosition() < 50) {
            //     pros::Task::delay(10);
            // }
            // robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery);
            // robot::drive::controller->moveDistance(color == Color::Blue ? -32_cm : -29_cm);
            // robot::drive::controller->turnAngle(-64_deg);
            // pros::delay(200);
            // robot::capIntake::controller->movePosition(robot::capIntake::positions::flat);
            // // robot::lift::controller->waitUntilSettled();
            // robot::capIntake::controller->waitUntilSettled();
            // // robot::drive::controller->forward(1);
            // // while (!robot::guide::limitSwitch.isPressed()) {
            // //     pros::Task::delay(10);
            // // }
            // // robot::drive::controller->stop();
            // robot::drive::controller->moveDistance(40_cm);
            // robot::capIntake::controller->movePosition(robot::capIntake::positions::lowPoleDelivery);
            // robot::capIntake::controller->waitUntilSettled();
            // robot::shooter::controller->moveVoltage(1);
            // // robot::lift::controller->movePosition(robot::lift::positions::lowPoleDelivery2, 0.5);
            // robot::lift::controller->movePosition(100, 0.5);
            // // robot::lift::controller->waitUntilSettled();
            // while (robot::lift::controller->getPosition() > 500) {
            //     pros::delay(10);
            // }
            // robot::shooter::controller->moveVoltage(0);
            // robot::ballIntake::controller->moveVoltage(0);
            // // robot::drive::controller->moveDistance(-30_cm);
            // robot::drive::controller->forward(-1);
            // while (pros::millis() < startingTime + 15000) {
            //     pros::delay(10);
            // }
            // robot::drive::controller->stop();
        // } else if constexpr (color == Color::Red) {
            // // robot::shooter::controller->moveVoltage(1);
            // robot::ballIntake::controller->moveVoltage(-1);
            // pros::delay(500);
            // robot::ballIntake::controller->moveVoltage(0);
            // // robot::drive::controller->moveDistance(15_in);
            // // pros::delay(1000);
            // // robot::shooter::controller->moveVoltage(0);
            // // robot::drive::controller->moveDistance(5_in);
            // // robot::shooter::controller->moveVoltage(1);
            // // pros::delay(700);
            // // robot::shooter::controller->moveVoltage(0);
            // // pros::delay(5000);
            // robot::drive::controller->moveDistance(-25.5_in);
            // // robot::drive::controller->turnAngle(-38_deg);
            // // robot::drive::controller->turnAngle(-55_deg);
            // // robot::shooter::controller->moveVoltage(1);
            // // pros::delay(700);
            // // robot::shooter::controller->moveVoltage(0);
            // // // robot::drive::controller->turnAngle(-52_deg);
            // // robot::drive::controller->turnAngle(-35_deg);
            // robot::drive::controller->turnAngle(-90_deg);
            // robot::drive::controller->moveDistance(-46_in);
            // // robot::drive::controller->turnAngle(-90_deg);
            // // robot::drive::controller->moveDistance(-45_in);
            // // robot::drive::controller->turnAngle(50_deg);
            // // robot::shooter::controller->moveVoltage(1);
            // // pros::delay(700);
            // // robot::shooter::controller->moveVoltage(0);
        // }
    } else if constexpr (tile == Tile::Front) {
        robot::drive::controller->moveDistance(-40_in);
        robot::drive::controller->moveDistance(20_in);
    }

}
