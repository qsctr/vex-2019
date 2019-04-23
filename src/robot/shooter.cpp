#include "main.h"
#include "robot/shooter.hpp"

namespace robot::shooter {

    VoltageController controller {std::make_shared<Motor>(-1),
        AbstractMotor::gearset::red, AbstractMotor::brakeMode::brake};

}
