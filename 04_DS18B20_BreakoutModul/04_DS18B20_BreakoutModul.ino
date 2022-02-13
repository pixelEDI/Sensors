/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
           
www.pixeledi.eu | twitter.com/pixeledi


  Projekt:  DS18B20 Schaltung mit Berakout Modul         
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
  display1.println("DS18B20 Breakout");
  display1.setCursor(15, 25);
  display1.println("Temp: "+String(tempC)+" C");
  display1.setCursor(15, 40);
  display1.println("Temp: "+String(tempF)+" F");
  display1.drawRect(0,0,128,64,SSD1306_WHITE);
  display1.display();
  
  delay(2000);
}
