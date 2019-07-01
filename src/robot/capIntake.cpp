#include "main.h"
#include "robot/capIntake.hpp"

namespace robot::capIntake {

    std::shared_ptr<MultiController> controller;
    Potentiometer potentiometer {'F'};

    void initialize() {
        controller = std::make_shared<MultiController>(
            std::make_shared<Motor>(-17),
            AbstractMotor::gearset::red,
            AbstractMotor::brakeMode::brake);
    }

    void resetPosition() {
        std::dynamic_pointer_cast<Motor>(controller->getMotor())
            ->set_zero_position(remapRange(potentiometer.get(),
                potentiometerValues::flat, potentiometerValues::vertical,
                positions::flat, positions::vertical));
    }

}
