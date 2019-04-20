#include "main.h"
#include "robot/lift.hpp"

constexpr auto gearing = AbstractMotor::gearset::red;

namespace robot::lift {

    Motor motor {11};
    AsyncPosIntegratedController controller =
        AsyncControllerFactory::posIntegrated(motor, toUnderlyingType(gearing));
    ADIButton leftLimitSwitch {'G'};
    ADIButton rightLimitSwitch {'H'};

    void initialize() {
        motor.setGearing(gearing);
        motor.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

}
