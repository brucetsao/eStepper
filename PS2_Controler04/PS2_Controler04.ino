#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
int motorSpeed = 0;

void setup(){
 Serial.begin(9600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(10,11,12,13, true, true);   
 //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 Serial.print("connection message is :");
 Serial.println(error);
 
}

void loop(){
  
    ps2x.read_gamepad(false, vibrate);
        motorSpeed = (ps2x.Analog(PSS_RY), DEC);
        Serial.print(motorSpeed);
        
    
    
 
 
 
 delay(50);
     
}

