#define GreenLedpin 8
#define RedLedpin 9
#define Sensorpin 3
void initall()
{
 // init Sensorpin  as output  and input
   pinMode(GreenLedpin,OUTPUT);
   pinMode(RedLedpin,OUTPUT);
   pinMode(Sensorpin,INPUT);
//-----------
   digitalWrite(GreenLedpin,LOW );
   digitalWrite(RedLedpin,LOW );

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

   if (checkSensor())
    {
          Serial.println("Photointerrupter interrupted");
    }
   else
    {
          Serial.println("Photointerrupter not interrupted");
    }
   
  delay(500);
 }

boolean checkSensor()
{
  boolean tmp = false ;
  if (digitalRead(Sensorpin) == HIGH)
  {
     digitalWrite(GreenLedpin,HIGH );
     digitalWrite(RedLedpin,LOW );
     tmp = false  ;
  }
  else
  {
     digitalWrite(GreenLedpin,LOW );
     digitalWrite(RedLedpin,HIGH );
     tmp = true  ;
  }
  return (tmp) ;
}  

