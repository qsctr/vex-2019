#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void initialize() {
    robot::lift::controller = std::make_shared<MultiController>(
        std::make_shared<Motor>(11), AbstractMotor::gearset::red, AbstractMotor::brakeMode::brake);
    robot::capIntake::controller = std::make_shared<MultiController>(
        std::make_shared<Motor>(-17), AbstractMotor::gearset::red,
        AbstractMotor::brakeMode::brake);
    robot::shooter::controller = std::make_shared<VoltageController>(
        std::make_shared<Motor>(-1), AbstractMotor::gearset::red,
        AbstractMotor::brakeMode::brake);
    robot::ballIntake::controller = std::make_shared<VoltageController>(
        std::make_shared<Motor>(4), AbstractMotor::gearset::green,
        AbstractMotor::brakeMode::brake);
    robot::drive::initialize();
    pros::Task::delay(SENSOR_INITIALIZATION_TIME);
    robot::capIntake::resetPosition();
}

void competition_initialize() {}

void disabled() {}
