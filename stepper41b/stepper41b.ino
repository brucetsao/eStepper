
// Author :BruceTsao 2014.3.6

#include <Stepper.h>
#define ClockPin1 9      // output pin to control Pulse
#define CWPin1 10        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define ClockPin2 11      // output pin to control Pulse
#define CWPin2 12        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define leftSwitchpin 4
#define rightSwitchpin 3

int RunSpeed =  300 ;   //  speed of motor
int  PulseWidth = 600  ;  // pulse width for each pulse
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
motor2steps(1600,1);
calmotor2();

//initmotor();
//stepper1.moveTo(200);
//stepper1.runSpeedToPosition();
//stepper1.run();
//motor1run(50000,2);
//motor1steps(50000,2);
//motor1Return();

}
void loop()
{
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

void calmotor1()
{
  if (!checkLeft())
  {

    Serial.println("Now Calibrate first step");
    motor1steps(100,1) ;
      delay(2000);
      motor2steps(1600,1) ;
      delay(1000);
      
    Serial.println("Now Calibrate second step");
    motor1steps(200,1) ;
      delay(2000);
      motor2steps(1600,1) ;
      delay(1000);
    Serial.println("Now Calibrate third step");
    motor1steps(200,2) ;
      delay(2000);
      motor2steps(1600,1) ;
      delay(1000);
    Serial.println("Now Calibrate fourth step");
    motor1steps(100,2) ;
      delay(2000);
     motor2steps(1600,1) ;
      delay(1000);

  }

  
// this avoid motor to hit 

}

void calmotor2()
{
  if (!checkLeft())
  {
      motor2steps(1600,1) ;
    Serial.println("Now Calibrate2 first step");
    motor1steps(100,1) ;
    motor2steps(400,1) ;
   motor1steps(100,2) ;
          delay(2000);
      
    Serial.println("Now Calibrate2 second step");
    motor1steps(100,2) ;
    motor2steps(600,1) ;
   motor1steps(100,1) ;
          delay(2000);
    Serial.println("Now Calibrate2 third step");
    motor1steps(100,1) ;
    motor2steps(1000,1) ;
   motor1steps(100,2) ;
          delay(2000);
    Serial.println("Now Calibrate2 fourth step");
    motor1steps(100,2) ;
    motor2steps(1600,1) ;
   motor1steps(100,1) ;
          delay(2000);

  }

  
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
