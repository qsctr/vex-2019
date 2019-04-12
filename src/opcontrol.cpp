#include "main.h"
#include "constants.h"
#include "presetMotor.h"
#include "robot.h"

#include <cstdio>

namespace {

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
    }

    namespace presetMotors {
        PresetMotor lift {robot::lift};
        PresetMotor intake {robot::intake};
    }

    // auto presetControl(AbstractMotor& motor) {
    //     bool presetActive = false;
    //     return [&] {
    //         if (buttons::manualLiftUp.isPressed()) {
    //             motor.moveVoltage(MAX_VOLTAGE);
    //             presetActive = false;
    //         } else if (buttons::manualLiftDown.isPressed()) {
    //             motor.moveVoltage(-MAX_VOLTAGE);
    //             presetActive = false;
    //         } else if (!presetActive) {
    //             motor.moveVoltage(0);
    //         }
    //         if (buttons::groundPickup.isPressed()) {
    //             motor.moveAbsolute(-50, GREEN_RPM);
    //             presetActive = true;
    //         } else if (buttons::lowPoleDelivery.isPressed()) {
    //             motor.moveAbsolute(600, GREEN_RPM);
    //             presetActive = true;
    //         } else if (buttons::highPoleDelivery.isPressed()) {
    //             motor.moveAbsolute(700, GREEN_RPM);
    //             presetActive = true;
    //         }
    //     };
    // }

}

void opcontrol() {
    double liftTarget = -200;
    // intake 960 flat
        // rel 600 up
        // rel -30 down

    ADIButton limitSwitch {'A'};
    Potentiometer pot {'B'};
    int i = 0;
    // controller.setText(0, 0, "hello");
    // remapRange(pot.get(), 1760, 3350, 0, 266)
    presetMotors::lift.moveManual(-MAX_VOLTAGE);
    while (!limitSwitch.isPressed()) {
        pros::Task::delay(10);
    }
    robot::lift.tarePosition();
    presetMotors::lift.movePreset(-50, GREEN_RPM);
    pros::Task::delay(100);
    double intakePos = remapRange(pot.get(), 3350, 1760, 0, 266);
    printf("%f\n", intakePos);
    robot::intake.set_zero_position(intakePos);
    // bool intakePreset = true;
    // auto intakeController = AsyncControllerFactory::posPID(robot::intake, pot, -0.006636, 0.342856, 0.211047);
    // auto intakeController = AsyncControllerFactory::posPID(robot::intake, pot, -0.01, -0.835209, -0.826340);
    // auto intakeController = AsyncControllerFactory::posPID(robot::intake, pot, -0.0015, 0, -1);
    // intakeController.flipDisable(true);
    // auto tuner = PIDTunerFactory::create(std::make_shared<Potentiometer>(pot), std::make_shared<Motor>(robot::intake), 1_s, 3350, -0.01, 0, -1, 0, -1, 0);
    while (true) {
        robot::drive.tank(
            controller.getAnalog(ControllerAnalog::leftY),
            controller.getAnalog(ControllerAnalog::rightY));
        if (buttons::groundPickup.isPressed()) {
            presetMotors::lift.movePreset(-50, GREEN_RPM);
            presetMotors::intake.movePreset(-30, RED_RPM);
        } else if (buttons::lowPoleDelivery.isPressed()) {
            presetMotors::lift.movePreset(600, GREEN_RPM);
            presetMotors::intake.movePreset(-30, RED_RPM / 4);
        } else if (buttons::highPoleDelivery.isPressed()) {
            presetMotors::lift.movePreset(700, GREEN_RPM);
            presetMotors::intake.movePreset(70, RED_RPM / 4);
        } else if (buttons::lowPolePickup.isPressed()) {
            presetMotors::lift.movePreset(300, GREEN_RPM);
            presetMotors::intake.movePreset(0, RED_RPM / 4);
        } else if (buttons::highPolePickup.isPressed()) {
            presetMotors::lift.movePreset(500, GREEN_RPM);
            presetMotors::intake.movePreset(0, RED_RPM / 4);
        }
        if (buttons::manualLiftUp.isPressed()) {
            presetMotors::lift.moveManual(MAX_VOLTAGE);
        } else if (buttons::manualLiftDown.isPressed()) {
            presetMotors::lift.moveManual(-MAX_VOLTAGE);
        } else if (!presetMotors::lift.presetActive()) {
            presetMotors::lift.moveManual(0);
        }
        if (buttons::manualIntakeIn.isPressed()) {
            presetMotors::intake.moveManual(MAX_VOLTAGE);
        } else if (buttons::manualIntakeOut.isPressed()) {
            presetMotors::intake.moveManual(-MAX_VOLTAGE);
        } else if (!presetMotors::intake.presetActive()) {
            presetMotors::intake.moveManual(0);
        }
        // if (buttons::manualIntakeIn.isPressed()) {
        //     robot::intake.moveVoltage(MAX_VOLTAGE);
        //     intakePreset = false;
        // } else if (buttons::manualIntakeOut.isPressed()) {
        //     robot::intake.moveVoltage(-MAX_VOLTAGE);
        //     intakePreset = false;
        // }
        // else if (buttons::intakeFlat.isPressed()) {
        //     intakeController.flipDisable(false);
        //     intakeController.setTarget(3350);
        //     // auto output = tuner.autotune();
        //     // printf("%f\t%f\t%f\n", output.kP, output.kI, output.kD);
        // }
        // else {
        //     intakeController.flipDisable(true);
        //     robot::intake.moveVoltage(0);
        //     intakePreset = false;
        // }
        if (limitSwitch.isPressed()) {
            robot::lift.tarePosition();
        }
        // if (buttons::manualLiftUp.isPressed() && liftTarget < 800) {
        //     liftTarget += 10;
        // }
        // if (buttons::manualLiftDown.isPressed() && liftTarget > -200) {
        //     liftTarget -= 10;
        // }
        // robot::lift.moveAbsolute(liftTarget, 200);
        // if (controller.getDigital(ControllerDigital::A)) {
        //     robot::lift.moveAbsolute(-200, 200);
        // } else {
            // robot::lift.moveVoltage(
            //     buttons::manualLiftUp.isPressed() ? 12000 :
            //     buttons::manualLiftDown.isPressed() ? -12000 :
            //     0);
        // }
        // robot::intake.moveVoltage(
        //     buttons::manualIntakeIn.isPressed() ? 12000 :
        //     buttons::manualIntakeOut.isPressed() ? -12000 :
        //     0);
        if (i == 200) {
            // controller.setText(0, 0, std::to_string(robot::lift.getFaults()));
            controller.setText(0, 0, std::to_string(robot::lift.getPosition()));
            i = 0;
        }
        printf("%f %f %d %f %x\n", robot::lift.getPosition(), robot::intake.getPosition(), limitSwitch.isPressed(), pot.get(), robot::lift.getFaults());
        pros::Task::delay(10);
        i++;
    }
}
