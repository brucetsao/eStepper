
// Author :BruceTsao 2014.3.6

#include <Stepper.h>
#include <Psx.h>      

#define ClockPin1 9      // output pin to control Pulse
#define CWPin1 10        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define ClockPin2 11      // output pin to control Pulse
#define CWPin2 12        // Control Motor direcsetSpeedtion : Clcokwise or CounterClockwise
#define leftSwitchpin 4
#define rightSwitchpin 3
//----------------------
#define dataPin 30
#define cmndPin 32
#define attPin 34
#define clockPin 36
//-------------------------

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
Psx Psx;       

int MoveSteps = 400000 ;
unsigned int data = 0;  

double motor1ratio = 0.001 ;
double motor2ratio = 0.025 ;

void setup()
{ 
  
initall();
initcontroller();


}
void loop()
{
  
    data = Psx.read();    
    if ((data & 0x0001)==1)  // the button data
  { 
    if (!checkLeft())
    {
      Serial.print(data ); 
      Serial.print("/"); 
      Serial.println("psxLeft"); 
      motor1steps(calculatePulse(3,motor1ratio),1) ;
    }
    else
    {
            Serial.println("hit Left"); 
    }
  }
    if (data & 0x0002)  // the
  { 
      Serial.print(data ); 
      Serial.print("/"); 
      Serial.println("psxDown"); 
     motor2steps(calculatePulse(3,motor2ratio),1) ;
  }
  if (data & 0x0004)  // the
   { 
  if (!checkRight())
    {
      Serial.print(data ); 
      Serial.print("/"); 
       Serial.println("psxRight"); 
        motor1steps(calculatePulse(3,motor1ratio),2);
    }
    else
    {
            Serial.println("hit Right"); 
    }
    
   }
      if (data & 0x0008)  // the
   { 
      Serial.print(data ); 
      Serial.print("/"); 
     Serial.println("psxUp"); 
      motor2steps(calculatePulse(3,motor2ratio),2) ;
   }
  
//  Serial.println(data,HEX);                                   // Display the returned numeric value
   delay(50);
    
    
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
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used

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
