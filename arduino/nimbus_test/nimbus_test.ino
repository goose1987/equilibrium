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

const int TX_BT = 10;
const int RX_BT = 11;
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
int foo;
double pitchSP,pitch,pitchcomp;

PID rollPID(&roll,&rollcomp,&rollSP,5,0.1,0.5, DIRECT);

PID pitchPID(&pitch,&pitchcomp,&pitchSP,5,0.1,0.5,DIRECT);



SoftwareSerial btSerial(TX_BT,RX_BT);

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
  Serial.begin(38400); //38400
  Serial.println("USB Connected");

  btSerial.begin(19200);
  
  //servo init
  //attach dedicate pin to servo
  servo9.attach(M9);
  servo6.attach(M6);
  servo5.attach(M5);
  servo3.attach(M3);
  arm();
  ///////////////////////////////

  rollPID.SetMode(AUTOMATIC);
  pitchPID.SetMode(AUTOMATIC);
  
  
  rollPID.SetSampleTime(20);
  pitchPID.SetSampleTime(20);
  
  rollPID.SetOutputLimits(-100,100);
  pitchPID.SetOutputLimits(-100,100);
  
  rollSP=0;
  pitchSP=0;
  
  throttle=1100;
  
}


void loop() {
  
  //read bluetooth serial buffer
  
  if(btSerial.available()>=2){
    
    //roll=((double)(btSerial.read()<<8|btSerial.read()))/10;
    
    pitch=((double)(btSerial.read()<<8|btSerial.read()))/100;
    
    rollPID.Compute();
    pitchPID.Compute();
    
    servo6.writeMicroseconds(throttle+pitchcomp);
    servo5.writeMicroseconds(throttle-pitchcomp);
    
    Serial.println(pitchcomp);
    
    
    
  }
  

}
