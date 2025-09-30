/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*   This program will have the robot move left when it senses higher         */
/*   reflectivity than the threshold (Light maximum reflectivity +            */
/*   Dark maximum reflectivity / 2) and will move to the right when it        */
/*   senses less reflectivity than the threshold.                             */
/*                                                                            */
/*   IMPORTANT: In order for this program to work correctly, the Line         */
/*   Tracker needs to be mounted facing down towards the ground, close        */
/*   to the ground.                                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A
// LeftMotor            motor         1
// RightMotor           motor         10
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

float threshold;

int main() {
  vexcodeInit();

  threshold = 45;
  int base = 25;
  int delta = 5;
  int lastDir = 0;
  timer t;
  uint32_t lastInc = 0;

  while (digitalInputA.value() == 1) {
    Brain.Screen.clearScreen();
    bool L = LineTrackerE.reflectivity() < threshold;
    bool M = LineTrackerF.reflectivity() < threshold;
    bool R = LineTrackerG.reflectivity() < threshold;

    bool sensing = L || M || R;

    if (!sensing) {
      uint32_t now = t.time(msec);
      if (now - lastInc >= 100) {
        if (delta < 40) delta += 1;
        lastInc = now;
      }
    } else {
      delta = 5;
      lastInc = t.time(msec);
    }

    int desired = 0;
    if (L && !R) { desired = +1; lastDir = +1; }
    else if (R && !L) { desired = -1; lastDir = -1; }
    else if (!sensing || (L && R && !M)) { desired = lastDir; }

    int fwd = base + (M ? 5 : 0);

    int lm = fwd;
    int rm = fwd;

    if (desired == +1) {
      lm = fwd + delta;
      rm = fwd - delta;
      Brain.Screen.printAt(10, 60, "Left");
    } else if (desired == -1) {
      lm = fwd - delta;
      rm = fwd + delta;
      Brain.Screen.printAt(10, 60, "Right");
    }
    else {
      Brain.Screen.printAt(10, 60, "Forward");
    }

    if (lm < 0) lm = 0; if (lm > 100) lm = 100;
    if (rm < 0) rm = 0; if (rm > 100) rm = 100;

    LeftMotor.spin(forward, lm, percent);
    RightMotor.spin(forward, rm, percent);

    wait(20, msec);
  }
  Brain.programStop();
}
