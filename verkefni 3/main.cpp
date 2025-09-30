#include "vex.h"
#include <cstdlib>

using namespace vex;

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

      lastDist = newDist;
    }

    wait(0.2, seconds);
  }
}
