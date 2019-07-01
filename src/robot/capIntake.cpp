#include "main.h"
#include "robot/capIntake.hpp"

constexpr double flatPotentiometerValue = 2500;
constexpr double verticalPotentiometerValue = 970;

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
                flatPotentiometerValue, verticalPotentiometerValue,
                positions::flat, positions::vertical));
    }

}
