
// Author :BruceTsao 2014.3.6

#include <Stepper.h>
#define ClockPin1 9      // output pin to control Pulse
#define CWPin1 10        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define ClockPin2 11      // output pin to control Pulse
#define CWPin2 12        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define leftSwitchpin 4
#define rightSwitchpin 3

int MaxSpeed = 600 ;   // max speed of motor
int RunSpeed =  300 ;   //  speed of motor
int  AccSpeed = 250   ; // accelerate for motor
int  PulseWidth = 600  ;  // pulse width for each pulse
int  shiftsteps = 100  ;//　move motor back when init to avoid motor collision
int microsteps = 2;
int revolution = 200;
double  ratio = 2;
int Motor1direction = 1 ;
int rundelay = 200 ;


Stepper stepper1(revolution * microsteps  ,ClockPin1 ,CWPin1);
Stepper stepper2(revolution * microsteps  ,ClockPin2 ,CWPin2);
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
  motor2steps(400,1);
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
stepper1.setSpeed(RunSpeed);    // set Max Speed of Motor


// motor2 init
stepper2.setSpeed(RunSpeed); 

Serial.println(RunSpeed);
Serial.println(RunSpeed);
//stepper1.runSpeed();

}

void initmotor()
{
  if (!checkLeft())
  {
//    stepper1.move(-10) ;
    Serial.println("not in Zero pos");
    motor1steps(20,2) ;
      while (!checkLeft())
      {
      motor1steps(20,2) ;
     }
    
  }
        Serial.println("To Zero pos and stop");
  
// this avoid motor to hit 

}
void motor1steps(int motorspd, int dirw)
{
  int counter = 0 ;
    if (dirw == 1) {
          digitalWrite(CWPin1, HIGH);
    }
    else {
          digitalWrite(CWPin1, LOW);
    }

for(counter = 0 ; counter <motorspd; counter ++)
{
    digitalWrite(ClockPin1, HIGH);
  delayMicroseconds(PulseWidth);
  digitalWrite(ClockPin1, LOW);
  delayMicroseconds(PulseWidth);
}
}

void motor2steps(int motorspd, int dirw)
{
  int counter = 0 ;
    if (dirw == 1) {
          digitalWrite(CWPin2, HIGH);
    }
    else {
          digitalWrite(CWPin2, LOW);
    }

for(counter = 0 ; counter <motorspd; counter ++)
{
    digitalWrite(ClockPin2, HIGH);
  delayMicroseconds(PulseWidth);
  digitalWrite(ClockPin2, LOW);
  delayMicroseconds(PulseWidth);
}
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

int calculatePulse(int mm, double ratios )
{
  
  return (int)((double)mm * ratios * revolution * microsteps) ;
  
}
