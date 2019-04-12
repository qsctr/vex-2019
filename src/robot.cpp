#include "main.h"
#include "robot.h"

using gearset = AbstractMotor::gearset;
using brakeMode = AbstractMotor::brakeMode;

namespace robot {

    MotorGroup baseLeft {5, 11};
    MotorGroup baseRight {-6, -20};
    ChassisControllerIntegrated drive = ChassisControllerFactory::create(
        baseLeft, baseRight, gearset::green, {4_in, 13.75_in});
    MotorGroup lift {-4, 7};
    Motor intake {-3};

    void setup() {
        baseLeft.setBrakeMode(brakeMode::brake);
        baseRight.setBrakeMode(brakeMode::brake);
        lift.setGearing(gearset::green);
        lift.setBrakeMode(brakeMode::brake);
        intake.setGearing(gearset::red);
        intake.setBrakeMode(brakeMode::brake);
    }

}
