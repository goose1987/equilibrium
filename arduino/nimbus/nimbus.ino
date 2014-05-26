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

const int TX_BT = 10;
const int RX_BT = 11;

int i=0;
float cmdOut = 0;
 
int m9pwm=0;
int m6pwm=0;
int m5pwm=0;
int m3pwm=0;

int cmd=0; 
String echo="";

SoftwareSerial btSerial(TX_BT,RX_BT);

//function to arm servo during init
void arm(){
  
  servo9.writeMicroseconds(3000);
  servo6.writeMicroseconds(3000);
  servo5.writeMicroseconds(3000);
  servo3.writeMicroseconds(3000);
 /*
  servo9.write(150);
  servo6.write(150);
  servo5.write(150);
  servo3.write(150);
  */
  //byte serialBytes[8];
  
  delay(4000);
  //servo1.writeMicroseconds(2500);
  servo9.writeMicroseconds(1000);
  servo6.writeMicroseconds(1000);
  servo5.writeMicroseconds(1000);
  servo3.writeMicroseconds(1000);
 /* 
  servo9.write(10);
  servo6.write(10);
  servo5.write(10);
  servo3.write(10);
  */
  Serial.println("Armed");
  
}

void setup() {
  
  //initialize serial comm through USB
  Serial.begin(38400); //9600
  Serial.println("USB Connected");
  
  //initialize serial com through bluetooth
  btSerial.begin(38400);
  
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
  
  while(Serial.available()>=8){

    //m9pwm=0;
    m9pwm=(Serial.read()<<8)|Serial.read();
    
    //m5pwm=0;

    m5pwm=(Serial.read()<<8)|Serial.read();
    //m3pwm=0;

    m3pwm=(Serial.read()<<8)|Serial.read();
    //m6pwm=0;


    m6pwm = (Serial.read()<<8)|Serial.read();

   // Serial.readBytes(serialBytes, 8);
    //cmd = btSerial.read();
/*
    m9pwm=btSerial.read();
    m3pwm=btSerial.read();
    m5pwm=btSerial.read();
    m6pwm=btSerial.read();
*/
    //servo9.write(m3pwm);
    //servo5.write(m6pwm);
    //servo3.write(m9pwm);  
    //servo6.write(m5pwm);
   // Serial.println((int)((int)serialBytes[0]<<8|(int)serialBytes[1]));
    //Serial.println(m5pwm);
    //Serial.println(m9pwm);
    //Serial.println(m3pwm);
    //Serial.println();
    servo9.writeMicroseconds(m3pwm);
    servo5.writeMicroseconds(m6pwm);
    servo3.writeMicroseconds(m9pwm);  
    servo6.writeMicroseconds(m5pwm);
  
  
  
  }

}
