#include "EasyStepper.h"
 
EasyStepper::EasyStepper(byte stepPin, byte directionPin, byte enablePin, bool directionPinsInverted, bool enablePinsInverted)
{
        // save the parameters
        this->stepPin = stepPin;
        this->directionPin = directionPin;
        this->enablePin = enablePin;
        this->directionPinsInverted = directionPinsInverted;
        this->enablePinsInverted = enablePinsInverted;
}
 
void EasyStepper::startup()
{
        // set the pin mode
        pinMode(this->stepPin, OUTPUT);
        pinMode(this->directionPin, OUTPUT);
        pinMode(this->enablePin, OUTPUT);
        // enable the stepper
        digitalWrite(enablePin, HIGH ^ this->enablePinsInverted);
        // initialize the done to true
        this->done = true;
}
 
void EasyStepper::shutdown()
{
        // disable the stepper
        digitalWrite(enablePin, LOW ^ this->enablePinsInverted);
}
 
void EasyStepper::debugMode(boolean enabled)
{
        this->debugModeFlag = enabled;
}
 
void EasyStepper::rotate(float speed, int steps)
{
        // ignore the zero value
        if (speed != 0 && steps != 0)
        {
                if (steps > 0)
                {
                        // CW
                        digitalWrite(directionPin, HIGH ^ this->directionPinsInverted);
                        if (this->debugModeFlag)
                        {
                                Serial.println("CW");
                        }
                }
                else if (steps < 0)
                {
                        // CCW
                        digitalWrite(directionPin, LOW ^ this->directionPinsInverted);
                        if (this->debugModeFlag)
                        {
                                Serial.println("CCW");
                        }
                }
                this->done = false;
                // the steps to go
                this->stepsToGo = abs(steps);
                // the steps gone
                this->stepsGone = 0;
                // change the speed to stepTime, micro seconds per step
                this->stepTime = 1000.0 * 1000.0 / abs(speed);
                // current timestamp
                unsigned long time = micros();
                this->nextTimestamp = time + this->stepTime;
                if (this->debugModeFlag)
                {
                        Serial.print("stepsToGo=");
                        Serial.print(this->stepsToGo);
                        Serial.print(", stepTime=");
                        Serial.print(this->stepTime);
                        Serial.print(", currentTimestamp=");
                        Serial.print(time);
                        Serial.print(", nextTimestamp=");
                        Serial.println(this->nextTimestamp);
                }
                // call the step method to rotate the motor
                this->step();
        }
}
 
void EasyStepper::stop()
{
        this->stepsToGo = 0;
        this->done = true;
}
 
void EasyStepper::run()
{
        // the current timestamp
        unsigned long time = micros();
        if (time >= this->nextTimestamp && !this->done)
        {
                this->step();
        }
        if (this->debugModeFlag)
        {
                Serial.print("currentTimestamp=");
                Serial.println(time);
        }
}
 
void EasyStepper::step()
{
        // are there some steps to rotate?
        if (this->stepsToGo > this->stepsGone)
        {
                // HIGH value
                digitalWrite(stepPin, HIGH);
                // delay
                delayMicroseconds(2);
                // LOW value
                digitalWrite(stepPin, LOW);
                // increase the stepsGone
                this->stepsGone++;
                // current timestamp
                unsigned long time = micros();
                this->nextTimestamp = time + this->stepTime;
                if (this->debugModeFlag)
                {
                        Serial.print("stepsGone=");
                        Serial.print(stepsGone);
                        Serial.print(", currentTimestamp=");
                        Serial.print(time);
                        Serial.print(", nextTimestamp=");
                        Serial.println(this->nextTimestamp);
                }
        }
        else
        {
                this->done = true;
        }
}
 
boolean EasyStepper::isDone()
{
        return this->done;
}