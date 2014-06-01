#include <PID_v1.h>

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

double rollSP,roll,rollcomp;

double pitchSP,pitch,pitchcomp;

double motor5,motor6;

//PID rollPID(&roll,&rollcomp,&rollSP,2,0.1,0.5, DIRECT);

PID pitchPID(&pitch,&motor5,&pitchSP,1,0.05,0.05,REVERSE);

PID pitchPID2(&pitch,&motor6,&pitchSP,1,0.05,0.05,DIRECT);

int throttle;

void arm(){
  
  servo5.writeMicroseconds(2500);
  servo6.writeMicroseconds(2500);
  servo9.writeMicroseconds(2500);
  servo3.writeMicroseconds(2500);
  delay(2000);
  //servo1.writeMicroseconds(2500);
  servo5.writeMicroseconds(1000);
  servo6.writeMicroseconds(1000);
  servo9.writeMicroseconds(1000);
  servo3.writeMicroseconds(1000);
  
  
}

void setup() {
  
  //initialize serial comm through bluetooth 1 0
  Serial.begin(19200); //38400
  
  
  //servo init
  //attach dedicate pin to servo
  servo9.attach(M9);
  servo6.attach(M6);
  servo5.attach(M5);
  servo3.attach(M3);
  arm();
  ///////////////////////////////
  
  //rollPID.SetMode(AUTOMATIC);
  pitchPID.SetMode(AUTOMATIC);
  pitchPID2.SetMode(AUTOMATIC);
  
  //rollPID.SetSampleTime(10);
  pitchPID.SetSampleTime(20);
  pitchPID2.SetSampleTime(20);
  
  
  
  rollSP=0;
  pitchSP=0;
  
  throttle=1150;
  
  delay(3000);
  
}


void loop() {
  
  //read bluetooth serial buffer
  //
  
 
  
  if(Serial.available()>=2){
    
    //roll=((double)(Serial.read()<<8|Serial.read()))/10;
    pitch=((double)(Serial.read()<<8|Serial.read()));
    
  
      
      
      
      //rollPID.Compute();
      //pitchPID.Compute();
      //pitchPID2.Compute();
      
    
  }
  
  pitchPID.Compute();
  pitchPID2.Compute();
  
  servo6.writeMicroseconds(throttle+motor6);
  servo5.writeMicroseconds(throttle+motor5);

}
