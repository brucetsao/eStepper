#include <EasyStepper.h>
 
// define the pins
#define STEP_PIN 34
#define DIR_PIN 35
#define EN_PIN 36
 
// define the inverted
#define DIR_PIN_INVERTED true
#define EN_PIN_INVERTED true
 
// the EasyStepper instance
EasyStepper stepper1(STEP_PIN, DIR_PIN, EN_PIN, DIR_PIN_INVERTED, EN_PIN_INVERTED);
 
// the stepps to rotate
int stepps = 200;
 
// run times
int times = 0;
 
void setup()
{
  Serial.begin(9600);
  stepper1.debugMode(false);
  stepper1.startup();
  stepper1.rotate(400.0, stepps);
}
 
void loop()
{
  if (times < 10)
  {
    stepper1.run();
    if (stepper1.isDone())
    {
      // go back
      stepps *= -1;
      stepper1.rotate(400.0, stepps);
      times++;
    }
  }
}
