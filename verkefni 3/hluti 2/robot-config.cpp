#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision11__BLUEBOX =
    signature(1, -3441, -2785, -3113, 8975, 10355, 9665, 2.5, 0);
signature Vision11__GREENBOX =
    signature(2, -5767, -4965, -5366, -3803, -2861, -3332, 2.5, 0);
signature Vision11__REDBOX =
    signature(3, 8099, 8893, 8496, -1505, -949, -1227, 2.5, 0);
signature Vision11__SIG_4 = signature(4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_5 = signature(5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_6 = signature(6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision11__SIG_7 = signature(7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision11 =
    vision(PORT13, 50, Vision11__BLUEBOX, Vision11__GREENBOX, Vision11__REDBOX,
           Vision11__SIG_4, Vision11__SIG_5, Vision11__SIG_6, Vision11__SIG_7);
/*vex-vision-config:end*/

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}
