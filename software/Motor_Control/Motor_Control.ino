// Author: Arunroth VEN

#include <PID_v1.h>
#include <Encoder.h>

Encoder myEnc(2, 3);

#define MA            6 
#define MB            7 

double kp=3,ki=0,kd=0.0;
double input=0, output=0, setpoint=0;
PID myPID(&input, &output, &setpoint,kp,ki,kd, DIRECT);
volatile long encoder0Pos = 0;
boolean auto1=false, auto2=false,counting=false;
long previousMillis = 0;  

long target1=0; 



void setup() { 
   
  pinMode(MA, OUTPUT); 
  pinMode(MB, OUTPUT);  
  pinMode(5, OUTPUT);
  
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-255,255);
} 

void loop(){
    setpoint=target1;
    input = myEnc.read(); 
    while(!myPID.Compute());
    pwm(output); 
    
}

  void pwm(int out) {
   if(out>0) { digitalWrite(MA,0); digitalWrite(MB,1); }
   else      { digitalWrite(MA,1); digitalWrite(MB,0); }
   analogWrite(5,abs(out));
  }