#include "Moisturizer.h"
#include "MoistureScreen.h"

// IO Config
// Enter the digital chan number for the light relay
#define LIGHT_OUTPUT 4

Moisturizer moisturizer0(0, 282, 591, 40, 7, 2000);
Moisturizer moisturizer1(1, 288, 590, 40, 6, 2000);
Moisturizer moisturizer2(2, 291, 592, 40, 5, 2000);
int const size = 3;
Moisturizer moisturizers[size] = {moisturizer0, moisturizer1, moisturizer2};
MoistureScreen moistureScreen(size, moisturizers);

void setup() {
  // Serial on the same port of nodemcu
  Serial.begin(115200);
  // Setup our Screen
  moistureScreen.setup();
  // Setup our moisturizers
  moisturizer0.setup();
  moisturizer1.setup();
  moisturizer2.setup();
  // Set the pin for the light in OUTPUT mode
  pinMode(LIGHT_OUTPUT, OUTPUT);
  // and keep it not lit durint init
  digitalWrite(LIGHT_OUTPUT, HIGH);
}

void loop() {
  moisturizer0.loop();
  moisturizer1.loop();
  moisturizer2.loop();
  moistureScreen.loop();
}
