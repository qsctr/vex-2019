#pragma once

#include "main.h"

class VoltageController {
    static constexpr auto maxVoltage = 12000;
protected:
    std::shared_ptr<AbstractMotor> motor;
public:
    VoltageController(std::shared_ptr<AbstractMotor> motor,
        AbstractMotor::gearset gearing, AbstractMotor::brakeMode brakeMode);
    const std::shared_ptr<AbstractMotor> getMotor();
    virtual void moveVoltage(double voltageScale);
};
