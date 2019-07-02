#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void initialize() {
    robot::initialize();
    pros::Task::delay(sensorInitTime);
    robot::capIntake::resetPosition();
}

void competition_initialize() {}

void disabled() {}
