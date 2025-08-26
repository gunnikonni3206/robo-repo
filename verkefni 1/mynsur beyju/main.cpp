/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  This program will turn right 90 degrees using the         */
/*                  Inertial Sensor.                                          */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1               
// RightMotor           motor         10              
// Inertial20           inertial      20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void right90(){
    Drivetrain.driveFor(forward,500,mm);
    wait(0.3,seconds); 
    Inertial20.calibrate();
    while (Inertial20.isCalibrating()) {
      wait(200, msec);
    }
    LeftMotor.spin(forward);
    RightMotor.spin(reverse);
    waitUntil((Inertial20.rotation(degrees) >= 75.0));
    LeftMotor.stop();
    RightMotor.stop();
    wait(0.5, seconds);
  }
  void left90(){
    Drivetrain.driveFor(forward,500,mm);
    wait(0.3,seconds); 
    Inertial20.calibrate();
    while (Inertial20.isCalibrating()) {
      wait(200, msec);
    }
    LeftMotor.spin(reverse);
    RightMotor.spin(forward);
    waitUntil((Inertial20.rotation(degrees) <= -77.0));
    LeftMotor.stop();
    RightMotor.stop();
    wait(0.5, seconds);
  }

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial20.calibrate();
  // waits for the Inertial Sensor to calibrate
  while (Inertial20.isCalibrating()) {
    wait(100, msec);
  }
  right90();
  left90();
  left90();
  right90();
  right90();
  left90();
  right90();
  right90();
  left90();
  right90();
  right90();
  left90();
  left90();
  right90();
  Drivetrain.driveFor(forward,500,mm);

  
  
}
