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
 * brushless esc wire 
 * orange = signal
 * red = plus
 * brown is ground
 ********************/

int i=0;
float cmdOut = 0;

int m9pwm=0;
int m6pwm=0;
int m5pwm=0;
int m3pwm=0;

double rollrateSP,rollrate,motor6,motor5;


PID rollratePID1(&rollrate,&motor6,&rollrateSP,3,0,0, DIRECT);
PID rollratePID2(&rollrate,&motor5,&rollrateSP,3,0,0, REVERSE);


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


  //servo init
  //attach dedicate pin to servo
  servo9.attach(M9);
  servo6.attach(M6);
  servo5.attach(M5);
  servo3.attach(M3);
  arm();
  ///////////////////////////////

  rollratePID1.SetMode(AUTOMATIC);
  rollratePID2.SetMode(AUTOMATIC);


  rollratePID1.SetSampleTime(16);
  rollratePID2.SetSampleTime(16);

  rollrateSP=0;

  throttle=1200;
  rollrate=0;
  motor5=0;
  motor6=0;

}


void loop() {

  //read bluetooth serial buffer

  if(Serial.available()>=2){
    rollrate=(double)(Serial.read()<<8|Serial.read());
    rollratePID1.Compute();
    rollratePID2.Compute();

    servo6.writeMicroseconds(throttle+motor6);
    servo5.writeMicroseconds(throttle+motor5);

  }



}

