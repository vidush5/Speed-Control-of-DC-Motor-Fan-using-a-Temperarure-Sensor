#include "Arduino.h"
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define ONE_WIRE_BUS A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int fan = 8;       // the pin where fan is 
int temp;
int tempMin=40;// the temperature to start the fan
int tempMax = 80;   // the maximum temperature when fan is at 100%
int fanSpeed;
int fanLCD;

 
void setup() {
 pinMode(fan, OUTPUT);
 Serial.begin(9600); 
 analogWrite(9,130);
 
 lcd.begin(16,2);
 lcd.print("    GROUP 7");
 lcd.setCursor(0,1); // move cursor to next line
 lcd.print("  MINI PROJECT");
 delay(5000);
 sensors.begin();
}
 
void loop() {
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);     // get the temperature
   if(temp  < tempMin) { // if temp is lower than minimum temp 
      fanSpeed = 0; // fan is not spinning 
      digitalWrite(fan, LOW);
      Serial.print("Temperature is: ");
      Serial.println(temp);
   } 
   if((temp  >= tempMin) && (temp <= tempMax)) { // if temperature is higher than minimum temp 
      fanSpeed = map(temp, tempMin, tempMax, 20, 255); // the actual speed of fan
      fanSpeed = 1.4*temp;
      fanLCD = map(temp, tempMin, tempMax, 0, 100); // speed of fan to display on LCD 
      analogWrite(fan, fanSpeed); // spin the fan at the fanSpeed speed 
   } 
  lcd.clear(); 
  lcd.print("    GROUP 7");
  lcd.setCursor(0,1); // move cursor to next line
  lcd.print("TEM:");
  lcd.print(temp);      // display the temperature
  lcd.print("C ");
  lcd.print("FAN:");
  lcd.print(fanLCD);    // display the fan speed
  lcd.print("%");
  delay(100);
 
}

