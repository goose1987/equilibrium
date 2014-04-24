//hello
#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;

//brushless esc wire 
//orange = signal
//red = plus
//brown is ground

const int TX_BT = 10;
const int RX_BT = 11;


int test = 5;
int i=0;
 
int outPWM = 9;
int duty = 0; //duty cycle
int serialRead = 0;  
int throttle = 0;

int cmd=0; 
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

  
}


void loop() {
  /*
  //read bluetooth serial buffer
  if(btSerial.available()){
    cmd=btSerial.parseInt();
    Serial.println(cmd);    
  }
  */
    // Read serial input:
  if(Serial.available()){
    cmd=Serial.parseInt();
    servo1.write(cmd);
   
    Serial.println(cmd); 
  }
}


