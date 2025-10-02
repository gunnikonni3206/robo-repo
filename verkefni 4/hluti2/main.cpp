#include "vex.h"
#include <cmath>

using namespace vex;

int main() {
  vexcodeInit();

  // Calibrate GPS
  if (GPS8.installed()) {
    Brain.Screen.print("Calibrating GPS...");
    GPS8.calibrate();
    while (GPS8.isCalibrating()) wait(20, msec);
    Brain.Screen.clearScreen();
  }

  // Speeds
  Drivetrain.setDriveVelocity(30, pct);  // slower forward
  Drivetrain.setTurnVelocity(8, pct);    // slow turning

  while (true) {
    double x = GPS8.xPosition(mm);
    double y = GPS8.yPosition(mm);
    double dist = sqrt(x * x + y * y);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("X: %.1f Y: %.1f D: %.1f", x, y, dist);

    // Stop if close enough
    if (dist <= 100) {
      Drivetrain.stop();
      break;
    }

    // ---- ROTATE for 3 seconds ----
    timer rotTimer;
    rotTimer.reset();
    while (rotTimer.time(sec) < 3) {
      // Target angle
      double targetAngle = atan2(-x, -y) * 180.0 / M_PI;
      if (targetAngle < 0) targetAngle += 360.0;

      // GPS mounted backwards → rotate 180
      double heading = GPS8.heading() + 180.0;
      if (heading >= 360.0) heading -= 360.0;

      double error = targetAngle - heading;
      while (error > 180) error -= 360;
      while (error < -180) error += 360;

      if (error > 5) {
        Drivetrain.turn(left);
      } else if (error < -5) {
        Drivetrain.turn(right);
      } else {
        Drivetrain.stop();
      }

      wait(50, msec);

      // Update position for next loop
      x = GPS8.xPosition(mm);
      y = GPS8.yPosition(mm);
      dist = sqrt(x * x + y * y);
      if (dist <= 50) break;
    }
    Drivetrain.stop();

    if (dist <= 50) break;

    // ---- DRIVE forward for 2 seconds ----
    timer driveTimer;
    driveTimer.reset();
    Drivetrain.drive(fwd);
    while (driveTimer.time(sec) < 3) {
      x = GPS8.xPosition(mm);
      y = GPS8.yPosition(mm);
      dist = sqrt(x * x + y * y);

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("X: %.1f Y: %.1f D: %.1f", x, y, dist);

      if (dist <= 50) break;
      wait(50, msec);
    }
    Drivetrain.stop();

    if (dist <= 50) break;
  }

  Drivetrain.stop(hold);
  while (true) wait(100, msec);
}
