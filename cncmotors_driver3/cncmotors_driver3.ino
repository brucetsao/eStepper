/* Stepper motor control program

*/

// constants won't change. Used here to set pin numbers:
const int ledPin =  13;      // the number of the LED pin

const int OFF = 0;
const int ON = 1;

const int XmotorDIR = 5;
const int XmotorPULSE = 2;

const int YmotorDIR = 6;
const int YmotorPULSE = 3;


//half step delay for blank pixels - multiply by 8 (<8ms)
const unsigned int shortdelay = 936;

//half step delay for burnt pixels - multiply by 8 (<18ms)
const unsigned int longdelay = 2125;      

//Scale factor
//Motor driver uses 200 steps per revolution
//Ballscrew pitch is 5mm. 200 steps/5mm, 1 step = 0.025mm
//const int scalefactor = 4;        //full step
const int scalefactor = 8;          //half step


const int LASER = 51;

// Variables that will change:
int ledState = LOW;             // ledState used to set the LED
int counter = 0;
int a = 0;
int initialmode = 0;
int lasermode = 0;

long xpositioncount = 0;
long ypositioncount = 0;


//***********************************************************************************************************
//Initialisation Function
//***********************************************************************************************************

void setup()
{
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(LASER, OUTPUT);
  
  for (a = 2; a <8; a++){
    pinMode(a, OUTPUT);
  }
  
  a = 0;
  
  
  setinitialmode();
  digitalWrite (ledPin, ON);
  delay(2000);
  digitalWrite (ledPin, OFF);
  
  // Turn the Serial Protocol ON
  Serial.begin(9600);
}




//************************************************************************************************************
//Main loop
//************************************************************************************************************

void loop()
{
  byte byteRead;
  
  if (Serial.available()) {
  
    /* read the most recent byte */
    byteRead = Serial.read();
    //You have to subtract '0' from the read Byte to convert from text to a number.
    if (byteRead!='r'){
      byteRead=byteRead-'0';
    }
    
    //Move motors
    if(byteRead==1){
      //Move right FAST
      fastright();         
    }
    if(byteRead==2){
      //Move right SLOW
      slowright();
    }
    if(byteRead==3){
      //Move left FAST
      fastleft();         
    }
    if(byteRead==4){
      //Move left SLOW
      slowleft();         
    }
    if(byteRead==5){
      //Move up FAST
      fastup();
    }
    if(byteRead==6){
      //Move up SLOW
      slowup();
    }
    if(byteRead==7){
      //Move down FAST
      fastdown();
    }
    if(byteRead==8){
      //Move down SLOW
      slowdown();
    }
    if(byteRead==9){
      digitalWrite (LASER, ON);
    }
    if(byteRead==0){
      digitalWrite (LASER, OFF);
    }
    if (byteRead=='r'){
      //reset position
      xresetposition();
      yresetposition();
      delay(1000);
    }
  }
   
}


//************************************************************************************************************
//Set initial mode
//************************************************************************************************************
void setinitialmode()
{
  if (initialmode == 0){
    digitalWrite (XmotorDIR, OFF);
    digitalWrite (XmotorPULSE, OFF);

    digitalWrite (YmotorDIR, OFF);
    digitalWrite (YmotorPULSE, OFF);

    digitalWrite (ledPin, OFF);
    initialmode = 1;
  }
}



//************************************************************************************************************
// Main Motor functions
//************************************************************************************************************

void fastright()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (XmotorDIR, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, OFF);
    delayMicroseconds(shortdelay);
    digitalWrite (ledPin, OFF);
  }
  xpositioncount++;
}

void slowright()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (XmotorDIR, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, OFF);
    delayMicroseconds(longdelay);
    digitalWrite (ledPin, OFF);
  }
  xpositioncount++;
}

void fastleft()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (XmotorDIR, OFF);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, OFF);
    delayMicroseconds(shortdelay);
    digitalWrite (ledPin, OFF);
  }
  xpositioncount--;
}

void slowleft()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (XmotorDIR, OFF);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (XmotorPULSE, OFF);
    delayMicroseconds(longdelay);
    digitalWrite (ledPin, OFF);
  }
  xpositioncount--;
}

void fastup()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (YmotorDIR, ON);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);    
    digitalWrite (YmotorPULSE, OFF);
    delayMicroseconds (shortdelay);
    digitalWrite (ledPin, OFF);
  }
  ypositioncount++;
}

void slowup()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (YmotorDIR, ON);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);    
    digitalWrite (YmotorPULSE, OFF);
    delayMicroseconds (longdelay);
    digitalWrite (ledPin, OFF);
  }
  ypositioncount++;
}

void fastdown()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (YmotorDIR, OFF);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, OFF);
    delayMicroseconds (shortdelay);
    digitalWrite (ledPin, OFF);
  }
  ypositioncount--;
}

void slowdown()
{
  for (a=0; a<scalefactor; a++)
  {
    digitalWrite (YmotorDIR, OFF);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, ON);
    digitalWrite (ledPin, ON);
    delayMicroseconds(15);
    digitalWrite (YmotorPULSE, OFF);
    delayMicroseconds (longdelay);
    digitalWrite (ledPin, OFF);
  }
  ypositioncount--;
}

void xresetposition()
{
  while (xpositioncount!=0){
    if (xpositioncount > 0){
      fastleft();
    }
    if (xpositioncount < 0){
      fastright();
    }
  }
}


void yresetposition()
{
  while (ypositioncount!=0){
    if (ypositioncount > 0){
      fastdown();
    }
    if (ypositioncount < 0){
      fastup();
    }
  }
}



