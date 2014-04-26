#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;

/********************
brushless esc wire 
orange = signal
red = plus
brown is ground
********************/

const int TX_BT = 10;
const int RX_BT = 11;


int test = 5;
int i=0;
int cmdOut = 0;
 
int outPWM = 9;
int duty = 0; //duty cycle
int serialRead = 0;  
int throttle = 0;

float cmd=0; 
String echo="";

SoftwareSerial btSerial(TX_BT,RX_BT);

void setup() {
  
  //initialize serial comm through USB
  Serial.begin(9600);
  Serial.println("USB Connected");
  
  //initialize serial com through bluetooth
  btSerial.begin(9600);
  
  //servo init
  //attach dedicate pin to servo
  servo1.attach(3);
  ///////////////////////////////
  servo1.writeMicroseconds(2500);
  delay(2000);
  //servo1.writeMicroseconds(2500);
  servo1.writeMicroseconds(1000); 
  //delay(3000);
  //digitalWrite(test, LOW);
  //for(int i = 0; i<178; i++) {
  //    servo1.write(i);
  //    delay(50);
  //}
  //servo1.write(0);
  //delay(3000);
 // for(int i = 178; i>1; i--) {
//      servo1.write(i);
 //     delay(50);
 // }
  
}


void loop() {
  
  //read bluetooth serial buffer
  if(btSerial.available()){
    cmd=btSerial.parseFloat();
    //cmd=(int)btSerial.read();
    //Serial.write(cmd);
     
    cmdOut = map(cmd, -90, 90, 1000, 1200);
    Serial.println(cmdOut);  
    servo1.writeMicroseconds(cmdOut); 
  }
/*
    // Read serial input:
  if(Serial.available()){
    cmd=Serial.parseInt();
    servo1.writeMicroseconds(cmd);
   
    Serial.println(cmd); 
  }*/
}
