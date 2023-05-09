
/*
        _          _ ______ _____ _____ 
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |  
 | '_ \| \ \/ / _ \ |  __| | |  | || |  
 | |_) | |>  <  __/ | |____| |__| || |_ 
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |                                    
 |_|                                    
                             
www.pixeledi.eu | https://linktr.ee/pixeledi
DHT20 und DHT22 | V1.0 | 05.2023
*/

#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h> // DHT22
#include <DFRobot_DHT20.h>

// Default I2C address = 0x38
DFRobot_DHT20 dht20;

// DHT22
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht22 = DHT(DHTPIN, DHTTYPE);

// OLED 0,96
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long previousMillis = millis();

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);

  dht22.begin();
  dht20.begin();
  // Optional
  // while (dht20.begin()) {
  //   Serial.println("Sensor Fehler");
  //   delay(1000);
  // }
}

void loop() {

  unsigned long currentMillis = millis();
 
  if (currentMillis - previousMillis >= (1000 * 2)) {
      Serial.println("neue Werte");

    previousMillis = currentMillis;

    float dht20_temperature = dht20.getTemperature();
    float dht20_humidity = dht20.getHumidity()*100;

    float dht22_temperature = dht22.readTemperature();
    float dht22_humidity = dht22.readHumidity();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    // DHT20 data.
    display.setCursor(0, 2);
    display.setTextSize(2);
    display.print("DHT20");

    display.setCursor(10, 35);
    display.setTextSize(1);
    display.print(dht20_temperature);
    display.print((char)247);
    display.print("C ");

    display.setCursor(10, 45);
    display.print(dht20_humidity);
    display.print("%");

    display.drawLine(SCREEN_WIDTH / 2, 30, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

    // DHT22 data.
    byte dht22_width = SCREEN_WIDTH / 2;
    display.setTextSize(2);
    display.setCursor(dht22_width, 2);
    display.print("DHT22");

    display.setCursor(dht22_width + 20, 35);
    display.setTextSize(1);
    display.print(dht22_temperature);
    display.print((char)247);
    display.print("C ");

    display.setCursor(dht22_width + 20, 45);
    display.print(dht22_humidity);
    display.print("%");

    display.display();
  }
}
