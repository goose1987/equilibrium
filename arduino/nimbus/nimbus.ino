#include <Servo.h>
#include <SoftwareSerial.h>

#define M9  9
#define M6  6
#define M5  5
#define M3  3

Servo servo9;
Servo servo6;
Servo servo5;
Servo servo3;

/********************
brushless esc wire 
orange = signal
red = plus
brown is ground
********************/

//const int TX_BT = 10;
//const int RX_BT = 11;

int i=0;
float cmdOut = 0;
 
int m9pwm=0;
int m6pwm=0;
int m5pwm=0;
int m3pwm=0;

int cmd=0; 
String echo="";

//SoftwareSerial btSerial(TX_BT,RX_BT);

//function to arm servo during init
void arm(){
  
  servo9.writeMicroseconds(3000);
  servo6.writeMicroseconds(3000);
  servo5.writeMicroseconds(3000);
  servo3.writeMicroseconds(3000);
  delay(4000);
  //servo1.writeMicroseconds(2500);
  servo9.writeMicroseconds(1000);
  servo6.writeMicroseconds(1000);
  servo5.writeMicroseconds(1000);
  servo3.writeMicroseconds(1000);
  Serial.println("Armed");
  
}

void setup() {
  
  //initialize serial comm through USB
  Serial.begin(9600);
  //Serial.println("USB Connected");
  
  //initialize serial com through bluetooth
  //btSerial.begin(9600);
  
  //servo init
  //attach dedicate pin to servo
  servo9.attach(M9);
  servo6.attach(M6);
  servo5.attach(M5);
  servo3.attach(M3);
  ///////////////////////////////
  arm();//arm servos
  
  
}


void loop() {
  
  //read bluetooth serial buffer
  
  if(Serial.available()>=8){
    m9pwm=0;
    m9pwm=Serial.read();
    m9pwm=(m9pwm<<8)|Serial.read();
    m5pwm=0;
    m5pwm=Serial.read();
    m5pwm=(m5pwm<<8)|Serial.read();
    m3pwm=0;
    m3pwm=Serial.read();
    m3pwm=(m3pwm<<8)|Serial.read();
    m6pwm=0;
    m6pwm = Serial.read();
    m6pwm = (m6pwm<<8)|Serial.read();
    //cmd = btSerial.read();
     
  
    //Serial.println(cmd);
    servo9.writeMicroseconds(m9pwm);
    servo5.writeMicroseconds(m5pwm);
    servo3.writeMicroseconds(m3pwm);  
    servo6.writeMicroseconds(m6pwm);
  
  }
  
  /*
  if (btSerial.available()>=4) {
    
    m5pwm=0;
    m5pwm=btSerial.read();
    m5pwm=(m5pwm<<8)|btSerial.read();
    m6pwm=0;
    m6pwm = btSerial.read();
    m6pwm = (m6pwm<<8)|btSerial.read();
    
    if(m5pwm>1150){
       m5pwm=1150; 
    }
    
    if(m6pwm>1150){
       m6pwm=1150; 
    }
    //servo9.writeMicroseconds(1000);
    //servo3.writeMicroseconds(1000);
    servo5.writeMicroseconds(1090);
    servo6.writeMicroseconds(109);
    Serial.println(m5pwm);
    Serial.println(m6pwm);
    
    
   // if (cmd > 110) {
     // cmd = 110;
   // }
    //servo9.writeMicroseconds(1090+cmd);  
    //servo6.writeMicroseconds(cmd);
    //servo5.writeMicroseconds(cmd);  
    //servo3.writeMicroseconds(1090-cmd);
  }
  */

}
