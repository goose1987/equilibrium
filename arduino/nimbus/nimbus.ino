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

int i=0;
float cmdOut = 0;
 
int m9pwm=0;
int m6pwm=0;
int m5pwm=0;
int m3pwm=0;

int cmd=0; 

//function to arm servo during init
void arm(){
  
  servo9.writeMicroseconds(2500);
  servo6.writeMicroseconds(2500);
  servo5.writeMicroseconds(2500);
  servo3.writeMicroseconds(2500);
  delay(2000);
  //servo1.writeMicroseconds(2500);
  servo9.writeMicroseconds(1000);
  servo6.writeMicroseconds(1000);
  servo5.writeMicroseconds(1000);
  servo3.writeMicroseconds(1000);
  
  
}



void setup() {
  
  //initialize serial comm through bluetooth 1 0
  Serial.begin(19200); //38400
  

  
  //servo init
  //attach dedicate pin to servo
  servo9.attach(M9,1000,2000);
  servo6.attach(M6,1000,2000);
  servo5.attach(M5,1000,2000);
  servo3.attach(M3,1000,2000);
  ///////////////////////////////
  arm();
  
}


void loop() {
  
  //read bluetooth serial buffer
  
  if(Serial.available()>=4){
    
    Serial.read();
    servo3.writeMicroseconds(0); 
    servo5.writeMicroseconds(1100+Serial.read());
    Serial.read();
    servo9.writeMicroseconds(0);    
    servo6.writeMicroseconds(1100+Serial.read());
  
  
  }

}
