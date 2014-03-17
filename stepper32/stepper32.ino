
// Author :BruceTsao 2014.3.6

#include <AccelStepper.h>
#define ClockPin 9      // output pin to control Pulse
#define CWPin 10        // Control Motor direction : Clcokwise or CounterClockwise
#define leftSwitchpin 4
#define rightSwitchpin 3

int MaxSpeed = 600 ;   // max speed of motor
int RunSpeed =  500 ;   //  speed of motor
int  AccSpeed = 250   ; // accelerate for motor
int  PulseWidth = 800  ;  // pulse width for each pulse
int  shiftsteps = 100  ;//　move motor back when init to avoid motor collision
int microsteps = 1;
int revolution = 200;
double  ratio = 2;
int Motor1direction = 1 ;



AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin ,CWPin);
// THis init Stepper Motor object for use
int MoveSteps = 400000 ;
void setup()
{ 
initall();
initcontroller();


}
void loop()
{
// Change direction at the limits
//motor1run(15,true);
//motor1run(15,false);


if (Motor1direction == 1)
stepper1.setSpeed(RunSpeed) ;
else
stepper1.setSpeed(-RunSpeed); 

//stepper1.setSpeed(RunSpeed); 

   if (checkLeft())
    {
      if (Motor1direction == 2)
      { 
          Serial.println("Hit left ");
          Serial.print("direction =  ");
          Serial.println(Motor1direction);
          Motor1direction = 1;
      }
    } 
   if (checkRight())
    {
      if (Motor1direction == 1)
      { 
          Serial.println("Hit Right ");
         Serial.print("direction =  ");
          Serial.println(Motor1direction);
          Motor1direction = 2;
      }
    } 

stepper1.runSpeed();
//delayMicroseconds(600);
}
void initall()
{
  pinMode(ClockPin,OUTPUT) ;
  pinMode(CWPin,OUTPUT) ;

   // init motor direction Led output 
   pinMode(leftSwitchpin,INPUT);
   pinMode(rightSwitchpin,INPUT);

  Serial.begin(9600);
  
}
void initcontroller()
{
stepper1.setMaxSpeed(MaxSpeed);    // set Max Speed of Motor
//stepper1.setAcceleration(AccSpeed);  // Set Accelerate speed of motor
//stepper1.setMinPulseWidth(PulseWidth);    //set Pulse width
stepper1.setSpeed(RunSpeed); 
Serial.println(MaxSpeed);
Serial.println(RunSpeed);
//stepper1.runSpeed();
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

boolean checkLeft()
{
  boolean tmp = false ;
  if (digitalRead(leftSwitchpin) == HIGH)
  {
     tmp = true  ;
  }
  else
  {
     tmp = false  ;
  }
  return (tmp) ;
}  
boolean checkRight()
{
  boolean tmp = false ;
  if (digitalRead(rightSwitchpin) == HIGH)
  {
     tmp = true  ;
  }
  else
  {
     tmp = false  ;
  }
  return (tmp) ;
}  

