#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT7, ratio18_1, true);
inertial DrivetrainInertial = inertial(PORT10);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);
gps GPS8 = gps(PORT4, 0.00, -240.00, mm, 180);
distance Distance = distance(PORT9);
bumper Neydarhnappi = bumper(Brain.ThreeWirePort.A);
motor ClawMotor = motor(PORT3, ratio18_1, false);
motor ArmMotor = motor(PORT8, ratio18_1, false);
signature Vision11__BLUEBOX =
    signature(1, 4301, 4807, 4554, 5887, 6401, 6144, 2.5, 0);
signature Vision11__GREENBOX =
    signature(2, -5767, -4965, -5366, -3803, -2861, -3332, 2.5, 0);
signature Vision11__REDBOX =
    signature(3, 8099, 8893, 8496, -1505, -949, -1227, 2.5, 0);
signature Vision11__SIG_4 = signature(4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_5 = signature(5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_6 = signature(6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_7 = signature(7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision13 =
    vision(PORT13, 50, Vision11__BLUEBOX, Vision11__GREENBOX, Vision11__REDBOX,
           Vision11__SIG_4, Vision11__SIG_5, Vision11__SIG_6, Vision11__SIG_7);




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}