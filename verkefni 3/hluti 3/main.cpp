#include "vex.h"

using namespace vex;

const int CENTER_FOV = 158;
const int OFFSET_X = 15;

int main() {
  vexcodeInit();

  while (digitalInputA.value() == 1) {
    Brain.Screen.clearLine(1);
    Brain.Screen.clearLine(2);

   
    Vision13.takeSnapshot(Vision13__RED1BOX);

    
    if (Vision13.largestObject.exists) {
      int width = Vision13.largestObject.width;
      int centerX = Vision13.largestObject.centerX;
      Brain.Screen.printAt(10, 40, "Width: %d", width);
      if(width > 120 && width < 1000){
        Drivetrain.drive(reverse,5 ,velocityUnits::pct);
        Brain.Screen.printAt(10, 60, "afurabak");
      }
      else if (centerX < CENTER_FOV - OFFSET_X) {
        Drivetrain.turn(left, 1, velocityUnits::pct);
        Brain.Screen.printAt(10, 60, "vinstri");
        
      }
      else if (centerX > CENTER_FOV + OFFSET_X) {   
        Drivetrain.turn(right, 1, velocityUnits::pct);
        Brain.Screen.printAt(10, 60, "Hægri");
        
      }
       else if(width < 60) {
        Drivetrain.drive(forward, 20, velocityUnits::pct);
        Brain.Screen.printAt(10, 60, "Áfram");
      }
      else if(width < 95) {
        Drivetrain.drive(forward, 10, velocityUnits::pct);
        Brain.Screen.printAt(10, 60, "Áfram");
      }
      else {
        Drivetrain.stop();
        Brain.Screen.printAt(10, 60, "FANN DAD");
      }
    } else {
      Drivetrain.stop();
      Brain.Screen.printAt(10, 40, "See ekkert");
    }

    wait(20, msec);
  }
  Brain.programStop();
}
