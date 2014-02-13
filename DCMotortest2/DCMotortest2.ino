#define motor1a 7 
#define motor1b 6 
#define motor2a 5 
#define motor2b 4 
#define leftLedpin 8
#define rightLedpin 9
#define leftSwitchpin 10
#define rightSwitchpin 11
int Motor1direction = 1 ;
void initall()
{
 // init motor pin as output 
   pinMode(motor1a,OUTPUT);
   pinMode(motor1b,OUTPUT);
   pinMode(motor2a,OUTPUT);
   pinMode(motor2b,OUTPUT);
 // init motor direction Led output 
   pinMode(leftLedpin,OUTPUT);
   pinMode(rightLedpin,OUTPUT);
 // init motor direction Led output 
   pinMode(leftSwitchpin,INPUT);
   pinMode(rightSwitchpin,INPUT);
//-----------
   digitalWrite(leftLedpin,LOW );
   digitalWrite(rightLedpin,LOW );

}
 void setup()
 {
  initall();
   //init serial for debug
Serial.begin(9600);
Serial.println("program start here ");
 }

 void loop()
 {
  // Serial.println("Motor1 Forward ");
   if (checkLeft())
    {
      if (Motor1direction == 2)
      { 
          Serial.println("Hit left ");
          Motor1direction = 1;
      }
    } 
   if (checkRight())
    {
      if (Motor1direction == 1)
      { 
          Serial.println("Hit Right ");
          Motor1direction = 2;
      }
    } 
    
    if (Motor1direction == 1)
    {
       Motor2Forward();
    }
    else
    {
       Motor2Backward();
    }
    Motor1Forward();
  delay(100);
 }

 void Motor1Forward()
 {
   digitalWrite(motor1a,HIGH);
   digitalWrite(motor1b,LOW);
 }
 void Motor1Backward()
 {
   digitalWrite(motor1a,LOW );
   digitalWrite(motor1b,HIGH);
 }
 void Motor2Forward()
 {
   digitalWrite(motor2a,HIGH);
   digitalWrite(motor2b,LOW);
 }
 void Motor2Backward()
 {
   digitalWrite(motor2a,LOW );
   digitalWrite(motor2b,HIGH);
 }

boolean checkLeft()
{
  boolean tmp = false ;
  if (digitalRead(leftSwitchpin) == HIGH)
  {
     digitalWrite(leftLedpin,HIGH );
     tmp = true  ;
  }
  else
  {
     digitalWrite(leftLedpin,LOW );
     tmp = false  ;
  }
  return (tmp) ;
}  
boolean checkRight()
{
  boolean tmp = false ;
  if (digitalRead(rightSwitchpin) == HIGH)
  {
     digitalWrite(rightLedpin,HIGH );
     tmp = true  ;
  }
  else
  {
     digitalWrite(rightLedpin,LOW );
     tmp = false  ;
  }
  return (tmp) ;
}  

