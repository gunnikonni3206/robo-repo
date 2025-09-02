#include "vex.h"
using namespace vex;

motor LeftMotor  = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT7, ratio18_1, true);

const double WHEEL_DIAM_CM  = 9.45;
const double TRACK_WIDTH_CM = 23.0;
const double PI = 3.141592653589793;

double cmToRevs(double cm){ 
  return cm / (PI * WHEEL_DIAM_CM); 
}

void driveCircle(float radius, float speed){
  double rL = radius - 0.5 * TRACK_WIDTH_CM;
  double rR = radius + 0.5 * TRACK_WIDTH_CM;
  if(rL <= 0) return;
  double revL = cmToRevs(2.0 * PI * rL);
  double revR = cmToRevs(2.0 * PI * rR);
  double longest = revL > revR ? revL : revR;
  double vL = speed * (revL / longest);
  double vR = speed * (revR / longest);
  LeftMotor.setVelocity(vL, percent);
  RightMotor.setVelocity(vR, percent);
  LeftMotor.spinFor(revL, rev, false);
  RightMotor.spinFor(revR, rev, true);
}

int main(){
  int i=0;
  float radius = 45.0;
  while(i<3){
    driveCircle(radius, 30.0);
    radius += 5;
    i+=1;
  }
}
