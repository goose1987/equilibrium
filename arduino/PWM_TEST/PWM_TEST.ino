//hello
#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;
int test = 5;
int i=0;
 
int outPWM = 9;
int duty = 0; //duty cycle
int serialRead = 0;  
int throttle = 0;

int cmd=0; 
String echo="";

void setup() {
  Serial.begin(9600);
  Serial.println("USB Connected");
  // put your setup code here, to run once:
  pinMode(test, OUTPUT);
  servo1.attach(3);
  digitalWrite(test, HIGH);
  
}


void loop() {
    // Read serial input:
  if(Serial.available()){
   cmd=Serial.parseInt();
   
    Serial.println(cmd); 
  }
}


