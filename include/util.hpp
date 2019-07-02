#pragma once

#include <functional>

namespace util {

    void delayUntil(std::function<bool ()> cond);

}
