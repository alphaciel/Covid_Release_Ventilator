// MIT-Cambodia Emergency Ventilator Prototype
// Authors: Jared Baribeau

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#include <Encoder.h>
#include <PID_v1.h>

Encoder myEnc(2, 3);

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP085 bmp;

enum states {CALIBRATION, SETUP, INHALE, PAUSE, EXHALE};

/**************************************************/
// Hard-coded Parameters
/**************************************************/
// Clinical
float t_hold    = 0.015;    // The amount of time (in seconds) to hold the compression at the end of the inhale for plateau pressure.
int p_max       = 40;       // The maximum allowable pressure (set to 40 cmH20).
int v_ex        = 0.5;      // The velocity of the fingers in the expiratory phase (in % of max). Note: this doens't affect breath.

// PID
double kp=3;
double ki=0;
double kd=0.0;

// Arm Position Calibration
int pos_open = 250;             // Where the figers should open to between breaths.
int pos_hardstop_offset = 30;   // How far home position is from hard stop.
int v_homing = 0.5;          // The velocity of the fingers during homing (i.e. slow), in % of max.
int step_size = 3;              // Step size during home scan (will affect how fast calibration happens)
int step_interval = 7;          // How long between steps (changing setpoint). Cannot be too fast or it will be miss-calibrated!
int max_error = step_size * 20; // Sensitivity for detecting hardstop. Too low will cause miss-calibration. Too high stresses the mechanicals.


/**************************************************/
// Pin Assignments
/**************************************************/
const int PIN_TIDAL_VOLUME_INPUT    = A0;
const int PIN_BPM_INPUT             = A1;
const int PIN_IE_RATIO_INPUT        = A2;
const int PIN_MOTOR_PWM             = 5;
const int PIN_MOTOR_A               = 6;
const int PIN_MOTOR_B               = 7;
const int PIN_HOME_SWITCH           = 7;


/**************************************************/
// Variables
/**************************************************/
int state; // Current state
float t_current = 0;        // Time elapsed in current state
float t_start = 0;          // Time elapsed in current state
float p_peak = 0;           // Maximum pressure during inhale. We consider 40 cmH20 to be the upper pressure limit for safety.
float p_plat = 0;           // The plateau pressure of the inhale. An important diagnostic number for clinicians.
int peep = 0;               // The residual pressure in the system after exhale. Controlled manually via a PEEP valve on the Ambu Bag.
long p_meas = 0;            // Measured pressure
bool at_home = false;       // Flag indicating limit switch at home is pressed.
volatile long pos_home = 0; // Calibrated home position
volatile long pos_max = 0;  // TODO: Determine how to calibrate this.
double v_max = 0.0;         // Set the max speed of the fingers, depending on state TODO: Determine if there's a better way to do MISO/Split-PID control.
long pos_homing_error = 0;  // During homing, how far off is the setpoint from the actual
long t_homing_step = 0;     // How long between shifts in setpoint for homing (this change how fast homing happens)

// Clinical Settings
float tidal_vol = 0.0;  // The total volume of air to be delivered to the patient, in % of bag max. Max will be roughly 1000ml.
int bpm = 0;            // Breaths per minute, also called respiratory rate (RR). Typically varies between 8-30 BPM.
int ie_ratio = 0;       // The ratio (1:ie_ratio) of the duration of the inhale to the duration of the exhale. 
                        // For example, a 1:3 ratio means that the exhale phase lasts three times longer than the inhale phase.
                        // Typically varies between 1:1 to 1:3, with a maximum of 1:4 currently being observed in COVID-19 patients.

// Calculated Parameters
int t_cycle = 0;    // The length of time (in seconds) of an inhale/exhale cycle.
int t_in = 0;       // The length of time (in seconds) of the inspiratory phase.
int t_ex = 0;       // The length of time (in seconds) of the expiratory phase.
int v_in = 0;       // The rotation rate of the inspiratory phase (in pulses/second).

// PID
double enc_input=0, vel_output=0, pos_setpoint=0;
PID myPID(&enc_input, &vel_output, &pos_setpoint,kp,ki,kd, DIRECT);


