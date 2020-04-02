// MIT-Cambodia Emergency Ventilator Prototype
// Authors: Jared Baribeau

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP085 bmp;

enum states {SETUP, INHALE, PAUSE, EXHALE};

//
// State Variables
//
int state = SETUP; // Current state
int t_current = 0;  // Time elapsed in current state
int p_peak = 0;     // Maximum pressure during inhale. We consider 40 cmH20 to be the upper pressure limit for safety.
int p_plat = 0;     // The plateau pressure of the inhale. An important diagnostic number for clinicians.
int peep = 0;       // The residual pressure in the system after exhale. Controlled manually via a PEEP valve on the Ambu Bag.
long p_meas = 0;    // Measured pressure

//
// Clinical Parameters
//
float tidal_vol = 0;  // The total volume of air to be delivered to the patient, in % of bag max. Max will be roughly 1000ml.
int bpm = 0;        // Breaths per minute, also called respiratory rate (RR). Typically varies between 8-30 BPM.
int ie_ratio = 0;   // The ratio (1:ie_ratio) of the duration of the inhale to the duration of the exhale. 
                    // For example, a 1:3 ratio means that the exhale phase lasts three times longer than the inhale phase.
                    // Typically varies between 1:1 to 1:3, with a maximum of 1:4 currently being observed in COVID-19 patients.

//
// Hard-coded Parameters
//
int t_hold = 0;     // The amount of time (in seconds) to hold the compression at the end of the inhale for plateau pressure.
int v_ex = 0;       // The velocity of the fingers in the expiratory phase (in pulses/second). Note: this doens't affect breath.
int v_homing = 0;   // The velocity of the fingers during homing (i.e. slow), in pulses/second).
int p_max = 40;     // The maximum allowable pressure (set to 40 cmH20).

//
// Calculated Parameters
//
int t_cycle = 0;    // The length of time (in seconds) of an inhale/exhale cycle.
int t_in = 0;       // The length of time (in seconds) of the inspiratory phase.
int t_ex = 0;       // The length of time (in seconds) of the expiratory phase.
int v_in = 0;       // The rotation rate of the inspiratory phase (in pulses/second).

//
// Pin Assignments
//
const int PIN_TIDAL_VOLUME_INPUT    = A0;
const int PIN_BPM_INPUT             = A1;
const int PIN_IE_RATIO_INPUT        = A2;

void readSettings(){
    // Read settings poteniometers, and update parameters accordingly.
    tidal_vol = analogRead(A0) / 10.24;      // TODO: Converstion from analog (0-1024) to percent scale (0-100)
    bpm = analogRead(A1) / 22 + 8;   // Converts from 0-1024 to 8-30bpm (range of 22)
    ie_ratio = analogRead(A2) / 4;   // Converts from 0-1024 to 1-4
}

void updateLCD()
{
    // Current Pressure
    lcd.setCursor(0, 0);
    lcd.print("P= ");
    lcd.print(bmp.readPressure());
    lcd.print("   ");

    // Tidal Volume
    lcd.setCursor(0, 1);
    lcd.print("TV: ");
    lcd.print(tidal_vol);
    lcd.print("  ");

    // BPM
    lcd.setCursor(10, 1);
    lcd.print("BPM: ");
    lcd.print(bpm);
    lcd.print("  ");

    // IE Ratio
    lcd.setCursor(0, 2);
    lcd.print("IE: 1:");
    lcd.print(ie_ratio);
    lcd.print("  ");

    // Peak Pressure
    lcd.setCursor(10, 2);
    lcd.print("PkP");
    lcd.print(p_peak);
    lcd.print("  ");

    // Plateau Pressure
    lcd.setCursor(0, 3);
    lcd.print("PltP: ");
    lcd.print(p_plat);
    lcd.print(" ");

    // // Temperature
    // lcd.setCursor(0, 3);
    // lcd.print("Temperature: ");
    // lcd.print(bmp.readTemperature());
    // lcd.print(" ");
}

void initializeLCD(){
    lcd.init();
    lcd.backlight();
    if (!bmp.begin())
    {
        lcd.setCursor(0, 0);
        lcd.print("Cannot Find BMP180");
        while (1)
        {
        }
    }
}

void setup()
{
    initializeLCD();
}

void loop()
{
    // Read sensors
    p_meas = bmp.readPressure();
    // TODO: read encoder
    // TODO: read limit switch

    /**************************************************/
    // Check Fault Conditions
    /**************************************************/
    // 1. Pressure Over Limit
    if (p_meas > p_max){
        // TODO: Sound alarm.
    }
    // 2. Motor not moving
    // 3. Pressure not changing when motor moving
    // 4. Pressure changing when motor not moving
    // 5. Main Power loss (assuming we have battery backup)
    // 6. 

    /**************************************************/
    // State machine
    /**************************************************/
    switch (state)
    {
    case SETUP:
        // Do homing:
        if(homing_switch == 0){
            // Move motor towards limit switch, with velocity v_homing
        }
        else {
            // Zero encoder
            // Move to INHALE
        }
        break;
    
    case INHALE:
        if(t_current < t_in){
            // Command motor to go to position VT, at velocity v_in
        }
        else {
            // Move to PAUSE
        }
        
        break;
    
    case PAUSE:
        if(t_current < t_hold){
            // Hold position for time t_hold
            // Measure plateau pressure
        }
        else {
            // Move to EXHALE
        }
        
        break;
    
    case EXHALE:
        if(t_current < t_ex){
            // Command motor to go to home position, at velocity v_ex
        }
        else {
            // Check if input settings have changed
            readSettings();
            // Move to INHALE
        }
        break;
    
    default:
        // Sound alarm.
        break;
    }
    updateLCD();
    delay(200);
}
