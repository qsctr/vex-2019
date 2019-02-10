#include "purescript.h"
#include "main.h"

FOREIGN_BEGIN(Pros_Motor)

exports["newMotor"] = [](const boxed& port) -> boxed {
    return [=](const boxed& gearset) -> boxed {
        return [=](const boxed& reverse) -> boxed {
            return [=](const boxed& encoder_units) -> boxed {
                return box<pros::Motor>(pros::Motor(
                    unbox<std::uint8_t>(port),
                    unbox<pros::motor_gearset_e_t>(gearset),
                    unbox<bool>(reverse),
                    unbox<pros::motor_encoder_units_e_t>(encoder_units)
                ));
            };
        };
    };
};

exports["gearset36"] = MOTOR_GEARSET_36;
exports["gearset18"] = MOTOR_GEARSET_18;
exports["gearset6"] = MOTOR_GEARSET_6;

exports["degrees"] = MOTOR_ENCODER_DEGREES;
exports["rotations"] = MOTOR_ENCODER_ROTATIONS;
exports["counts"] = MOTOR_ENCODER_COUNTS;

FOREIGN_END
