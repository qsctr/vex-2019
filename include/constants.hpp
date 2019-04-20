#pragma once

#include "main.h"

constexpr int MAX_VOLTAGE = 12000;

constexpr int RED_RPM = toUnderlyingType(AbstractMotor::gearset::red);
constexpr int GREEN_RPM = toUnderlyingType(AbstractMotor::gearset::green);
constexpr int BLUE_RPM = toUnderlyingType(AbstractMotor::gearset::blue);

constexpr uint32_t SENSOR_INITIALIZATION_TIME = 500;
