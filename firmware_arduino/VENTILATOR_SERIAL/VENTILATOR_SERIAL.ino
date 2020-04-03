#include<SFE_BMP180.h>
#include <Wire.h>

//Define Stepper 
#define EN 8
#define DIR 6
#define STP 3


// You will need to create an SFE_BMP180 object, here called "pressure":
SFE_BMP180 pressure;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STP, OUTPUT);
  Serial.begin(115200);
  Serial.println("initialize bmp180"); 
  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("connecting");
  delay(1000);
}
