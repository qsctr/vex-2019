#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

void initialize() {
    robot::drive::initialize();
    pros::Task::delay(SENSOR_INITIALIZATION_TIME);
    robot::capIntake::resetPosition();
}

void competition_initialize() {}

void disabled() {}
