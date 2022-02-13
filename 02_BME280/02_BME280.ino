/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    


  Projekt:  BME280 Schaltung           
  Datum:    01/2022

*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; // I2C

//Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);

  //0x76 I2C Adresse vom Sensor
  if (!bme.begin(0x76)) {
    Serial.println("Keinen BME280 Sensor gefunden!");
    while (1);
  }

}

void loop() {
  
  float temp =bme.readTemperature();
  float pressure =bme.readPressure() / 100.0F;
  float hum =bme.readHumidity();

  Serial.print("Temperatur:  ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Luftdruck: ");
  Serial.print(pressure);
  Serial.println(" hPa");  

  Serial.print("Feuchtigkeit: ");
  Serial.print(hum);
  Serial.println(" %");

  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 10);
  display1.println("Temp: "+String(temp)+" C");
  display1.setCursor(15, 25);
  display1.println("Luftd: "+String(pressure)+" hPa");
  display1.setCursor(15, 40);
  display1.println("Feucht: "+String(hum)+" %");
  display1.drawRect(0,0,128,64,SSD1306_WHITE);
  display1.display();

  delay(2000);
}
