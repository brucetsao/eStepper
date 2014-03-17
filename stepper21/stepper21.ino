
// Author :BruceTsao 2014.2.27

#include <AccelStepper.h>
#define ClockPin 9
#define CWPin 10
#define MaxSpeed 400
#define AccSpeed 250
#define PulseWidth 800
AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin ,CWPin);
int MoveSteps = 300 ;
void setup()
{ 
stepper1.setMaxSpeed(MaxSpeed);
stepper1.setAcceleration(AccSpeed);
stepper1.setMinPulseWidth(PulseWidth);
stepper1.moveTo(MoveSteps);

}
void loop()
{
// Change direction at the limits
if (stepper1.distanceToGo() == 0)
stepper1.moveTo(-stepper1.currentPosition());
stepper1.run();

}


