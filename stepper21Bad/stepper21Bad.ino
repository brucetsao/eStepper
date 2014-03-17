#include <AccelStepper.h>

//AccelStepper Xaxis(1, 2, 5); // pin 2 = step, pin 5 = direction
//AccelStepper Yaxis(1, 3, 6); // pin 3 = step, pin 6 = direction
//AccelStepper Zaxis(1, 4, 7); // pin 4 = step, pin 7 = direction

AccelStepper Xaxis(1, 9, 10); // pin 3 = step, pin 6 = direction
//AccelStepper Yaxis(1, 4, 7); // pin 4 = step, pin 7 = direction
//AccelStepper Zaxis(1, 5, 9); // pin 5 = step, pin 8 = direction
int pos = 2000 ;

void setup() {
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  Xaxis.setMaxSpeed(650);
//  Yaxis.setMaxSpeed(400);
//  Zaxis.setMaxSpeed(400);
//Xaxis.setMinPulseWidth(1000);
Xaxis.setCurrentPosition(0);
  //Xaxis.setSpeed(400);
//  Yaxis.setSpeed(25);
//  Zaxis.setSpeed(80);
  Serial.println("=====================");
  Serial.println(Xaxis.distanceToGo());
  Serial.println("=====================");

}

void loop() {  
   //Xaxis.runSpeed();
  //   Xaxis.move(-400);  
   // Xaxis.run(); 
    
//   Yaxis.runSpeed();
 //  Zaxis.runSpeed();
//  Serial.println(Xaxis.distanceToGo());
  Serial.println(Xaxis.distanceToGo());
  if (Xaxis.distanceToGo() == 0)
  {
    delay(1500);
    pos = -pos;
    Xaxis.moveTo(pos);
  }
  Xaxis.run();
}


