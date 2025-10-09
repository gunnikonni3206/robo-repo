using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern vex::digital_in digitalInputA;
extern smartdrive Drivetrain;
extern inertial Inertial20;
extern signature Vision13__RED1BOX;  //blue
extern signature Vision13__RED2BOX; //green
extern signature Vision13__RED3BOX; //red
extern signature Vision13__SIG_4;
extern signature Vision13__SIG_5;
extern signature Vision13__SIG_6;
extern signature Vision13__SIG_7;
extern vision Vision13;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
