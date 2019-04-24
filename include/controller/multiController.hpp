#pragma once

#include <variant>
#include "main.h"
#include "controller/voltageController.hpp"

class MultiController : public VoltageController {
    static constexpr double defaultVelocityScale = 1;
protected:
    struct SettledCallback {
        std::function<void ()> callback;
    };
    struct CustomCallback {
        std::function<bool ()> condition;
        std::function<void ()> callback;
    };
    const int32_t maxVelocity;
    std::unique_ptr<AsyncPosIntegratedController> posController;
    std::optional<std::variant<SettledCallback, CustomCallback>> callback;
    void setPosition(double position, double velocityScale);
    void execCallback(std::function<void ()> f);
public:
    MultiController(std::shared_ptr<AbstractMotor> motor,
        AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode);
    double getPosition();
    std::optional<double> getTarget();
    void movePosition(double position,
        double velocityScale = defaultVelocityScale);
    void movePosition(double position, std::function<void ()> settledCallback);
    void movePosition(double position, double velocityScale,
        std::function<void ()> settledCallback);
    void movePosition(double position, std::function<bool ()> condition,
        std::function<void ()> customCallback);
    void movePosition(double position, double velocityScale,
        std::function<bool ()> condition,
        std::function<void ()> customCallback);
    void moveVoltage(double voltageScale) override;
    void moveVoltageDefault(double voltageScale);
    void checkCallback();
    void waitUntilSettled();
};
