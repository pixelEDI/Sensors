/*
    ___ _____        ____       ___                      
   /   /__  /       / __ \___  / (_)   _____  _______  __
  / /| | / / ______/ / / / _ \/ / / | / / _ \/ ___/ / / /
 / ___ |/ /_/_____/ /_/ /  __/ / /| |/ /  __/ /  / /_/ / 
/_/  |_/____/    /_____/\___/_/_/ |___/\___/_/   \__, /  
                                                /____/   
  Produkt, Datenblatt und Pinout unter:
  https://www.az-delivery.de/

  Projekt:  DS18B20 Schaltung mit wasserdichten Edelstahl-Gehäuse
  Datum:    02/2022

*/
#include <OneWire.h>
#include <DallasTemperature.h>


const int tempSensor=D3;
/*
  Falls beim Kompelieren ein Fehler 'void directModeInput(uint32_t)' kommt
  eine frühere Version von OneWire installieren
*/
OneWire oneWire(tempSensor);
DallasTemperature sensors(&oneWire);
DeviceAddress one;
#define TEMPERATURE_PRECISION 10

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
  
  sensors.begin();
  if(!sensors.getAddress(one, 0)) {
    Serial.println("Unable to find address for Device 0");
  }
  sensors.setResolution(one, TEMPERATURE_PRECISION);
}

void loop() {
  
sensors.requestTemperatures(); 
  float tempC = sensors.getTempCByIndex(0);
  float tempF = sensors.getTempFByIndex(0);     
  Serial.print(tempC);
  Serial.println("ºC");
  Serial.print(tempF);
  Serial.println("ºF");
 
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 10);
  display1.println("DS18B20 Edelstahl");
  display1.setCursor(15, 25);
  display1.println("Temp: "+String(tempC)+" C");
  display1.setCursor(15, 40);
  display1.println("Temp: "+String(tempF)+" F");
  display1.drawRect(0,0,128,64,SSD1306_WHITE);
  display1.display();
  
  delay(300);
}
