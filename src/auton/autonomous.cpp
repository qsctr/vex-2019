#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void autonomous() {
    uint32_t startingTime = pros::millis();
    robot::lift::reset();
    robot::lift::controller.movePosition(100);
    robot::lift::controller.waitUntilSettled();
    robot::ballIntake::controller.moveVoltage(-1);
    robot::shooter::controller.moveVoltage(1);
    pros::delay(700);
    robot::ballIntake::controller.moveVoltage(1);
    robot::shooter::controller.moveVoltage(0);
    robot::drive::controller.turnAngle(-90_deg);
    robot::drive::controller.moveDistance(-100_cm);
    robot::lift::controller.movePosition(0);
    robot::capIntake::controller.movePosition(-30);
    // pros::Task::delay(100);
    robot::drive::controller.moveDistance(50_cm);
    robot::drive::controller.turnAngle(130_deg);
    robot::capIntake::controller.waitUntilSettled();
    robot::drive::controller.moveDistance(60_cm);
    robot::capIntake::controller.movePosition(300);
    while (robot::capIntake::controller.getPosition() < 50) {
        pros::Task::delay(10);
    }
    robot::lift::controller.movePosition(650);
    robot::drive::controller.moveDistance(-32_cm);
    robot::capIntake::controller.movePosition(-20);
    robot::drive::controller.turnAngle(-61_deg);
    // robot::lift::controller.waitUntilSettled();
    robot::capIntake::controller.waitUntilSettled();
    robot::drive::controller.forward(1);
    while (!robot::guide::limitSwitch.isPressed()) {
        pros::Task::delay(10);
    }
    robot::drive::controller.stop();
    robot::shooter::controller.moveVoltage(1);
    // robot::capIntake::controller.waitUntilSettled();
    // robot::capIntake::controller.movePosition(-20);
    // robot::capIntake::controller.waitUntilSettled();
    // robot::capIntake::controller.setMaxVelocity(RED_RPM / 2);
    // robot::lift::controller.setMaxVelocity(RED_RPM / 2);
    robot::lift::controller.movePosition(400);
    robot::lift::controller.waitUntilSettled();
    robot::shooter::controller.moveVoltage(0);
    robot::ballIntake::controller.moveVoltage(0);
    uint32_t totalTime = pros::millis() - startingTime;
    while (true) {
        printf("%u\n", totalTime);
        pros::delay(10);
    }

}
