using namespace vex;

extern brain Brain;

// VEXcode devices
extern line LineTrackerE; //left
extern line LineTrackerF; //middle
extern line LineTrackerG; //right
extern motor LeftMotor;
extern motor RightMotor;
extern vex::digital_in digitalInputA;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
