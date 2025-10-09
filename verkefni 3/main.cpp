#include "vex.h"

using namespace vex;

const int CENTER_FOV = 158;
const int OFFSET_X = 15;

int main() {
  vexcodeInit();

  int lastDist = 9999;
  int lastDir = 0;

  while (true) {
    int d = Distance2.objectDistance(mm);

    if (!Distance2.isObjectDetected() || d >= 1000) {
      Drivetrain.drive(forward);
    } else {
      int deg = (rand() % 91) + 90;
      int dir = (lastDir == 0) ? ((rand() % 2) ? 1 : -1) : lastDir;

      if (dir > 0) Drivetrain.turnFor(left, deg, degrees);
      else Drivetrain.turnFor(right, deg, degrees);

      int newDist = Distance2.objectDistance(mm);

      if (newDist <= lastDist) {
        if (dir > 0) Drivetrain.turnFor(right, deg, degrees);
        else Drivetrain.turnFor(left, deg, degrees);
        lastDir = -dir;
      } else {
        lastDir = dir;
      }
    } else {
      Drivetrain.stop();
      Brain.Screen.printAt(10, 40, "See ekkert");
    }

    wait(20, msec);
  }
  Brain.programStop();
}
