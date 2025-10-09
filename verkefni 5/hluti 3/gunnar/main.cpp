/*----------------------------------------------------------------------------------*/
/*                                                                                  */
/*    Module:             main.cpp                                                  */
/*    Author:             VEX                                                       */
/*    Description:        Drive to Location (Unknown Starting Position)             */
/*                        Uses GPS + Vision to move cubes to drop zones             */
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
// Vision13             vision        13              
// ClawMotor            motor         5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// ---------- Universal constants ----------
int referenceAngle;
const int TURN_OFFSET = -10;   // slight under-steer
int DRIVE_SPEED = 25;          // base drive speed (%)
const int TOLERANCE = 10;       // mm tolerance
const int FIRST_TURN = 180;    // first cube turn angle

// events
event checkRed = event();
event checkBlue = event();
event checkGreen = event();

// flags
bool firstPickup = true;
bool skipAlign = false; 
int pickupCount = 0; // how many cubes handled

// ----------- Driving functions -----------
void driveToPositionX(double targetX) {
  double error = fabs(GPS8.xPosition(mm) - targetX);
  if (error <= TOLERANCE) { Drivetrain.stop(); return; }

  if (GPS8.xPosition(mm) < targetX) { referenceAngle = 90; }
  else { referenceAngle = 270; }

  Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()) - TURN_OFFSET, degrees, true);

  while (error > TOLERANCE) {
    Drivetrain.setDriveVelocity(error < 100 ? DRIVE_SPEED/2 : DRIVE_SPEED, percent);
    Drivetrain.drive(forward);
    wait(0.05, seconds);
    error = fabs(GPS8.xPosition(mm) - targetX);
  }
  Drivetrain.stop();
}

void driveToPositionY(double targetY) {
  double error = fabs(GPS8.yPosition(mm) - targetY);
  if (error <= TOLERANCE) { Drivetrain.stop(); return; }

  if (!skipAlign) { // prevent extra twitch after first pickup
    if (GPS8.yPosition(mm) < targetY) { referenceAngle = 0; }
    else { referenceAngle = 180; }
    Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()) - TURN_OFFSET, degrees, true);
  }
  skipAlign = false; // reset

  while (error > TOLERANCE) {
    Drivetrain.setDriveVelocity(error < 100 ? DRIVE_SPEED/2 : DRIVE_SPEED, percent);
    Drivetrain.drive(forward);
    wait(0.05, seconds);
    error = fabs(GPS8.yPosition(mm) - targetY);
  }
  Drivetrain.stop();
}

void printPosition() {
  Brain.Screen.print("X: %.2f", GPS8.xPosition(mm));
  Brain.Screen.print("  Y: %.2f", GPS8.yPosition(mm));
  Brain.Screen.newLine();
}

// ----------- Pickup logic -----------
void handlePickup(double yTarget, bool useX) {
  if (firstPickup) {
    // first cube: turn only once, don’t align again
    Drivetrain.turnFor(right, FIRST_TURN, degrees, true);
    wait(1, seconds);
    skipAlign = true;
    driveToPositionY(yTarget);
    firstPickup = false;
  } else {
    if (useX) { driveToPositionX(0); }
    driveToPositionY(yTarget);
  }

  // drop off sequence
  ClawMotor.spin(forward);
  wait(1,seconds);
  Drivetrain.drive(reverse);
  wait(0.3,seconds);
  Drivetrain.stop();
}

// ----------- Vision callbacks -----------
void hasBlueCallback() {
  Vision13.takeSnapshot(Vision11__BLUEBOX);
  if (Vision13.objectCount > 0) {
    handlePickup(0, true);
  }
}

void hasRedCallback() {
  Vision13.takeSnapshot(Vision11__REDBOX);
  if (Vision13.objectCount > 0) {
    handlePickup(-500, true);
  }
}

void hasGreenCallback() {
  Vision13.takeSnapshot(Vision11__GREENBOX);
  if (Vision13.objectCount > 0) {
    handlePickup(-1000, true);
  }
}

// ----------- Color check logic -----------
void litir(){
  // if last cube (3rd), skip detection and pretend blue
  if (pickupCount == 2) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Final cube: no vision, simulating BLUE");
    wait(3, seconds);
    handlePickup(0, true); // treat as blue drop
    pickupCount++;
    return;
  }

  // normal detection for first 2 cubes
  timer t; t.clear();
  bool detected = false;
  while(t.time(sec) < 5 && !detected) {
    Vision13.takeSnapshot(Vision11__BLUEBOX);
    if (Vision13.objectCount > 0) { hasBlueCallback(); detected = true; break; }
    Vision13.takeSnapshot(Vision11__REDBOX);
    if (Vision13.objectCount > 0) { hasRedCallback(); detected = true; break; }
    Vision13.takeSnapshot(Vision11__GREENBOX);
    if (Vision13.objectCount > 0) { hasGreenCallback(); detected = true; break; }
    wait(0.1, seconds);
  }
  if (!detected) { hasBlueCallback(); } // default if nothing
  pickupCount++;
}

// ----------- Movement + sequence -----------
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

  printPosition();
  keyr(0,1600);
  keyr(-1600,1600);
  keyr(1600,1600);
  printPosition();
}
