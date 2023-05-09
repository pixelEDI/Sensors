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
CCS811 Sensor | V1.0 | 05.2023
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ccs811.h" // by Maarten Pennings

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// CCS811 Sensor
CCS811 ccs811(-1);
uint16_t eco2, etvoc, errstat, raw;
unsigned long previousMillis = 0;

void showSensorValues()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // eco2 data.
  display.setCursor(0, 2);
  display.setTextSize(2);
  display.print("eco2");

  display.setCursor(10, 35);
  display.setTextSize(1);
  display.print(eco2);
  display.print(" ppm ");

  display.drawLine(SCREEN_WIDTH / 2, 30, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

  byte halfscreen = SCREEN_WIDTH / 2;
  display.setTextSize(2);
  display.setCursor(halfscreen, 2);
  display.print("etvoc");

  display.setCursor(halfscreen + 20, 35);
  display.setTextSize(1);
  display.print(etvoc);
  display.print(" ppb ");

  display.display();
}


void getSensorValues()
{
  ccs811.read(&eco2, &etvoc, &errstat, &raw);

  if (errstat == CCS811_ERRSTAT_OK)
  {
    Serial.println(eco2);
    Serial.println(etvoc);
    Serial.println("--------");
  }
  else if (errstat == CCS811_ERRSTAT_OK_NODATA)
  {
    Serial.println("CCS811: waiting for (new) data");
  }
  else if (errstat & CCS811_ERRSTAT_I2CFAIL)
  {
    Serial.println("CCS811: I2C error");
  }
  else
  {
    Serial.print("CCS811: errstat=");
    Serial.print(errstat, HEX);
    Serial.print("=");
    Serial.println(ccs811.errstat_str(errstat));
  }
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);

  ccs811.set_i2cdelay(50);
  bool ok = ccs811.begin();
  if (!ok)
    Serial.println("setup: CCS811 begin FAILED");

  // Start measuring
  ok = ccs811.start(CCS811_MODE_1SEC);
  if (!ok)
    Serial.println("setup: CCS811 start FAILED");

  Serial.println("Setup finished");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 5000)
  {
    previousMillis = currentMillis;
    getSensorValues();
    showSensorValues();
    // here is space for IoT Magic
    // push values via MQTT to InfluxDB
  }
}