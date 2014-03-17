
// Author :BruceTsao 2014.2.27

#include <AccelStepper.h>
#define ClockPin 9
#define CWPin 10
// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin ,CWPin);
void setup()
{ 
stepper1.setMaxSpeed(600.0);

//stepper1.setMinPulseWidth(500);
stepper1.setSpeed(500); 
//stepper1.AccelStepper(DIRECTION_CCW );
//stepper1.AccelStepper();
}
void loop()
{
// Change direction at the limits

stepper1.runSpeed();

}


