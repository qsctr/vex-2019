#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void autonomous() {
    // ADIButton liftLimitSwitch {'A'};
    Potentiometer pot {'B'};
    ADIButton guideLimitSwitch {'C'};
    auto liftController = AsyncControllerFactory::posIntegrated(robot::lift, GREEN_RPM);
    auto intakeController = AsyncControllerFactory::posIntegrated(robot::intake, RED_RPM);
    auto profileController = AsyncControllerFactory::motionProfile(0.3, 0.6, 3, robot::drive);
    profileController.generatePath({
        Point {0_cm, 0_cm, 0_deg},
        Point {37_cm, -18_cm, -60_deg}
    }, "toPole");
    robot::lift.moveVoltage(-MAX_VOLTAGE);
    robot::drive.moveDistance(-105_cm);
    // while (!liftLimitSwitch.isPressed()) {
    //     pros::Task::delay(10);
    // }
    robot::lift.tarePosition();
    robot::intake.set_zero_position(remapRange(pot.get(), 3350, 1760, 0, 266));
    liftController.setTarget(-50);
    robot::drive.turnAngle(85_deg);
    intakeController.setTarget(-30);
    robot::drive.moveDistance(-30_cm);
    intakeController.waitUntilSettled();
    robot::drive.moveDistance(50_cm);
    intakeController.setTarget(10);
    robot::drive.turnAngle(-80_deg);
    liftController.setTarget(650);
    liftController.waitUntilSettled();
    intakeController.setTarget(300);
    intakeController.waitUntilSettled();
    intakeController.setTarget(-30);
    // intakeController.setMaxVelocity(RED_RPM);
    profileController.setTarget("toPole");
    profileController.waitUntilSettled();
    robot::baseLeft.moveVoltage(MAX_VOLTAGE / 3);
    robot::baseRight.moveVoltage(MAX_VOLTAGE / 3);
    while (!guideLimitSwitch.isPressed()) {
        pros::Task::delay(10);
    }
    robot::baseLeft.moveVoltage(0);
    robot::baseRight.moveVoltage(0);
    // intakeController.waitUntilSettled();
    // intakeController.setTarget(-30);
    intakeController.waitUntilSettled();
    // liftController.waitUntilSettled();
    liftController.setTarget(400);
    liftController.waitUntilSettled();
    printf("%u\n", pros::millis());
}
