/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Fri Sep 27 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*    This project will detect 3 different colored objects and display        */
/*    when each object is found on the V5 Brain's screen.                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision5              vision        5
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

event checkRed = event();
event checkBlue = event();
event checkGreen = event();

void hasBlueCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(1, 1);
  Vision11.takeSnapshot(Vision11__BLUEBOX);
  if (Vision11.objectCount > 0) {
    Brain.Screen.print("Blár fundinn");
  } else {
    Brain.Screen.print("ekkert Blátt");
  }
}

void hasRedCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(3, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(3, 1);
  Vision11.takeSnapshot(Vision11__REDBOX);
  if (Vision11.objectCount > 0) {
    Brain.Screen.print("Rauður fundinn");
  } else {
    Brain.Screen.print("ekkert Rautt");
  }
}

void hasGreenCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(5, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(5, 1);
  Vision11.takeSnapshot(Vision11__GREENBOX);
  if (Vision11.objectCount > 0) {
    Brain.Screen.print("Grænn Fundin");
  } else {
    Brain.Screen.print("ekkert Grænt");
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  checkGreen(hasGreenCallback);
  
  while (true) {
    checkBlue.broadcastAndWait();
    checkRed.broadcastAndWait();
    checkGreen.broadcastAndWait();
    wait(1, seconds);
  }
}
