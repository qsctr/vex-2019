#include "main.h"
#include "robot/ballIntake.hpp"

namespace robot::ballIntake {

    Motor motor {4};

    void initialize() {
        motor.setGearing(AbstractMotor::gearset::green);
        motor.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
