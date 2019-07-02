#pragma once

#include <memory>
#include "main.h"
#include "controller/voltageController.hpp"

namespace robot::shooter {

    extern std::shared_ptr<VoltageController> controller;

    void initialize();

}
