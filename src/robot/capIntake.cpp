#include "main.h"
#include "robot/capIntake.hpp"

constexpr auto gearing = AbstractMotor::gearset::red;

constexpr double flatPotentiometerValue = 2500;
constexpr double verticalPotentiometerValue = 970;

namespace robot::capIntake {

    Motor motor {-17};
    AsyncPosIntegratedController controller =
        AsyncControllerFactory::posIntegrated(motor, toUnderlyingType(gearing));
    Potentiometer potentiometer {'F'};

    void initialize() {
        motor.setGearing(gearing);
        motor.setBrakeMode(AbstractMotor::brakeMode::brake);
    }

    void resetPosition() {
        motor.set_zero_position(remapRange(potentiometer.get(),
            flatPotentiometerValue, verticalPotentiometerValue,
            positions::flat, positions::vertical));
    }

}
