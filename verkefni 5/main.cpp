/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:             main.cpp                                                  */
/*    Author:             VEX                                                       */
/*    Created:            Wed Jun 09 2021                                           */
/*    Description:        Drive to Location (Unknown Starting Position)             */
/*                        This example will show how to use a GPS Sensor to         */
/*                        navigate a V5 Moby Hero Bot to a specified position       */
/*                        by driving along the X-axis then the Y-axis               */
/*                                                                                  */
/*    Starting Position:  Any                                                       */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10, 3        
// ForkMotorGroup       motor_group   2, 9            
// Rotation4            rotation      4               
// GPS8                 gps           8               
// DistanceLeft         distance      12              
// DistanceRight        distance      20              
// Optical19            optical       19              
// BumperA              bumper        A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int referenceAngle;
event checkRed = event();
event checkBlue = event();
event checkGreen = event();

void driveToPositionX(double x) {
  // Reorient the robot before driving along the X-axis
  if (GPS8.xPosition(mm) < x) {
    referenceAngle = 90;
  }
  else {
    referenceAngle = 270;
  }
  // Using an absolute reference angle along with the GPS heading,
  // we can turn the robot to face the correct direction before driving along the X-axis
  Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()), degrees, true);
  wait(1,seconds);
  if (!(GPS8.xPosition(mm) - x > -200 && GPS8.xPosition(mm) - x < 200)){
    Drivetrain.drive(forward);
  }
  // Keep driving until the GPS position for the X-axis is within 20mm of the target X position
  while (!(GPS8.xPosition(mm) - x > -10 && GPS8.xPosition(mm) - x < 10)) {
    wait(0.01, seconds);
  }

  // This will allow the drivetrain to stop in time, preventing the robot from overshooting the target
  wait(0.8,seconds);
  Drivetrain.stop();
}

void driveToPositionY(double y) {
  // Reorient the robot before driving along the Y-axis
  if (GPS8.yPosition(mm) < y) {
    referenceAngle = 0;
  }
  else {
    referenceAngle = 180;
  }
  // Using an absolute reference angle along with the GPS heading,
  // we can turn the robot to face the correct direction before driving along the Y-axis
  Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()), degrees, true);
  Drivetrain.drive(forward);

  // Keep driving until the GPS position for the Y-axis is within 20mm of the target Y position
  while (!(GPS8.yPosition(mm) - y > -10 && GPS8.yPosition(mm) - y < 10)) {
    wait(0.01, seconds);
  }

  // This will allow the drivetrain to stop in time, preventing the robot from overshooting the target
  wait(0.2,seconds);
  Drivetrain.stop();
}

void printPosition() {
  // Print GPS position values to the V5 Brain
  Brain.Screen.print("X: %.2f", GPS8.xPosition(mm));
  Brain.Screen.print("  Y: %.2f", GPS8.yPosition(mm));
  Brain.Screen.newLine();
}
void hasBlueCallback() {
  Vision13.takeSnapshot(Vision11__BLUEBOX);
  if (Vision13.objectCount > 0) {
    driveToPositionX(0);
    driveToPositionY(0);
    ClawMotor.spin(forward);
    wait(1,seconds);
    Drivetrain.drive(reverse);
    wait(0.5,seconds);
    Drivetrain.stop();
  } else {
    
  }
}

void hasRedCallback() {
  Vision13.takeSnapshot(Vision11__REDBOX);
  if (Vision13.objectCount > 0) {
    driveToPositionX(0);
    driveToPositionY(-500);
    ClawMotor.spin(forward);
    wait(1,seconds);
    Drivetrain.drive(reverse);
    wait(0.5,seconds);
    Drivetrain.stop();
  } else {
    
  }
}

void hasGreenCallback() {
  Vision13.takeSnapshot(Vision11__GREENBOX);
  if (Vision13.objectCount > 0) {
    driveToPositionX(0);
    driveToPositionY(-1000);
    ClawMotor.spin(forward);
    wait(1,seconds);
    Drivetrain.drive(reverse);
    wait(0.5,seconds);
    Drivetrain.stop();
  } else {
    
  }
}
void litir(){
  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  checkGreen(hasGreenCallback);
  checkBlue.broadcastAndWait();
  checkRed.broadcastAndWait();
  checkGreen.broadcastAndWait();
}
void keyr(int x,int y){
    GPS8.calibrate();
    while (GPS8.isCalibrating()) { task::sleep(50); }
    driveToPositionX(x);
    driveToPositionY(y);
    ClawMotor.spin(reverse);
    litir();
}
int main() {
  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  checkGreen(hasGreenCallback);
  Drivetrain.setTurnVelocity(8, percent);
  
  // Print the starting position of the robot
  printPosition();

  // Drive the robot to the specified X and Y position
  keyr(0,1600);
  keyr(-1600,1600);
  keyr(1600,1600);
  
  // Print the ending position of the robot
  printPosition();
}
