#pragma once

#include "main.h"
#include "controller/voltageController.hpp"

class MultiController : public VoltageController {
    static constexpr double defaultVelocityScale = 1;
protected:
    const int32_t maxVelocity;
    std::unique_ptr<AsyncPosIntegratedController> posController;
    std::optional<std::function<void()>> onSettled;
    void setPosition(double position, double velocityScale);
public:
    MultiController(std::shared_ptr<AbstractMotor> motor,
        AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode);
    double getPosition();
    void movePosition(double position,
        double velocityScale = defaultVelocityScale);
    void movePosition(double position, std::function<void()> cb);
    void movePosition(double position, double velocityScale,
        std::function<void()> cb);
    void moveVoltage(double voltageScale) override;
    void moveVoltageDefault(double voltageScale);
    void checkSettled();
    void waitUntilSettled();
};
