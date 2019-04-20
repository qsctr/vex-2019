#include "main.h"
#include "robot/capIntake.hpp"

constexpr auto gearing = AbstractMotor::gearset::red;

constexpr double FLAT_POTENTIOMETER_VALUE = 2500;
constexpr double VERTICAL_POTENTIOMETER_VALUE = 970;
constexpr double FLAT_ENCODER_DEGREES = 0;
constexpr double VERTICAL_ENCODER_DEGREES = 265;

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
            FLAT_POTENTIOMETER_VALUE, VERTICAL_POTENTIOMETER_VALUE,
            FLAT_ENCODER_DEGREES, VERTICAL_ENCODER_DEGREES));
    }

}
