#include "main.h"
#include "robot.hpp"
#include "util.hpp"

namespace {

    enum class Color {
        Red,
        Blue
    };
    constexpr auto color = Color::Red;

    enum class Tile {
        Front,
        Back
    };
    constexpr auto tile = Tile::Back;

    enum class Mode {
        PlaceCap,
        Climb
    };
    constexpr auto mode = Mode::PlaceCap;

    namespace pathIds {
        constexpr auto toCap = "toCap";
    }

}

void autonomous() {
    robot::drive::controller->setTurnsMirrored(color == Color::Red);
    robot::lift::reset();
    robot::lift::controller->movePosition(100);
    robot::lift::controller->waitUntilSettled();
    if constexpr (tile == Tile::Back) {
        if constexpr (mode == Mode::PlaceCap) {
            auto profileController = AsyncControllerFactory::motionProfile(
                0.6, 3, 6, *robot::drive::controller);
            constexpr int blueSide = color == Color::Blue ? 1 : -1;
            profileController.generatePath({
                Point {0_in, 0_in, 0_deg},
                Point {29_in, blueSide * 5_in, blueSide * 45_deg},
                Point {40_in, blueSide * 16_in, blueSide * 45_deg}
            }, pathIds::toCap);
            profileController.setTarget(pathIds::toCap);
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::groundPickup);
            robot::ballIntake::controller->moveVoltage(-1);
            robot::lift::controller->movePosition(-10);
            pros::delay(200);
            robot::ballIntake::controller->moveVoltage(1);
            robot::capIntake::controller->waitUntilSettled();
            profileController.waitUntilSettled();
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flat);
            robot::lift::controller->movePosition(300);
            robot::capIntake::controller->waitUntilSettled();
            robot::lift::controller->waitUntilSettled();
            robot::drive::controller->setMaxVelocity(100);
            robot::drive::controller->moveDistance(-24_in);
            robot::drive::controller->turnAngle(-46_deg);
            robot::lift::controller->movePosition(
                robot::lift::positions::lowPoleDelivery);
            robot::drive::controller->moveDistanceAsync(10_in);
            robot::lift::controller->waitUntilSettled();
            robot::drive::controller->waitUntilSettled();
            robot::drive::controller->moveDistance(12.5_in);
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::flip);
            robot::capIntake::controller->waitUntilSettled();
            robot::capIntake::controller->movePosition(
                robot::capIntake::positions::lowPoleDelivery);
            robot::capIntake::controller->waitUntilSettled();
            robot::lift::controller->movePosition(
                robot::lift::positions::lowPoleDelivery2);
            util::delayUntil([] {
                return robot::lift::controller->getPosition() < 500;
            });
            robot::drive::controller->moveDistance(-9_in);
            robot::drive::controller->turnAngle(-12_deg);
            robot::shooter::controller->moveVoltage(1);
            pros::delay(700);
            robot::shooter::controller->moveVoltage(0);
        } else if constexpr (mode == Mode::Climb) {
            robot::ballIntake::controller->moveVoltage(-1);
            pros::delay(500);
            robot::ballIntake::controller->moveVoltage(0);
            robot::drive::controller->moveDistance(-25.5_in);
            robot::drive::controller->turnAngle(-90_deg);
            robot::drive::controller->moveDistance(-46_in);
        }
    } else if constexpr (tile == Tile::Front) {
        robot::drive::controller->moveDistance(-40_in);
        robot::drive::controller->moveDistance(20_in);
    }

}
