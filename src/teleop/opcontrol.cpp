#include "main.h"
#include "constants.hpp"
#include "robot.hpp"
#include "teleop/controlMap.hpp"
#include "teleop/presetMotor.hpp"

#include <cstdio>

namespace teleop {

    Controller capController {ControllerId::master};
    Controller ballController {ControllerId::partner};

    namespace buttons {
        ControllerButton manualLiftUp {ControllerId::master, ControllerDigital::R1};
        ControllerButton manualLiftDown {ControllerId::master, ControllerDigital::R2};
        ControllerButton manualCapIntakeIn {ControllerId::master, ControllerDigital::L1};
        ControllerButton manualCapIntakeOut {ControllerId::master, ControllerDigital::L2};
        ControllerButton groundPickup {ControllerId::master, ControllerDigital::B};
        ControllerButton lowPoleDelivery {ControllerId::master, ControllerDigital::A};
        ControllerButton highPoleDelivery {ControllerId::master, ControllerDigital::X};
        ControllerButton lowPolePickup {ControllerId::master, ControllerDigital::left};
        ControllerButton highPolePickup {ControllerId::master, ControllerDigital::up};
        ControllerButton capIntakeFlip {ControllerId::master, ControllerDigital::right};
        ControllerButton capIntakeFlat {ControllerId::master, ControllerDigital::down};
        ControllerButton shoot {ControllerId::partner, ControllerDigital::R1};
        ControllerButton ballIntakeIn {ControllerId::partner, ControllerDigital::L1};
        ControllerButton ballIntakeOut {ControllerId::partner, ControllerDigital::L2};
    }

    // namespace presetMotors {
    //     PresetMotor lift {robot::lift};
    //     PresetMotor capIntake {robot::capIntake};
    // }

}

void opcontrol() {
    using namespace teleop;
    // ADIButton leftLiftLimitSwitch {'G'};
    // ADIButton rightLiftLimitSwitch {'H'};
    // Potentiometer capIntakePotentiometer {'F'};
    // ADIButton guideLimitSwitch {'E'};
    // int i = 0;
    // presetMotors::lift.moveManual(-MAX_VOLTAGE);
    // while (!(leftLiftLimitSwitch.isPressed() && rightLiftLimitSwitch.isPressed())) {
    //     pros::Task::delay(10);
    // }
    // robot::lift.tarePosition();
    // presetMotors::lift.movePreset(0, GREEN_RPM);
    // pros::Task::delay(500);
    // robot::capIntake.set_zero_position(remapRange(capIntakePotentiometer.get(), 2600, 1070, 0, 265));
    // while (true) {
    //     robot::drive.tank(
    //         capController.getAnalog(ControllerAnalog::leftY),
    //         capController.getAnalog(ControllerAnalog::rightY));

    //     if (buttons::groundPickup.isPressed()) {
    //         presetMotors::lift.movePreset(-50, RED_RPM);
    //         presetMotors::capIntake.movePreset(-30, RED_RPM);
    //     } else if (buttons::lowPoleDelivery.isPressed()) {
    //         presetMotors::lift.movePreset(600, RED_RPM);
    //         presetMotors::capIntake.movePreset(-30, RED_RPM);
    //     } else if (buttons::highPoleDelivery.isPressed()) {
    //         presetMotors::lift.movePreset(750, RED_RPM);
    //         presetMotors::capIntake.movePreset(70, RED_RPM);
    //     } else if (buttons::lowPolePickup.isPressed()) {
    //         presetMotors::lift.movePreset(300, RED_RPM);
    //         presetMotors::capIntake.movePreset(0, RED_RPM);
    //     } else if (buttons::highPolePickup.isPressed()) {
    //         presetMotors::lift.movePreset(500, RED_RPM);
    //         presetMotors::capIntake.movePreset(0, RED_RPM);
    //     }
    //     if (buttons::manualLiftUp.isPressed()) {
    //         presetMotors::lift.moveManual(MAX_VOLTAGE);
    //     } else if (buttons::manualLiftDown.isPressed()) {
    //         presetMotors::lift.moveManual(-MAX_VOLTAGE);
    //     } else if (!presetMotors::lift.presetActive()) {
    //         presetMotors::lift.moveManual(0);
    //     }
    //     if (buttons::capIntakeFlip.isPressed()) {
    //         presetMotors::capIntake.movePreset(300, RED_RPM);
    //     } else if (buttons::capIntakeFlat.isPressed()) {
    //         presetMotors::capIntake.movePreset(0, RED_RPM);
    //     }
    //     if (buttons::manualCapIntakeIn.isPressed()) {
    //         presetMotors::capIntake.moveManual(MAX_VOLTAGE);
    //     } else if (buttons::manualCapIntakeOut.isPressed()) {
    //         presetMotors::capIntake.moveManual(-MAX_VOLTAGE);
    //     } else if (!presetMotors::capIntake.presetActive()) {
    //         presetMotors::capIntake.moveManual(0);
    //     }
    //     if (buttons::ballIntakeIn.isPressed()) {
    //         robot::ballIntake.moveVoltage(MAX_VOLTAGE);
    //     } else if (buttons::ballIntakeOut.isPressed()) {
    //         robot::ballIntake.moveVoltage(-MAX_VOLTAGE);
    //     } else {
    //         robot::ballIntake.moveVoltage(0);
    //     }
    //     if (buttons::shoot.isPressed()) {
    //         robot::shooter.moveVoltage(MAX_VOLTAGE);
    //     } else {
    //         robot::shooter.moveVoltage(0);
    //     }
    //     if (leftLiftLimitSwitch.isPressed() && rightLiftLimitSwitch.isPressed()) {
    //         robot::lift.tarePosition();
    //     }
    //     if (i == 200) {
    //         // controller.setText(0, 0, std::to_string(robot::lift.getFaults()));
    //         capController.setText(0, 0, std::to_string(robot::lift.getPosition()));
    //         i = 0;
    //     }
    //     // printf("%f %f %f\n", robot::lift.getPosition(), robot::capIntake.getPosition(), capIntakePotentiometer.get());
    //     pros::Task::delay(10);
    //     i++;
    // }
}
