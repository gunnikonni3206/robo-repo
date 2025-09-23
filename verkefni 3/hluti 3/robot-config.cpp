#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

digital_in digitalInputA = digital_in(Brain.ThreeWirePort.A);
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT7, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart,
                                   TurnGyroSmart, 319.19, 320, 130, mm, 1);

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision13__RED1BOX = 
    signature(1, 8099, 8893, 8496, -1505, -949, -1227, 2.5, 0);
signature Vision13__RED2BOX =
    signature(2, -2489, -2097, -2293, 7669, 8117, 7893, 2.5, 0);
signature Vision13__RED3BOX =
    signature(3, -51, 51, 0, 32717, 32819, 32768, 2.5, 0);
signature Vision13__SIG_4 = signature(4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision13__SIG_5 = signature(5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision13__SIG_6 = signature(6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision13__SIG_7 = signature(7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision13 =
    vision(PORT13, 50, Vision13__RED1BOX, Vision13__RED2BOX, Vision13__RED3BOX,
           Vision13__SIG_4, Vision13__SIG_5, Vision13__SIG_6, Vision13__SIG_7);
/*vex-vision-config:end*/

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
    Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  inertial Inertial20 = inertial(PORT15);
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}
