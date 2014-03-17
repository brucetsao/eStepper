#ifndef EasyStepper_h
#define EasyStepper_h
 
#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif
 
// These defs cause trouble on some versions of Arduino
#undef round
 
/**
* author [email]shangcm@gmail.com[/email]
*/
class EasyStepper
{
        public:
 
                /**
                * to create the EasyStepper
                * parameters:
                * stepPin the step pin
                * directionPin the direction pin
                * enablePin the enable pin
                * directionPinsInverted if the value is true then invert HIGH/LOW value for direction pin
                * enablePinsInverted if the value is true then invert HIGH/LOW value for enable pin
                */
                EasyStepper(byte stepPin, byte directionPin, byte enablePin, bool directionPinsInverted, bool enablePinsInverted);
 
                /**
                * to startup the EasyStepper
                */
                void startup();
 
                /**
                * to shutdown the EasyStepper, will release the enable pin to save power
                */
                void shutdown();
 
                /**
                * to rotate steps from current position with speed
                * speed the speed for rotation, the unit is steps per second
                */
                void rotate(float speed, int steps);
 
                /**
                * to stop the stepper, the motor will stay at current position
                */
                void stop();
 
    /**
    * run, you must call this as frequently as possible, but at least once per minimum step interval,
    * preferably in your main loop.
    */
    void run();
 
    /**
    * if return true means the action is done
    */
    boolean isDone();
 
    /**
    * enable the debug mode?
    */
    void debugMode(boolean enabled);
 
        protected:
 
                //
 
        private:
 
                boolean debugModeFlag;
 
                byte stepPin;
                byte directionPin;
                byte enablePin;
 
                bool directionPinsInverted;
                bool enablePinsInverted;
 
                int stepsToGo;
                int stepsGone;
 
                float stepTime;
                unsigned long nextTimestamp;
 
                boolean done;
 
                void step();
 
};
 
#endif