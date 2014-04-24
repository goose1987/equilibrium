//hello
#include <Servo.h>
Servo servo1;
int test = 5;
int i=0;
 
int outPWM = 9;
int duty = 0; //duty cycle
int serialRead = 0;  
int throttle = 0;  
void setup() {
  // put your setup code here, to run once:
  pinMode(test, OUTPUT);
  servo1.attach(3);
  digitalWrite(test, HIGH);
  servo1.write(0);
  delay(3000);
  digitalWrite(test, LOW);
  servo1.write(179);

  delay(3000);
  
  digitalWrite(test, HIGH);

    servo1.write(0);
    delay(3000);
  
  
  //digitalWrite(test, LOW);

    servo1.write(179);

    delay(3000);
  
  //digitalWrite(test, LOW);
  delay(10000);
  servo1.write(90);
  
  delay(10000);
  servo1.write(30);
  delay(10000);
  servo1.write(120);
  
}


void loop() {
    //throttle = analogRead(16);
    //throttle = map(throttle, 0, 1023, 0, 179);
   // servo1.write(100);
   
   
  for (int i = 0; i<178; i++) {
    servo1.write(i);

    delay(200);
  }
    delay(3000000);
    //servo1.write(5);
    delay(30);
    //servo1.write(throttle);
    //delay(30);
}


