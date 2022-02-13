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

  Projekt:  GY01 Schaltung           
  Datum:    01/2022

*/

#include <Wire.h>
//Das Herzstück des GY-21-Moduls ist der Sensorchip "HTU21D(F)" somit können wir von Adafruit diese Bibliothek verwenden.
#include "Adafruit_HTU21DF.h"

//Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void setup() {
  Serial.begin(115200);
  
  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  //Sensor starten
  if (!htu.begin()) {
    Serial.println("Kein Sensor gefunden");
    while (1);
  }
  
}

void loop() {
  //Werte aktualisieren
  float temp = htu.readTemperature();
  float rel_hum = htu.readHumidity();
  Serial.print("Temperture: "); Serial.print(temp); Serial.println(" C°");
  Serial.print("Feuchtigkeit: "); Serial.print(rel_hum); Serial.println(" %");

  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 15);
  display1.println("Temp: "+String(temp)+" C");
  display1.setCursor(15, 30);
  display1.println("Feucht: "+String(rel_hum)+" %");
  display1.drawRect(0,0,128,64,SSD1306_WHITE);
  display1.display();

  delay(2000);
}
