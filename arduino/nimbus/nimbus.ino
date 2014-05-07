#include <Servo.h>
#include <SoftwareSerial.h>

#define M1  9
#define M2  6
#define M3  5
#define M4  3

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

/********************
brushless esc wire 
orange = signal
red = plus
brown is ground
********************/

const int TX_BT = 1;
const int RX_BT = 0;

int i=0;
float cmdOut = 0;
 
int outPWM = 9;
int duty = 0; //duty cycle
int serialRead = 0;  
int throttle = 0;

float cmd=0; 
String echo="";

SoftwareSerial btSerial(TX_BT,RX_BT);

//function to arm servo during init
void arm(){
  
  servo1.writeMicroseconds(4000);
  servo2.writeMicroseconds(4000);
  servo3.writeMicroseconds(4000);
  servo4.writeMicroseconds(4000);
  delay(4000);
  //servo1.writeMicroseconds(2500);
  servo1.writeMicroseconds(1000);
  servo2.writeMicroseconds(1000);
  servo3.writeMicroseconds(1000);
  servo4.writeMicroseconds(1000);
  Serial.println("Armed");
  
}

void setup() {
  
  //initialize serial comm through USB
  Serial.begin(9600);
  Serial.println("USB Connected");
  
  //initialize serial com through bluetooth
  btSerial.begin(9600);
  
  //servo init
  //attach dedicate pin to servo
  servo1.attach(M1);
  servo2.attach(M2);
  servo3.attach(M3);
  servo4.attach(M4);
  ///////////////////////////////
  arm();//arm servos
  
  
}


void loop() {
  
  //read bluetooth serial buffer
  /*
  if(btSerial.available()){
    cmd=btSerial.parseFloat();
    //cmd = btSerial.read();
     
    cmdOut = map(cmd, -90, 90, 900, 1100);
    Serial.println(cmd);  
    servo4.writeMicroseconds(cmdOut);  
    servo3.writeMicroseconds(cmdOut);
  }*/
  if (Serial.available()) {
    cmd = Serial.parseFloat();
    Serial.println(cmd);
    Serial.println("in loop");
    servo1.writeMicroseconds(cmd);  
    servo2.writeMicroseconds(cmd);
    servo3.writeMicroseconds(cmd);  
    servo4.writeMicroseconds(cmd);
  }

}

