
#ifndef MOISTURIZE_SCREEN_H
#define MOISTURIZE_SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include "Moisturizer.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define VERSION_NAME "v0.5.1"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned char humidity2_icon16x16[] =
{
  0b00000000, 0b00000000, //                 
  0b00000001, 0b10000000, //        ##       
  0b00000011, 0b11000000, //       ####      
  0b00000111, 0b11100000, //      ######     
  0b00001111, 0b11110000, //     ########    
  0b00001111, 0b11110000, //     ########    
  0b00011111, 0b11111000, //    ##########   
  0b00011111, 0b11011000, //    ####### ##   
  0b00111111, 0b10011100, //   #######  ###  
  0b00111111, 0b10011100, //   #######  ###  
  0b00111111, 0b00011100, //   ######   ###  
  0b00011110, 0b00111000, //    ####   ###   
  0b00011111, 0b11111000, //    ##########   
  0b00001111, 0b11110000, //     ########    
  0b00000011, 0b11000000, //       ####      
  0b00000000, 0b00000000, //                 
};

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
          if(henloTimer <= millis()){
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
//                 display.print(F(" ~~~"));
                 display.drawBitmap(100, ((SCREEN_HEIGHT / 4) * index), humidity2_icon16x16, 16, 16, 1 );
              }
              // Display our values
              if(index == (size - 1)) {
               display.display();
              }
            };
          }
        }
        
    protected:
        Moisturizer *moisturizers;
        int size;
        unsigned long henloTimer;
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
            // Print droplet after
            display.drawBitmap(25, (SCREEN_HEIGHT / 2), humidity2_icon16x16, 16, 16, 1 );
            // Print version
            display.setTextSize(1);
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
            display.setCursor(60, (SCREEN_HEIGHT / 2) + 6);
            display.print(VERSION_NAME);
            // Display our values
            display.display();
            henloTimer = millis() + 5000;
        }
};

#endif
