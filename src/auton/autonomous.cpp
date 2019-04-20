#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void autonomous() {
    uint32_t startingTime = pros::millis();
    robot::lift::reset();
    robot::lift::controller.setTarget(100);
    robot::lift::controller.waitUntilSettled();
    robot::ballIntake::motor.moveVoltage(-MAX_VOLTAGE);
    robot::shooter::motor.moveVoltage(MAX_VOLTAGE);
    pros::delay(700);
    robot::ballIntake::motor.moveVoltage(MAX_VOLTAGE);
    robot::shooter::motor.moveVoltage(0);
    robot::drive::controller.turnAngle(-90_deg);
    robot::drive::controller.moveDistance(-100_cm);
    robot::lift::controller.setTarget(0);
    robot::capIntake::controller.setTarget(-30);
    // pros::Task::delay(100);
    robot::drive::controller.moveDistance(50_cm);
    robot::drive::controller.turnAngle(130_deg);
    robot::capIntake::controller.waitUntilSettled();
    robot::drive::controller.moveDistance(60_cm);
    robot::capIntake::controller.setTarget(300);
    while (robot::capIntake::motor.getPosition() < 50) {
        pros::Task::delay(10);
    }
    robot::lift::controller.setTarget(650);
    robot::drive::controller.moveDistance(-32_cm);
    robot::capIntake::controller.setTarget(-20);
    robot::drive::controller.turnAngle(-61_deg);
    // robot::lift::controller.waitUntilSettled();
    robot::capIntake::controller.waitUntilSettled();
    robot::drive::controller.forward(1);
    while (!robot::guide::limitSwitch.isPressed()) {
        pros::Task::delay(10);
    }
    robot::drive::controller.stop();
    robot::shooter::motor.moveVoltage(MAX_VOLTAGE);
    // robot::capIntake::controller.waitUntilSettled();
    // robot::capIntake::controller.setTarget(-20);
    // robot::capIntake::controller.waitUntilSettled();
    // robot::capIntake::controller.setMaxVelocity(RED_RPM / 2);
    // robot::lift::controller.setMaxVelocity(RED_RPM / 2);
    robot::lift::controller.setTarget(400);
    robot::lift::controller.waitUntilSettled();
    robot::shooter::motor.moveVoltage(0);
    robot::ballIntake::motor.moveVoltage(0);
    uint32_t totalTime = pros::millis() - startingTime;
    while (true) {
        printf("%u\n", totalTime);
        pros::delay(10);
    }

    // robot::drive::controller.turnAngle(-134_deg);
    // robot::lift::controller.setTarget(650);
    // robot::lift::controller.waitUntilSettled();
    // robot::capIntake::controller.setMaxVelocity(RED_RPM);
    // robot::capIntake::controller.setTarget(-10);
    // profileController.setTarget("toPole");
    // profileController.waitUntilSettled();

    // ADIButton leftLiftLimitSwitch {'G'};
    // ADIButton rightLiftLimitSwitch {'H'};
    // Potentiometer capIntakePotentiometer {'F'};
    // ADIButton guideLimitSwitch {'E'};
    // auto liftController = AsyncControllerFactory::posIntegrated(robot::lift, RED_RPM);
    // auto capIntakeController = AsyncControllerFactory::posIntegrated(robot::capIntake, RED_RPM);
    // auto baseLeftController = AsyncControllerFactory::posIntegrated(robot::baseLeft, GREEN_RPM);
    // auto profileController = AsyncControllerFactory::motionProfile(0.3, 0.6, 3, robot::drive);
    // profileController.generatePath({
    //     Point {0_cm, 0_cm, 0_deg},
    //     Point {26_cm, -10_cm, -60_deg}
    // }, "toPole");
    // pros::delay(500);
    // robot::capIntake.set_zero_position(remapRange(capIntakePotentiometer.get(), 2600, 1070, 0, 265));
    // robot::lift.moveVoltage(-MAX_VOLTAGE);
    // robot::ballIntake.moveVoltage(MAX_VOLTAGE);
    // robot::drive.moveDistance(-100_cm);
    // robot::lift.tarePosition();
    // liftController.setTarget(-50);
    // capIntakeController.setTarget(-30);
    // pros::delay(100);
    // robot::drive.moveDistance(50_cm);
    // robot::ballIntake.moveVoltage(0);
    // robot::drive.turnAngle(132_deg);
    // capIntakeController.waitUntilSettled();
    // robot::drive.moveDistance(60_cm);
    // capIntakeController.setTarget(300);
    // capIntakeController.waitUntilSettled();
    // robot::drive.turnAngle(-134_deg);
    // liftController.setTarget(650);
    // liftController.waitUntilSettled();
    // capIntakeController.setTarget(-30);
    // profileController.setTarget("toPole");
    // profileController.waitUntilSettled();



    // robot::baseLeft.moveRelative(390, GREEN_RPM);
    // pros::delay(2000);
    // robot::baseLeft.moveVoltage(MAX_VOLTAGE / 2);
    // robot::baseRight.moveVoltage(MAX_VOLTAGE / 2);
    // while (!guideLimitSwitch.isPressed()) {
    //     pros::delay(10);
    // }
    // robot::baseLeft.moveVoltage(0);
    // robot::baseRight.moveVoltage(0);
    // liftController.setTarget(400);
    // liftController.waitUntilSettled();

    // baseLeftController.setTarget(100);
    // baseLeftController.waitUntilSettled();

    // robot::drive.moveDistance(-5_cm);
    // // ADIButton liftLimitSwitch {'A'};
    // Potentiometer pot {'B'};
    // ADIButton guideLimitSwitch {'C'};
    // auto liftController = AsyncControllerFactory::posIntegrated(robot::lift, GREEN_RPM);
    // auto intakeController = AsyncControllerFactory::posIntegrated(robot::intake, RED_RPM);
    // auto profileController = AsyncControllerFactory::motionProfile(0.3, 0.6, 3, robot::drive);
    // profileController.generatePath({
    //     Point {0_cm, 0_cm, 0_deg},
    //     Point {37_cm, -18_cm, -60_deg}
    // }, "toPole");
    // robot::lift.moveVoltage(-MAX_VOLTAGE);
    // robot::drive.moveDistance(-105_cm);
    // // while (!liftLimitSwitch.isPressed()) {
    // //     pros::Task::delay(10);
    // // }
    // robot::lift.tarePosition();
    // robot::intake.set_zero_position(remapRange(pot.get(), 3350, 1760, 0, 266));
    // liftController.setTarget(-50);
    // robot::drive.turnAngle(85_deg);
    // intakeController.setTarget(-30);
    // robot::drive.moveDistance(-30_cm);
    // intakeController.waitUntilSettled();
    // robot::drive.moveDistance(50_cm);
    // intakeController.setTarget(10);
    // robot::drive.turnAngle(-80_deg);
    // liftController.setTarget(650);
    // liftController.waitUntilSettled();
    // intakeController.setTarget(300);
    // intakeController.waitUntilSettled();
    // intakeController.setTarget(-30);
    // // intakeController.setMaxVelocity(RED_RPM);
    // profileController.setTarget("toPole");
    // profileController.waitUntilSettled();
    // robot::baseLeft.moveVoltage(MAX_VOLTAGE / 3);
    // robot::baseRight.moveVoltage(MAX_VOLTAGE / 3);
    // while (!guideLimitSwitch.isPressed()) {
    //     pros::Task::delay(10);
    // }
    // robot::baseLeft.moveVoltage(0);
    // robot::baseRight.moveVoltage(0);
    // // intakeController.waitUntilSettled();
    // // intakeController.setTarget(-30);
    // intakeController.waitUntilSettled();
    // // liftController.waitUntilSettled();
    // liftController.setTarget(400);
    // liftController.waitUntilSettled();
    // printf("%u\n", pros::millis());
}
