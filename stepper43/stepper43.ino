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
  if ((data & 0x0001)==1)  // the button data
  { 
      Serial.print(data ); 
      Serial.print("/"); 
      Serial.println("psxLeft"); 
  }
    if (data & 0x0002)  // the
  { 
      Serial.print(data ); 
      Serial.print("/"); 
      Serial.println("psxDown"); 
  }
  if (data & 0x0004)  // the
   { 
      Serial.print(data ); 
      Serial.print("/"); 
       Serial.println("psxRight"); 
   }
      if (data & 0x0008)  // the
   { 
      Serial.print(data ); 
      Serial.print("/"); 
     Serial.println("psxUp"); 
   }
  
//  Serial.println(data,HEX);                                   // Display the returned numeric value
   delay(100);
}
