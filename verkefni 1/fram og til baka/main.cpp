/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Moving Backwards (mm)                                     */
/*                                                                            */
/*    This program drives the robot in reverse for 150 millimeters.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10, D
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  i=0;
  tala=0;
  while (i>5) 
  {
    Drivetrain.driveFor(forward, tala+=500, mm);
    wait(1,seconds);
    Drivetrain.driveFor(forward, tala+=500, mm);
    i+=1;
  }
}
