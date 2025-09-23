#include "vex.h"
using namespace vex;

// Assume Drivetrain has encoders and set speed is constant
int main() {
  vexcodeInit();

  // Tracking variables
  double totalDistance = 0.0; // mm
  timer t;
  t.reset();

  Drivetrain.setDriveVelocity(50, percent); // example speed

  while (true) {
    // Stop button check
    if (Controller1.ButtonStop.pressing()) {
      Drivetrain.stop();
      double timeSec = t.time(seconds);
      double avgSpeed = (timeSec > 0) ? (totalDistance / timeSec) : 0;
      Brain.Screen.clearScreen();
      Brain.Screen.print("Time: %.2f s", timeSec);
      Brain.Screen.newLine();
      Brain.Screen.print("Distance: %.2f mm", totalDistance);
      Brain.Screen.newLine();
      Brain.Screen.print("Avg Speed: %.2f mm/s", avgSpeed);
      break;
    }

    int d = Distance2.objectDistance(mm);

    if (!Distance2.isObjectDetected() || d >= 1000) {
      Drivetrain.drive(forward);
      // Add traveled distance from wheel rotation
      totalDistance += (Drivetrain.leftMotor().velocity(rpm) * 360.0/60.0) * (Drivetrain.wheelTravel() / 360.0) * 0.2;
    } else {
      Drivetrain.turnFor(left, 90, degrees);
    }

    wait(0.2, seconds);
  }
}
