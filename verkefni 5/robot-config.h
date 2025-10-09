using namespace vex;
using signature = vision::signature;
using code = vision::code;

extern brain Brain;

// VEXcode devices
extern signature Vision11__BLUEBOX;
extern signature Vision11__GREENBOX;
extern signature Vision11__REDBOX;
extern vision Vision13;
extern smartdrive Drivetrain;
extern gps GPS8;
extern distance Distance;
extern bumper BumperA;
extern motor ClawMotor;
extern motor ArmMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
