#include "util.hpp"
#include "main.h"
#include "constants.hpp"

namespace util {

    void delayUntil(std::function<bool()> cond) {
        while (!cond()) {
            pros::delay(loopCycleTime);
        }
    }

}
