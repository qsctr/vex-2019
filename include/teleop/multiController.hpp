#include <cstdint>
#include <functional>
#include <optional>
#include <utility>
#include <variant>
#include "main.h"

namespace teleop {

    class MultiController {
        AbstractMotor& motor;
        AsyncPosIntegratedController& posController;
        int32_t maxVelocity;
        std::variant<short, std::pair<double, std::optional<std::function<void()>>>> state;
    public:
        MultiController(AbstractMotor& motor,
            AsyncPosIntegratedController posController);
        void movePreset(double position, double velocityScale);
        void moveManual(double voltageScale);
        void update();
    };

}
