#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define ONE_WIRE_BUS 2 // In ESp8266 equal D4 Instead of A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
float Celsuis =0;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
 pinMode(D0, OUTPUT);
 sensor.begin();
  lcd.begin(16,2); // initialize LCD                    
 lcd.backlight(); // turn on LCD backlight  
  Serial.begin(9600);
}
void loop() {
    sensor.requestTemperatures();
    Celsuis = sensor.getTempCByIndex(0);
    Serial.print(Celsuis);// read to server
    lcd.setCursor(0, 0);// set cursor to first column, first row
    lcd.print("Temp:");
    lcd.print(Celsuis );
    delay(1000);
    lcd.setCursor(0,1);// set cursor to first column, second row
    if(Celsuis < 20){
      digitalWrite(D0,HIGH); // open motor and fan 
      lcd.print("System is stopped");
      }
    else {
      digitalWrite(D0,LOW);// close motor and fan
      lcd.print("System is Work");
      }
    delay(1000);
    lcd.clear(); 
}
