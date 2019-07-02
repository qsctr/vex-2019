#include "util.hpp"
#include "main.h"

namespace util {

    void delayUntil(std::function<bool()> cond) {
        while (!cond()) {
            pros::delay(10);
        }
    }

}
