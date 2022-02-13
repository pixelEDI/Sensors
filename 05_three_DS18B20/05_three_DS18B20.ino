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

  Projekt:  3x DS18B20 Schaltung           
  Datum:    02/2022

*/
#include <OneWire.h>
#include <DallasTemperature.h>
#define TEMPERATURE_PRECISION 12
const int tempSensor=26;
/*
  Falls beim Kompelieren ein Fehler 'void directModeInput(uint32_t)' kommt
  eine frühere Version von OneWire installieren
*/
OneWire oneWire(tempSensor);
DallasTemperature sensors(&oneWire);
DeviceAddress one, two, three;
float tempC1, tempC2, tempC3;

//Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void getSensorResolution(){
 sensors.setResolution(one, TEMPERATURE_PRECISION);
 sensors.setResolution(two, TEMPERATURE_PRECISION);
 sensors.setResolution(three, TEMPERATURE_PRECISION);
 Serial.println("");
 Serial.print("Device 0 Resolution: ");
 Serial.print(sensors.getResolution(one), DEC);
 Serial.println();
 Serial.print("Device 1 Resolution: ");
 Serial.print(sensors.getResolution(two), DEC);
 Serial.println();
 Serial.print("Device 2 Resolution: ");
 Serial.print(sensors.getResolution(three), DEC);
 Serial.println();

}

void getSensorAdresses(){
 if(!sensors.getAddress(one, 0)) {
  Serial.println("Unable to find address for Device 0"); }
 if(!sensors.getAddress(two, 1)) {
  Serial.println("Unable to find address for Device 1"); }
 if(!sensors.getAddress(three, 2)) {
  Serial.println("Unable to find address for Device 2"); }

  Serial.print("Device 0 Address: ");
  printAddress(one);
  Serial.println();
  Serial.print("Device 1 Address: ");
  printAddress(two);
  Serial.println();
  Serial.print("Device 2 Address: ");
  printAddress(three); 
}

void printAddress(DeviceAddress deviceAddress) {
 for(uint8_t i = 0; i < 8; i++) {
 if(deviceAddress[i] < 16) Serial.print("0");
 Serial.print(deviceAddress[i], HEX);
 }
}

void printResolution(DeviceAddress deviceAddress) {
 Serial.print("Resolution: ");
 Serial.println(sensors.getResolution(deviceAddress));
}

float printData(DeviceAddress deviceAddress) {
 float tempC = sensors.getTempC(deviceAddress);
 Serial.print("Temp: ");
 Serial.print(tempC);
 Serial.print(" C");

 Serial.print(" | Sensoradresse: ");
 printAddress(deviceAddress);
 Serial.println();
 return tempC;
}


void setup() {
  Serial.begin(115200);

  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(100);
  Serial.println("3xDS18B20 auf einem Pin auswerten.");
  sensors.begin();
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" gefunden.");
  Serial.print("Parasite power ist: ");
  if(sensors.isParasitePowerMode()) {
    Serial.println("ON");
  }
  else {
   Serial.println("OFF");
  }

  getSensorAdresses();
  getSensorResolution();

}



void loop() {
  

  Serial.print("Request...");
  sensors.requestTemperatures();
  Serial.println("fertig");
  tempC1 = printData(one);
  tempC2 = printData(two);
  tempC3 = printData(three);
  delay(1000);


  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(15, 10);
  display1.println("Sensor1: "+String(tempC1)+" C");
  display1.setCursor(15, 25);
  display1.println("Sensor2: "+String(tempC2)+" C");
  display1.setCursor(15, 40);
  display1.println("Sensor3: "+String(tempC3)+" C");
  display1.drawRect(0,0,128,64,SSD1306_WHITE);
  display1.display();
  
  delay(2000);
  
}
