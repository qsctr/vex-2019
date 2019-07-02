#include "robot.hpp"

namespace robot {

    void initialize() {
        robot::lift::initialize();
        robot::capIntake::initialize();
        robot::shooter::initialize();
        robot::ballIntake::initialize();
        robot::drive::initialize();
    }

}
