#include "vex.h"

using namespace vex;

brain Brain;
line LineTrackerE = line(Brain.ThreeWirePort.E);
line LineTrackerF = line(Brain.ThreeWirePort.F);
line LineTrackerG = line(Brain.ThreeWirePort.G);
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT7, ratio18_1, true);
digital_in digitalInputA = digital_in(Brain.ThreeWirePort.A);

void vexcodeInit(void) {
}
