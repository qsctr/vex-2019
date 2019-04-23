#include "main.h"
#include "robot/ballIntake.hpp"

namespace robot::ballIntake {

    VoltageController controller {std::make_shared<Motor>(4),
        AbstractMotor::gearset::green, AbstractMotor::brakeMode::brake};

}
