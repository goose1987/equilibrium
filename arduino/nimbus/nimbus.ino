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

double motor5,motor6,motor3,motor9;

PID rollPID(&roll,&motor9,&rollSP,60,5,40, REVERSE);
PID rollPID2(&roll,&motor3,&rollSP,60,5,40, DIRECT);

PID pitchPID(&pitch,&motor5,&pitchSP,60,5,40,REVERSE);

PID pitchPID2(&pitch,&motor6,&pitchSP,60,5,40,DIRECT);

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
  
  rollPID.SetMode(AUTOMATIC);
  rollPID2.SetMode(AUTOMATIC);
  
  pitchPID.SetMode(AUTOMATIC);
  pitchPID2.SetMode(AUTOMATIC);
  
  
  
  rollPID.SetSampleTime(5);
  rollPID2.SetSampleTime(5);
  
  pitchPID.SetSampleTime(5);
  pitchPID2.SetSampleTime(5);
  
  //pitchPID.SetOutputLimits(0,400);
  //pitchPID2.SetOutputLimits(0,400);
  
  rollSP=0;
  pitchSP=0.0;
  
  throttle=1200;
  
  
  
  delay(3000);
  //servo6.writeMicroseconds(1200);
  //servo5.writeMicroseconds(1200);
  servo3.writeMicroseconds(1100);
  servo9.writeMicroseconds(1100);  
  servo6.writeMicroseconds(1100);
  servo5.writeMicroseconds(1100); 
  
  delay(1000);
  servo3.writeMicroseconds(1100);
  servo9.writeMicroseconds(1100);  
  servo6.writeMicroseconds(1100);
  servo5.writeMicroseconds(1100);
  delay(1000);
  servo3.writeMicroseconds(throttle);
  servo9.writeMicroseconds(throttle);  
  servo6.writeMicroseconds(throttle);
  servo5.writeMicroseconds(throttle);
  
  
}


void loop() {
  
  //read bluetooth serial buffer
  //
 
 
  
  if(Serial.available()>=4){
    
    roll=((double)(Serial.read()<<8|Serial.read()))/1000;
    pitch=((double)(Serial.read()<<8|Serial.read()))/1000;
    
 
    
  }
  
  rollPID.Compute();
  rollPID2.Compute();
  
  pitchPID.Compute();
  pitchPID2.Compute();
  
  
  servo3.writeMicroseconds(throttle+motor3);
  servo9.writeMicroseconds(throttle+motor9);  
  servo6.writeMicroseconds(throttle+motor6);
  servo5.writeMicroseconds(throttle+motor5);   
  
  
  
  if(pitch>1|pitch<-1){
   throttle=0; 
    
  }
   /*
   if(pitch>1|pitch<-1){
     
     pitchPID.SetMode(MANUAL);
     pitchPID2.SetMode(MANUAL);
     throttle=0;
     servo6.writeMicroseconds(0);
      servo5.writeMicroseconds(0);
      
   }else{
     
      servo6.writeMicroseconds(throttle+motor6);
      servo5.writeMicroseconds(throttle-10+motor5);
   }
   */
}
