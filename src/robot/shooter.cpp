#include "main.h"
#include "robot/shooter.hpp"

namespace robot::shooter {

    Motor motor {-1};

    void initialize() {
        motor.setGearing(AbstractMotor::gearset::red);
        motor.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
