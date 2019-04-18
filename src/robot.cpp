#include "main.h"
#include "constants.hpp"
#include "robot.hpp"

namespace robot {

    namespace drive {
        MotorGroup baseLeft {3, 20};
        MotorGroup baseRight {-2, -12};
        ChassisControllerIntegrated controller =
            ChassisControllerFactory::create(baseLeft, baseRight,
                AbstractMotor::gearset::green, {4.25_in, 14_in});
    }

    namespace lift {
        Motor motor {11};
        AsyncPosIntegratedController controller =
            AsyncControllerFactory::posIntegrated(motor, RED_RPM);
        ADIButton leftLimitSwitch {'G'};
        ADIButton rightLimitSwitch {'H'};
    }

    namespace capIntake {
        Motor motor {-17};
        AsyncPosIntegratedController controller =
            AsyncControllerFactory::posIntegrated(motor, RED_RPM);
        Potentiometer potentiometer {'F'};
        const double FLAT_POTENTIOMETER_VALUE = 2600;
        const double VERTICAL_POTENTIOMETER_VALUE = 1070;
        const double FLAT_ENCODER_DEGREES = 0;
        const double VERTICAL_ENCODER_DEGREES = 265;
        static void reset() {
            motor.set_zero_position(remapRange(potentiometer.get(),
                FLAT_POTENTIOMETER_VALUE, VERTICAL_POTENTIOMETER_VALUE,
                FLAT_ENCODER_DEGREES, VERTICAL_ENCODER_DEGREES));
        }
    }

    namespace guide {
        ADIButton limitSwitch {'E'};
    }

    namespace shooter {
        Motor motor {-1};
    }

    namespace ballIntake {
        Motor motor {4};
    }

    void setup() {
        drive::left.setBrakeMode(AbstractMotor::brakeMode::brake);
        drive::right.setBrakeMode(AbstractMotor::brakeMode::brake);
        lift::motor.setGearing(AbstractMotor::gearset::red);
        lift::motor.setBrakeMode(AbstractMotor::brakeMode::brake);
        capIntake::motor.setGearing(AbstractMotor::gearset::red);
        capIntake::motor.setBrakeMode(AbstractMotor::brakeMode::brake);
        ballIntake::motor.setGearing(AbstractMotor::gearset::green);
        ballIntake::motor.setBrakeMode(AbstractMotor::brakeMode::brake);
        shooter::motor.setGearing(AbstractMotor::gearset::red);
        shooter::motor.setBrakeMode(AbstractMotor::brakeMode::brake);
        pros::delay(500);
        capIntake::reset();
    }

}
