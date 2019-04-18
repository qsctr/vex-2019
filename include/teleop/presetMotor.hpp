#pragma once

#include "main.h"

namespace teleop {

    class PresetMotor {
        AbstractMotor& motor;
        bool preset {false};
    public:
        PresetMotor(AbstractMotor& motor);
        bool presetActive();
        void movePreset(double position, int32_t velocity);
        void movePreset(double position, int32_t velocity, std::function<void()> onSettled);
        void moveManual(int16_t voltage);
    };

}
