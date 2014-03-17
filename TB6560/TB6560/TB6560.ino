#define CLK_PIN 9
#define ENABLE_PIN 2
// #define RESET_PIN 11
#define CCW_PIN 10
void setup() {
  // Make all the pins OUTPUT and set them to LOW
  pinMode(CLK_PIN,OUTPUT);
  pinMode(CCW_PIN,OUTPUT);
    pinMode(ENABLE_PIN,OUTPUT);
  // This is the order according to the application notes
  //digitalWrite(RESET_PIN, HIGH);
  digitalWrite(ENABLE_PIN, LOW);
}
int del = 130;
int counter = 0;
int dir = LOW;
void loop() {
  // Send out a clock signal. switch the direction bit every 2000 clocks.
  digitalWrite(CLK_PIN, HIGH);
  delayMicroseconds(del);
  digitalWrite(CLK_PIN, LOW);
  delayMicroseconds(del);
  counter++;
  if (counter == 20000) {
    if (dir == LOW) {
        digitalWrite(ENABLE_PIN, HIGH);
        delay(1000);
        digitalWrite(ENABLE_PIN, LOW);
      dir = HIGH;
    }
    else {
        digitalWrite(ENABLE_PIN, HIGH);
        delay(1000);
        digitalWrite(ENABLE_PIN, LOW);
      dir = LOW;
    }
    digitalWrite(CCW_PIN, dir);
    counter = 0;
  }
}



