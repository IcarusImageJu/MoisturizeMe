
#ifndef MOISTURIZE_SCREEN_H
#define MOISTURIZE_SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "Moisturizer.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define VERSION_NAME "v0.3.2"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class MoistureScreen {

    public:
        MoistureScreen(int size, Moisturizer *moisturizers):
            size(size),
            moisturizers(moisturizers)
        {}

        void setup() {
            // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
            if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
                Serial.println(F("SSD1306 allocation failed"));
                for(;;); // Don't proceed, loop forever
            }
            henlo();
        }

        void loop() {
          for (int index = 0; index <= size; index++) {
            Moisturizer currentMoisturizer = moisturizers[index];
            if(index == 0) {
               display.clearDisplay();
            }
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0, ((SCREEN_HEIGHT / 4) * index ) + ((SCREEN_HEIGHT / 4 / (size - 1)) * index));
            display.print(index);
            display.print(" > ");
            display.print(F("H% "));
            display.print(currentMoisturizer.humidity());
            if(currentMoisturizer.askWatering()) {
               display.print(F(" ~~~"));
            }
            // Display our values
            if(index == (size - 1)) {
             display.display();
            }
          };
        }
        
    protected:
        Moisturizer *moisturizers;
        int size;
        void henlo() {
            // Clear the screen from previous values
            display.clearDisplay();
            // Set a text size
            display.setTextSize(2);
            // Set the text color to white
            display.setTextColor(SSD1306_WHITE);
            // Set our cursor to the starting point
            display.setCursor(0,0);
            // Print on 1st line
            display.print(F("Moisturize"));
            // Print on 2nd line
            display.print(F("Me"));
            // Print version
            display.setTextSize(1);
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
            display.setCursor(60, (SCREEN_HEIGHT / 2) + 6);
            display.print(VERSION_NAME);
            // Display our values
            display.display();
        }
};

#endif
