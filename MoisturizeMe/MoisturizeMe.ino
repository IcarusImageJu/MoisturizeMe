#include "MoistureSensor.h"
#include "Valve.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IO Config
// Number of sensors/valves
#define CONTROLS 3
// MoistureSensor pin, waterValue, airValue, minMoistRatio
MoistureSensor moistureSensor0(0, 282, 591, 40);
MoistureSensor moistureSensor1(1, 288, 590, 40);
MoistureSensor moistureSensor2(2, 291, 592, 40);
MoistureSensor const MOISTURE_SENSORS [CONTROLS] = {moistureSensor0, moistureSensor1, moistureSensor2};
// Enter the digital chan number for the valve relay
Valve valve0(7);
Valve valve1(7);
Valve valve2(7);
Valve const VALVES [CONTROLS] = {valve0, valve1, valve2};
// Enter the digital chan number for the light relay
#define LIGHT_OUTPUT 4

void setup() {
  // Serial on the same port of nodemcu
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  for (int i = 0; i <= CONTROLS - 1; i++)
  {
    VALVES[i].setup();
  }
  
  // Set the pin for the light in OUTPUT mode
  pinMode(LIGHT_OUTPUT, OUTPUT);
  // and keep it not lit durint init
  digitalWrite(LIGHT_OUTPUT, HIGH);
  // Print our Logo
  // henlo();
}

void loop() {
  for (int i = 0; i <= CONTROLS - 1; i++)
  {
    moisturizing(i);
    VALVES[i].loop();
  }
  
  delay(1000);
}

void moisturizing(int i) {
  // Read the sensor value and set it to the var
  float soilMoistureValue = calcMoistureRatio(i);
  bool watering = soilMoistureValue < MOISTURE_SENSORS[i].minMoistRatio;
  // Check the moisture ratio against our min var
  if(watering) {
    // Close the gate, to water the plant
    VALVES[i].watering();
  }
  logMoisture(i, soilMoistureValue, watering);
}

// Calc the moisture ratio, return the ratio
// 0 is air
// 100 is water
float calcMoistureRatio(int i) {
  MoistureSensor sensor = MOISTURE_SENSORS[i];
  float current = analogRead(sensor.pin);
  return 100 - (((current - sensor.waterValue) / (sensor.airValue - sensor.waterValue)) * 100);
}


// Print stuff on the OLED Screen that concern moisture status
void logMoisture(int index, float soilMoistureValue, bool watering) {
  if(index == 0) {
    display.clearDisplay();
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, ((SCREEN_HEIGHT / 4) * index ) + ((SCREEN_HEIGHT / 4 / (CONTROLS - 1)) * index));
  display.print(index);
  display.print(" > ");
  if(watering) {
    display.print(F("Watering"));
  } else {
    if(soilMoistureValue < 1) {
      display.print(F("Air"));
      // Check our ratio if its water like
    } else if (soilMoistureValue > 95) {
      display.print(F("Water"));
      // Print our humidity %
    } else {
      
      display.print(F("H% "));
      display.print(soilMoistureValue);
    }
  }
  // Display our values
  // convert data to String
  String cdata = "V";
  cdata += index;
  cdata += ":";
  cdata += soilMoistureValue;
  cdata += ",W";
  cdata += index;
  cdata += ":";
  cdata += watering;
  // Print it for nodemcu reading
  Serial.println(cdata);
  if(index == (CONTROLS - 1)) {
    display.display();
  }
}
