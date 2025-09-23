using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision11__BLUEBOX;
extern signature Vision11__GREENBOX;
extern signature Vision11__REDBOX;
extern signature Vision11__SIG_4;
extern signature Vision11__SIG_5;
extern signature Vision11__SIG_6;
extern signature Vision11__SIG_7;
extern vision Vision11;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
