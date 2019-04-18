#pragma once

#include "main.h"

namespace robot {

    namespace drive {
        extern MotorGroup left;
        extern MotorGroup right;
        extern ChassisControllerIntegrated controller;
    }

    namespace lift {
        extern Motor motor;
        extern AsyncPosIntegratedController controller;
        extern ADIButton leftLimitSwitch;
        extern ADIButton rightLimitSwitch;
    }

    namespace capIntake {
        extern Motor motor;
        extern AsyncPosIntegratedController controller;
        extern Potentiometer potentiometer;
    }

    namespace guide {
        extern ADIButton limitSwitch;
    }

    namespace shooter {
        extern Motor motor;
    }

    namespace ballIntake {
        extern Motor motor;
    }

    void setup();

}
