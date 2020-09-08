#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IO Config
// Enter the Analog Chan number for the moisture sensor
short int const MOISTURE_SENSOR = 0;
// Entre the digital chan number for the valve relay
short int const VALVE_OUTPUT = 7;
// Nodemcu communication
SoftwareSerial nodemcu(0,1); // RX, TX
String data;

// Moisturize Me Config
String const VERSION_NAME = "v0.1.1";

// Moisutre Config
// Register a float var for the sensor value to be stored
float soilMoistureValue;
// Register an int var for the value of the sensor when completly dry and is in ambiant air
short int const airValue = 581;
// Register an int var for the value of the sensor when dipped in water
short int const waterValue = 312;
// Register an int var for the minimum accepted value in % before watering the plant
short int const minMoistRatio = 40;

void setup() {
  Serial.begin(115200);
  nodemcu.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Set the pin for the valve in OUTPUT mode
  pinMode(VALVE_OUTPUT, OUTPUT);
  // Be sure to keep the vavle closed during the initialization phase
  digitalWrite(VALVE_OUTPUT, HIGH);
  // Print our Logo
//  henlo();
}

void loop() {
  moisturizing();
}

void moisturizing() {
  // Read the sensor value and set it to the var
  soilMoistureValue = analogRead(MOISTURE_SENSOR);
  // Check the moisture ratio against our min var
  if(calcMoistureRatio() < minMoistRatio) {
    // Close the gate, to water the plant
    digitalWrite(VALVE_OUTPUT, LOW);
    // Clear the screen from previous values
    display.clearDisplay();
    // Set the biggest size accepted by the screen
    display.setTextSize(2);
    // Set the color to white
    display.setTextColor(SSD1306_WHITE);
    // Set our cursor to the starting point
    display.setCursor(0,0);
    // Set our message
    display.println(F("Watering"));
    // Display our message
    display.display();
  } else {
    // Open the gate to stop watering the plant
    digitalWrite(VALVE_OUTPUT, HIGH);
    // Print the log to our OLED screen
    logMoisture();
  }
  delay(1000);
}

// Calc the moisture ratio, return the ratio
// 0 is air
// 100 is water
float calcMoistureRatio() {
  float ratio = ((soilMoistureValue - waterValue) / (airValue - waterValue)) * 100;
  float invertedRatio = 100 - ratio;
  return invertedRatio;
}

String cdata;
// Print stuff on the OLED Screen that concern moisture status
void logMoisture() {
  // Clear the screen from previous values
  display.clearDisplay();
  // Set the biggest size accepted by the screen
  display.setTextSize(4);
  // Set the text color to white
  display.setTextColor(SSD1306_WHITE);
  // Check our ratio if its air like
  if(calcMoistureRatio() < 1) {
    display.setCursor(0,0);
    display.print(F("Air"));
    // Check our ratio if its water like
  } else if (calcMoistureRatio() > 95) {
    display.setCursor(0,0);
    display.print(F("Water"));
    // Print our humidity %
  } else {
    display.setCursor(0,0);
    display.print(F("H%"));
    display.setCursor(60,0);
    display.print(calcMoistureRatio());
  }
  // Display our values
  display.display();
  cdata = calcMoistureRatio();
  nodemcu.println(cdata);
  Serial.println(cdata);
}

void henlo(void) {
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
  // Go for the programm after this delay in MS
  delay(5000);
}
