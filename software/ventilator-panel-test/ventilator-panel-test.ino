// Author: Arunroth VEN

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP085 bmp;
  

void setup()
{
  lcd.init();                      
  lcd.backlight();
  if (!bmp.begin()) {
    lcd.setCursor(0,0);
    lcd.print("Cannot Find BMP180");
  while (1) {}
  }
  
}


void loop()
{
  lcd.setCursor(0,0);
  lcd.print("P= ");
  lcd.print(bmp.readPressure());
  lcd.print("   ");
  
  lcd.setCursor(0,1);
  lcd.print("A0: ");
  lcd.print(analogRead(A0));
  lcd.print("  ");
  
  lcd.setCursor(10,1);
  lcd.print("A1: ");
  lcd.print(analogRead(A1));
  lcd.print("  ");

  lcd.setCursor(0,2);
  lcd.print("A2: ");
  lcd.print(analogRead(A2));
  lcd.print("  ");
  
  lcd.setCursor(10,2);
  lcd.print("A3: ");
  lcd.print(analogRead(A3));
  lcd.print("  ");

  lcd.setCursor(0,3);
  lcd.print("Temperature: ");
  lcd.print(bmp.readTemperature());
  lcd.print(" ");

  delay(200);
  

}
