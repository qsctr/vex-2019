#include "main.h"

namespace teleop {

    template<std::size_t N>
    using ControlMap =
        std::array<std::pair<ControllerButton, std::function<void()>>, N>;

    namespace controlMap {

        template<std::size_t N>
        bool run(ControlMap<N> controls) {
            for (auto& [button, action] : controls) {
                if (button.isPressed()) {
                    action();
                    return true;
                }
            }
            return false;
        }

    }

}
