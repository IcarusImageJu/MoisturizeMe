#include "Moisturizer.h"
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
// Enter the digital chan number for the light relay
#define LIGHT_OUTPUT 4

Moisturizer moisturizer0(0, 282, 591, 40, 7, 2000);
Moisturizer moisturizer1(1, 288, 590, 40, 6, 2000);
Moisturizer moisturizer2(2, 291, 592, 40, 5, 2000);

void setup() {
  // Serial on the same port of nodemcu
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Setup our moisturizers
  moisturizer0.setup();
  moisturizer1.setup();
  moisturizer2.setup();
  // Set the pin for the light in OUTPUT mode
  pinMode(LIGHT_OUTPUT, OUTPUT);
  // and keep it not lit durint init
  digitalWrite(LIGHT_OUTPUT, HIGH);
  // Print our Logo
  henlo();
}

void loop() {
  moisturizer0.loop();
  moisturizer1.loop();
  moisturizer2.loop();
}

// Print stuff on the OLED Screen that concern moisture status
// void logMoisture(int index, float soilMoistureValue, bool watering) {
//   if(index == 0) {
//     display.clearDisplay();
//   }
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0, ((SCREEN_HEIGHT / 4) * index ) + ((SCREEN_HEIGHT / 4 / (CONTROLS - 1)) * index));
//   display.print(index);
//   display.print(" > ");
//   if(watering) {
//     display.print(F("Watering"));
//   } else {
//     if(soilMoistureValue < 1) {
//       display.print(F("Air"));
//       // Check our ratio if its water like
//     } else if (soilMoistureValue > 95) {
//       display.print(F("Water"));
//       // Print our humidity %
//     } else {
      
//       display.print(F("H% "));
//       display.print(soilMoistureValue);
//     }
//   }
//   // Display our values
//   // convert data to String
//   String cdata = "V";
//   cdata += index;
//   cdata += ":";
//   cdata += soilMoistureValue;
//   cdata += ",W";
//   cdata += index;
//   cdata += ":";
//   cdata += watering;
//   // Print it for nodemcu reading
//   Serial.println(cdata);
//   if(index == (CONTROLS - 1)) {
//     display.display();
//   }
// }
