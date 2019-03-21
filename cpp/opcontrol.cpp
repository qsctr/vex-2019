#include "main.h"

pros::Controller controller(CONTROLLER_MASTER);
pros::Motor frontLeftMotor(1, MOTOR_GEARSET_18);
pros::Motor backLeftMotor(11, MOTOR_GEARSET_18);
pros::Motor frontRightMotor(10, MOTOR_GEARSET_18, true);
pros::Motor backRightMotor(20, MOTOR_GEARSET_18, true);
pros::Motor leftLiftMotor(2, MOTOR_GEARSET_18, true);
pros::Motor rightLiftMotor(9, MOTOR_GEARSET_18);
pros::Motor intakeMotor(3, MOTOR_GEARSET_18);

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	frontLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	frontRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	leftLiftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	rightLiftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	intakeMotor.set_encoder_units(MOTOR_ENCODER_DEGREES);
	// controller.print(0, 0, "hello world");
	while (true) {
		frontLeftMotor = controller.get_analog(ANALOG_LEFT_Y);
		backLeftMotor = controller.get_analog(ANALOG_LEFT_Y);
		frontRightMotor = controller.get_analog(ANALOG_RIGHT_Y);
		backRightMotor = controller.get_analog(ANALOG_RIGHT_Y);
		if (controller.get_digital(DIGITAL_R1)) {
			leftLiftMotor = 127;
			rightLiftMotor = 127;
		} else if (controller.get_digital(DIGITAL_R2)) {
			leftLiftMotor = -127;
			rightLiftMotor = -127;
		} else {
			leftLiftMotor = 0;
			rightLiftMotor = 0;
		}
		if (controller.get_digital(DIGITAL_L1)) {
			intakeMotor.move_absolute(180, 75);
		} else if (controller.get_digital(DIGITAL_L2)) {
			intakeMotor.move_absolute(0, 75);
		}
		pros::delay(20);
	}
}
