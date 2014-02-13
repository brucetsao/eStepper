#define leftLedpin 8
#define rightLedpin 9
#define leftSwitchpin 10
#define rightSwitchpin 11
int Motor1direct = 1 ;
void initall()
{
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
   if (checkLeft())
    {
      Serial.println("Hit left ");
    } 
   if (checkRight())
    {
      Serial.println("Hit Right ");
    } 
 delay(200);
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

