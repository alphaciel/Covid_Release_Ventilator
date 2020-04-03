// Author: Arunroth VEN

#include <PID_v1.h>
#include <Encoder.h>

Encoder myEnc(3, 2);

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
  Serial.begin(9600);
  pinMode(MA, OUTPUT); 
  pinMode(MB, OUTPUT);  
  pinMode(5, OUTPUT);
  
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-255,255);
  target1 = 0;
  homing();
} 

void homing(){
  long tstamp;    
  long error=0;
  int scanning_steps=3; // Step size
  int step_interval = 7;
  int max_error; // When stuck i.e. how long does it stick for
  float homing_power=1.00; // Max speed
  max_error=(scanning_steps*20);
    while( error>-max_error){  
      if(millis()-tstamp>7) // 7 is time interval between each step
        {
          setpoint-=scanning_steps;
          tstamp=millis(); 
        }
      input = myEnc.read();;
      error=setpoint-input;  
      while(!myPID.Compute()); 
      pwm(output*homing_power); 
  }
  target1=0; // target is now the new zero 
  myEnc.write(-30); // Setting zero (offset a bit)
  while(setpoint < 250  ){  
      if(millis()-tstamp>7)
        {
          setpoint+=scanning_steps;
          tstamp=millis(); 
        }
      input = myEnc.read();; 
      while(!myPID.Compute()); // wait till PID is actually computed
      pwm(output*homing_power); 
  }
  myEnc.write(0);
  target1=0; 
}

void loop(){
    setpoint=target1;
    input = myEnc.read(); 
    while(!myPID.Compute());
    pwm(output); 
    
}

  void pwm(int out) {
   if(out>0) { digitalWrite(MA,1); digitalWrite(MB,0); }
   else      { digitalWrite(MA,0); digitalWrite(MB,1); }
   analogWrite(5,abs(out));
  }