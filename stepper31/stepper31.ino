
// Author :BruceTsao 2014.3.6

#include <AccelStepper.h>
#define ClockPin 9      // output pin to control Pulse
#define CWPin 10        // Control Motor direction : Clcokwise or CounterClockwise
int MaxSpeed = 600 ;   // max speed of motor
int RunSpeed =  500 ;   //  speed of motor
int  AccSpeed = 250   ; // accelerate for motor
int  PulseWidth = 800  ;  // pulse width for each pulse
int  shiftsteps = 100  ;//　move motor back when init to avoid motor collision
int microsteps = 1;
int revolution = 200;
double  ratio = 2;

AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin ,CWPin);
// THis init Stepper Motor object for use
int MoveSteps = 4000 ;
void setup()
{ 
  Serial.begin(9600);
initcontroller();


}
void loop()
{
// Change direction at the limits
//motor1run(15,true);
//motor1run(15,false);

stepper1.runSpeed();
}

void initcontroller()
{
stepper1.setMaxSpeed(MaxSpeed);    // set Max Speed of Motor
//stepper1.setAcceleration(AccSpeed);  // Set Accelerate speed of motor
//stepper1.setMinPulseWidth(PulseWidth);    //set Pulse width
stepper1.setSpeed(RunSpeed); 
Serial.println(MaxSpeed);
Serial.println(RunSpeed);
stepper1.runSpeed();
}

void initmotor()
{
stepper1.move(shiftsteps);
// this avoid motor to hit 
}
void motor1run(long distance, boolean way)
{
  int tway = 1 ;
  if (way )
  {  
    tway = 1 ;
  }
  else
  {  
    tway = -1 ;
  }
  
    
  long motorsteps= 0 ;
  motorsteps = distance * ratio * revolution * microsteps *tway  ;
  stepper1.move(motorsteps);
}
