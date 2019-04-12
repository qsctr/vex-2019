#include "main.h"
#include "teleop/presetMotor.hpp"

namespace teleop {

    PresetMotor::PresetMotor(AbstractMotor& motor) : motor(motor) {}

    bool PresetMotor::presetActive() {
        return preset;
    }

    void PresetMotor::movePreset(double position, int32_t velocity) {
        motor.moveAbsolute(position, velocity);
        preset = true;
    }

    void PresetMotor::moveManual(int16_t voltage) {
        motor.moveVoltage(voltage);
        preset = false;
    }

}
