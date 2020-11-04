#define HOST_NAME "MoisturizeMe0"
// General
#include "general/General.h"
// Moisturizer
#include "Moisturizer.h"
Moisturizer moisturizer;

////// Setup
void setup() {
  // Initialize the Serial (use only in setup codes)
  Serial.begin(230400);
  // Init Setup for general libs
  setupGeneral();
  // Moisturizers
  moisturizer.setup();
}

void loop() {
  // Loop for general libs
  loopGeneral();
  // Moisturizers
  moisturizer.loop();
}

/////////// End
