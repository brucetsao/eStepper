
// Author :BruceTsao 2014.3.6

#include <AccelStepper.h>
#define ClockPin1 9      // output pin to control Pulse
#define CWPin1 10        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define ClockPin2 11      // output pin to control Pulse
#define CWPin2 12        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
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
int rundelay = 200 ;


AccelStepper stepper1(AccelStepper::DRIVER ,ClockPin1 ,CWPin1);
AccelStepper stepper2(AccelStepper::DRIVER ,ClockPin2 ,CWPin2);
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
  Serial.println("run motor2"); 
  motor2run(400,1);
  stepper2.runSpeed();
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
        Serial.print("Move to  Zero pos in loop function :(");
        Serial.print(stepper1.distanceToGo());
        Serial.print("/");
        Serial.print(stepper1.speed());
        Serial.print("@@");
        Serial.print(stepper2.distanceToGo());
        Serial.print("/");
        Serial.print(stepper2.speed());
        Serial.println(")");


}
void initall()
{
  pinMode(ClockPin1,OUTPUT) ;
  pinMode(CWPin1,OUTPUT) ;
  pinMode(ClockPin2,OUTPUT) ;
  pinMode(CWPin2,OUTPUT) ;

   // init motor direction Led output 
   pinMode(leftSwitchpin,INPUT);
   pinMode(rightSwitchpin,INPUT);

  Serial.begin(9600);
  
}
void initcontroller()
{
// motor1 init
stepper1.setMaxSpeed(MaxSpeed);    // set Max Speed of Motor
stepper1.setAcceleration(AccSpeed);  // Set Accelerate speed of motor
stepper1.setMinPulseWidth(PulseWidth);    //set Pulse width
stepper1.setSpeed(RunSpeed); 
stepper1.setCurrentPosition(0);

// motor2 init
stepper2.setMaxSpeed(MaxSpeed);    // set Max Speed of Motor
stepper2.setAcceleration(AccSpeed);  // Set Accelerate speed of motor
stepper2.setMinPulseWidth(PulseWidth);    //set Pulse width
stepper2.setSpeed(RunSpeed); 
stepper2.setCurrentPosition(0);


Serial.println(MaxSpeed);
Serial.println(RunSpeed);
//stepper1.runSpeed();

}

void initmotor()
{
  if (!checkLeft())
  {
//    stepper1.move(-10) ;
    Serial.println("not in Zero pos");
    motor1run(RunSpeed,2) ;
      while (!checkLeft())
      {
        // stepper1.move(-10) ;
        //  stepper1.move(100);
     //     motor1run(RunSpeed,2) ;
           stepper1.runSpeed();
         // delayMicroseconds(rundelay);
        Serial.print("Move to  Zero pos:(");
        Serial.print(stepper1.distanceToGo());
        Serial.print("/");
        Serial.print(stepper1.speed());
        Serial.print("@@");
        Serial.print(stepper2.distanceToGo());
        Serial.print("/");
        Serial.print(stepper2.speed());
        Serial.println(")");
        stepper1.runSpeed();
     }
    
  }
    stepper1.stop() ;
        Serial.println("To Zero pos and stop");
  stepper1.setCurrentPosition(0);
        Serial.print("Now POS is :(");
        Serial.print(stepper1.distanceToGo());
        Serial.print("/");
        Serial.print(stepper1.speed());
        Serial.print("@@");
        Serial.print(stepper2.distanceToGo());
        Serial.print("/");
        Serial.print(stepper2.speed());
        Serial.println(")");
            stepper1.stop() ;
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

void motor2steps(long motorspd, int dirw)
{
      if (dirw == 1)
      {
        Serial.println("Set Dir2 to one");
       // stepper2.setSpeed(RunSpeed) ;
          stepper2.move(motorspd); 
      }
    else
    {
        Serial.println("Set Dir2 to Two");
       // stepper2.setSpeed(-RunSpeed); 
          stepper2.move(-motorspd); 
    }
stepper2.setSpeed(RunSpeed); 
//  stepper2.run();
    
 //motorsteps = distance * ratio * revolution * microsteps *tway  ;
 //while (stepper2.distanceToGo() !=0)
// {
        Serial.print("Now Target POS2 is :");
        Serial.println(stepper2.distanceToGo());
      stepper2.runSpeedToPosition();
//       delayMicroseconds(rundelay);
stepper2.run();
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

void motor2run(long motorspd, int dirway)
{
      if (dirway == 1)
      {
       // stepper2.setSpeed(RunSpeed) ;
          stepper2.setSpeed(motorspd); 
      }
    else
    {
       // stepper2.setSpeed(-RunSpeed); 
           stepper2.setSpeed(-motorspd); 
    }


 //motorsteps = distance * ratio * revolution * microsteps *tway  ;

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

