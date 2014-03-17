#include <Stepper.h>

int Pin0 = 46; 
int Pin1 = 48; 
int Pin2 = 50; 
int Pin3 = 52; 

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution for your motor
// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, Pin0,Pin1,Pin2,Pin3);    
int val;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(300);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  val=analogRead(0);
  val=map(val,0,1023,0,99);
  Serial.println(val);
  // step one revolution  in two direction:
  if(val>50){
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);//
    delay(500);
  }
  else{
    // step one revolution in the other direction:
    Serial.println("counterclockwise");
    myStepper.step(stepsPerRevolution * (-1));
    delay(500); 
  }
}

