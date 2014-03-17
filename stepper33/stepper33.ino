
// Author :BruceTsao 2014.3.6

#include <AccelStepper.h>
#define ClockPin 9      // output pin to control Pulse
#define CWPin 10        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
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
int rundelay = 100 ;


//AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin ,CWPin);
AccelStepper stepper1(1,ClockPin ,CWPin);
// THis init Stepper Motor object for use
int MoveSteps = 400000 ;
void setup()
{ 
initall();
initcontroller();
//initmotor();
initmotor();
//stepper1.moveTo(200);
//stepper1.runSpeedToPosition();
//stepper1.run();
//motor1run(50000,2);
//motor1steps(50000,2);
//motor1Return();
}
void loop()
{
  /*
stepper1.run();
// Change direction at the limits
//motor1run(15,true);
//motor1run(15,false);
    stepper1.runSpeedToPosition();
        Serial.print("Now pos:(");
        Serial.print(stepper1.distanceToGo());
        Serial.println(")");
  //  stepper1.move(100);
 //   stepper1.runSpeed();
//  stepper1.run();
  //  stepper1.move(-100);
 //   stepper1.runSpeed();
 // stepper1.run();


//stepper1.setSpeed(RunSpeed); 



*/
//stepper1.runSpeed();
//delayMicroseconds(600);

        Serial.print("Move to  Zero pos:(");
        Serial.print(stepper1.distanceToGo());
        Serial.print("/");
        Serial.print(stepper1.speed());
        Serial.println(") in Loop function");
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
stepper1.setAcceleration(AccSpeed);  // Set Accelerate speed of motor
stepper1.setMinPulseWidth(PulseWidth);    //set Pulse width
stepper1.setSpeed(RunSpeed); 
Serial.println(MaxSpeed);
Serial.println(RunSpeed);
//stepper1.runSpeed();
stepper1.setCurrentPosition(0);
}

void initmotor()
{
  if (!checkLeft())
  {
//    stepper1.move(-10) ;
    Serial.println("not in Zero pos");
   // motor1run(RunSpeed,2) ;
  //   stepper1.runSpeed();
  //   stepper1.move(5000);
      while (!checkLeft())
      {
        // stepper1.move(-10) ;
        //  stepper1.move(100);
     //     stepper1.setSpeed(RunSpeed);
           stepper1.runSpeed();
         // delayMicroseconds(rundelay);
        Serial.print("Move to  Zero pos:(");
        Serial.print(stepper1.distanceToGo());
        Serial.print("/");
        Serial.print(stepper1.speed());
        Serial.println(")");
        stepper1.runSpeed();
     }
    
  }
    stepper1.stop() ;
        Serial.println("To Zero pos and stop");
  stepper1.setCurrentPosition(0);
        Serial.print("Now POS is :");
        Serial.println(stepper1.distanceToGo());
//stepper1.move(shiftsteps);
// this avoid motor to hit 

}
void motor1steps(long motorspd, int dirw)
{
      if (dirw == 1)
      {
        Serial.println("Set Dir to one");
       // stepper1.setSpeed(RunSpeed) ;
          stepper1.move(motorspd); 
      }
    else
    {
        Serial.println("Set Dir to Two");
       // stepper1.setSpeed(-RunSpeed); 
          stepper1.move(-motorspd); 
    }
stepper1.setSpeed(RunSpeed); 
//  stepper1.run();
    
 //motorsteps = distance * ratio * revolution * microsteps *tway  ;
 //while (stepper1.distanceToGo() !=0)
// {
        Serial.print("Now Target POS is :");
        Serial.println(stepper1.distanceToGo());
      stepper1.runSpeedToPosition();
//       delayMicroseconds(rundelay);
stepper1.run();
// }
}

void motor1Return()
{
      stepper1.moveTo(0); 
   stepper1.runSpeedToPosition();
   
 //motorsteps = distance * ratio * revolution * microsteps *tway  ;
/*
 while (stepper1.distanceToGo() !=0)
 {
      stepper1.run();
       delayMicroseconds(rundelay);
 }
 */
}

void motor1run(long motorspd, int dirway)
{
      if (dirway == 1)
      {
       // stepper1.setSpeed(RunSpeed) ;
          stepper1.setSpeed(motorspd); 
      }
    else
    {
       // stepper1.setSpeed(-RunSpeed); 
           stepper1.setSpeed(-motorspd); 
    }


 //motorsteps = distance * ratio * revolution * microsteps *tway  ;

}


boolean checkLeft()
{
  // delayMicroseconds(150);
  boolean tmp = false ;
  if (digitalRead(leftSwitchpin) == HIGH)
  {
     tmp = true  ;
     Serial.println("Left  Swithc High");
  }
  else
  {
     tmp = false  ;
     Serial.println("Left  Swithc Low");
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

void SHM()
{
  
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
}

