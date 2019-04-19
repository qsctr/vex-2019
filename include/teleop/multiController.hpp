#include <cstdint>
#include "main.h"

namespace teleop {

    class MultiController {
        AbstractMotor& motor;
        AsyncPosIntegratedController& posController;
        int32_t maxVelocity;
        bool presetActive;
        std::optional<std::function<void()>> onSettled;
        void setPreset(double position, double velocityScale);
    public:
        MultiController(AbstractMotor& motor,
            AsyncPosIntegratedController& posController);
        void movePreset(double position, double velocityScale = 1);
        void movePreset(double position, std::function<void()> onSettled);
        void movePreset(double position, double velocityScale,
        std::function<void()> onSettled);
        void moveManualOverride(double voltageScale);
        void moveManualDefault(double voltageScale);
        void update();
    };

}