void readSettings(){
    // Read settings poteniometers
    tidal_vol = analogRead(A0) / 1024.0;// Analog 0-1024 to percent scale (0-100)
    bpm = analogRead(A1) / 22 + 8;      // Analog 0-1024 to 8-30bpm (range of 22)
    ie_ratio = analogRead(A2) / 4;      // Analog 0-1024 to 1-4

    // TODO: decide between the use of seconds and milliseconds
    // Calculate new parameters
    t_cycle = 60/bpm;
    t_in = t_cycle / (1 + ie_ratio);
    t_ex = t_cycle - t_in;
    v_in = pos_max * tidal_vol / t_in;
}

// TODO: Plan when to update LCD 
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

void driveMotor(double _vel) {
    if(_vel>0) { digitalWrite(PIN_MOTOR_A,0); digitalWrite(PIN_MOTOR_B,1); }
    else      { digitalWrite(PIN_MOTOR_A,1); digitalWrite(PIN_MOTOR_B,0); }

    if(_vel > v_max){ _vel = v_max;};
    analogWrite(PIN_MOTOR_PWM,abs((int)_vel));
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

void resetStateClock(){
    t_start = millis() * 1000;
    t_current = 0;
}

void setup()
{
    state = CALIBRATION;
    initializeLCD();

    pinMode(PIN_MOTOR_A, OUTPUT); 
    pinMode(PIN_MOTOR_B, OUTPUT);  
    pinMode(PIN_MOTOR_PWM, OUTPUT);

    pinMode(PIN_HOME_SWITCH, INPUT_PULLUP);
    
    myPID.SetMode(AUTOMATIC);
    myPID.SetSampleTime(1);
    myPID.SetOutputLimits(-255,255);
}

void loop()
{
    t_current = millis()*1000 - t_start; // Update timer

    /**************************************************/
    // Read Sensors
    /**************************************************/
    p_meas = bmp.readPressure();
    enc_input = myEnc.read();
    // at_home = !digitalRead(PIN_HOME_SWITCH); // TODO chcek if this is backwards.
    

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
    
    case CALIBRATION:
        // Move arms until they hit hard-stop (and can no longer make it to setpoint)
        // TODO: Figure out how this can fail, and how to prevent it.
        pos_homing_error = pos_setpoint - enc_input; 
        if(pos_homing_error > -max_error){
            if(millis() - t_homing_step > step_interval){
                pos_setpoint -= step_size;
                v_max = v_homing;
                t_homing_step = millis();
            }
        }
        else {
            myEnc.write(-30);   // Set home position to a little bit before hard stop.
            pos_home = 0;       // Calibrate home position
            state = SETUP;
        }
        break;
    
    case SETUP:
        // Move arms to open position
        pos_setpoint = pos_open;
        v_max = v_ex;
        pos_homing_error = pos_setpoint - enc_input; 

        if(abs(pos_homing_error) <= max_error){
            state = INHALE;
            resetStateClock();
        }
        break;
    

    case INHALE:
        if(t_current < t_in){
            // Command motor to go to position VT, at velocity v_in
            pos_setpoint = pos_max * tidal_vol;
            v_max = v_in * 1.10; // TODO: Ensure this doesn't reduce the volume displaced
        }
        else {
            state = PAUSE;
            resetStateClock();
        }
        break;
    

    case PAUSE:
        if(t_current < t_hold){
            // Hold position for time t_hold
            pos_setpoint = enc_input;
        }
        else {
            p_plat = p_meas; // Record plateau pressure
            state = EXHALE;
            resetStateClock();
        }
        break;
    

    case EXHALE:
        if(t_current < t_ex){
            // Command motor to go to home position, at velocity v_ex
            pos_setpoint = pos_open;
            v_max = v_ex;
        }
        else {
            // Check if input settings have changed
            readSettings();
            state = INHALE;
            resetStateClock();
        }
        break;
    
    default:
        // Sound alarm.
        break;
    }

    /**************************************************/
    // Update Outputs
    /**************************************************/
    while(!myPID.Compute());
    // TODO: Calculate if on-track to be on-time. If not, adjust accordingly.
    driveMotor(vel_output);
    updateLCD(); // TODO: Don't do this every loop, it's slow.
}
