#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 30
#define cmndPin 32
#define attPin 34
#define clockPin 36

Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response

void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
//                 11            9    10       8                        // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
  Serial.begin(9600);
}

void loop()
{
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
                                                          // the button data
  Serial.println(data,HEX);                                   // Display the returned numeric value
   delay(50);
}
