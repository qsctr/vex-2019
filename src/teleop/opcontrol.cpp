#include "main.h"
#include "constants.hpp"
#include "robot.hpp"
#include "teleop/controlMap.hpp"
#include "teleop/presetMotor.hpp"

#include <cstdio>

namespace teleop {

    Controller controller;

    namespace buttons {
        ControllerButton manualLiftUp(ControllerDigital::R1);
        ControllerButton manualLiftDown(ControllerDigital::R2);
        ControllerButton manualIntakeIn(ControllerDigital::L1);
        ControllerButton manualIntakeOut(ControllerDigital::L2);
        ControllerButton groundPickup(ControllerDigital::B);
        ControllerButton lowPoleDelivery(ControllerDigital::A);
        ControllerButton highPoleDelivery(ControllerDigital::X);
        ControllerButton lowPolePickup(ControllerDigital::left);
        ControllerButton highPolePickup(ControllerDigital::up);
        ControllerButton intakeFlip(ControllerDigital::right);
        ControllerButton intakeFlat(ControllerDigital::down);
    }

    namespace presetMotors {
        PresetMotor lift {robot::lift};
        PresetMotor intake {robot::intake};
    }

    template<std::size_t P, std::size_t M>
    auto makePresetRunner(ControlMap<P> presetControls,
    ControlMap<M> manualControls, std::function<void()> manualDefault) {
        return [=, presetActive = false]() mutable {
            if (controlMap::run(manualControls)) {
                presetActive = false;
            } else if (controlMap::run(presetControls)) {
                presetActive = true;
            } else if (!presetActive) {
                manualDefault();
            }
        };
    }

    

    // auto runLift = makePresetRunner({
    //     {buttons::groundPickup, [] {
    //         robot::lift.moveAbsolute(-50, GREEN_RPM);
    //         robot::intake.moveAbsolute(-30, RED_RPM);
    //     }},
    //     {buttons::lowPoleDelivery, [] {
    //         robot::lift.moveAbsolute(600, GREEN_RPM);
    //         robot::intake.moveAbsolute(-30, RED_RPM / 2);
    //     }},
    //     {buttons::highPoleDelivery, [] {
    //         robot::lift.moveAbsolute(750, GREEN_RPM);
    //         robot::intake.moveAbsolute(70, RED_RPM / 2);
    //     }},
    //     {buttons::lowPolePickup, [] {
    //         robot::lift.moveAbsolute(300, GREEN_RPM);
    //         robot::intake.moveAbsolute(0, RED_RPM / 2);
    //     }},
    //     {buttons::highPolePickup, [] {
    //         robot::lift.moveAbsolute(500, GREEN_RPM);
    //         robot::intake.moveAbsolute(0, RED_RPM / 2);
    //     }}
    // }, {
    //     {buttons::manualLiftUp, [] {

    //     }}
    // })

}

void opcontrol() {
    using namespace teleop;
    // ADIButton limitSwitch {'A'};
    Potentiometer pot {'B'};
    int i = 0;
    // presetMotors::lift.moveManual(-MAX_VOLTAGE);
    // while (!limitSwitch.isPressed()) {
    //     pros::Task::delay(10);
    // }
    // robot::lift.tarePosition();
    // presetMotors::lift.movePreset(-50, GREEN_RPM);
    pros::Task::delay(500);
    double intakePos = remapRange(pot.get(), 3350, 1760, 0, 266);
    printf("%f\n", intakePos);
    robot::intake.set_zero_position(intakePos);
    while (true) {
        robot::drive.tank(
            controller.getAnalog(ControllerAnalog::leftY),
            controller.getAnalog(ControllerAnalog::rightY));

        // if (buttons::manualLiftUp.isPressed()) {
        //     presetMotors::lift.moveManual(MAX_VOLTAGE);
        // } else if (buttons::manualLiftDown.isPressed()) {
        //     presetMotors::lift.moveManual(-MAX_VOLTAGE);
        // }

        if (buttons::groundPickup.isPressed()) {
            presetMotors::lift.movePreset(-50, GREEN_RPM);
            presetMotors::intake.movePreset(-30, RED_RPM);
        } else if (buttons::lowPoleDelivery.isPressed()) {
            presetMotors::lift.movePreset(600, GREEN_RPM);
            presetMotors::intake.movePreset(-30, RED_RPM);
        } else if (buttons::highPoleDelivery.isPressed()) {
            presetMotors::lift.movePreset(750, GREEN_RPM);
            presetMotors::intake.movePreset(70, RED_RPM);
        } else if (buttons::lowPolePickup.isPressed()) {
            presetMotors::lift.movePreset(300, GREEN_RPM);
            presetMotors::intake.movePreset(0, RED_RPM);
        } else if (buttons::highPolePickup.isPressed()) {
            presetMotors::lift.movePreset(500, GREEN_RPM);
            presetMotors::intake.movePreset(0, RED_RPM);
        }
        if (buttons::manualLiftUp.isPressed()) {
            presetMotors::lift.moveManual(MAX_VOLTAGE);
        } else if (buttons::manualLiftDown.isPressed()) {
            presetMotors::lift.moveManual(-MAX_VOLTAGE);
        } else if (!presetMotors::lift.presetActive()) {
            presetMotors::lift.moveManual(0);
        }
        if (buttons::intakeFlip.isPressed()) {
            presetMotors::intake.movePreset(300, RED_RPM);
        } else if (buttons::intakeFlat.isPressed()) {
            presetMotors::intake.movePreset(0, RED_RPM);
        }
        if (buttons::manualIntakeIn.isPressed()) {
            presetMotors::intake.moveManual(MAX_VOLTAGE);
        } else if (buttons::manualIntakeOut.isPressed()) {
            presetMotors::intake.moveManual(-MAX_VOLTAGE);
        } else if (!presetMotors::intake.presetActive()) {
            presetMotors::intake.moveManual(0);
        }
        // if (limitSwitch.isPressed()) {
        //     robot::lift.tarePosition();
        // }
        if (i == 200) {
            // controller.setText(0, 0, std::to_string(robot::lift.getFaults()));
            controller.setText(0, 0, std::to_string(robot::lift.getPosition()));
            i = 0;
        }
        printf("%f %f %f %x\n", robot::lift.getPosition(), robot::intake.getPosition(), pot.get(), robot::lift.getFaults());
        pros::Task::delay(10);
        i++;
    }
}
