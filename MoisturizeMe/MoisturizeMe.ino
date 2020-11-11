#define HOST_NAME "MoisturizeMe0"
byte changed = 0;
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
  // Config called
  if (changed == 1) {
    // Reset changed to 0
    changed = 0;
    moisturizer.config();
  }
}

void loop() {
  // Loop for general libs
  loopGeneral();
  // Moisturizers
  moisturizer.loop();
}

/////////// End
