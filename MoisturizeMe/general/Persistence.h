void setupPersistence() {
  if (!EEPROM.begin(2048)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
}

unsigned long delayBeforeRestarting = 10000;
unsigned long configTimer;
int address = 0;

void loopPersistence() {
  if(configTimer <= millis()) {
    // commit the new values
    // EEPROM.commit();
    // restart
    // ESP.restart();
  }
}

void configController(char* topic, String content) {
  // callback for controller Id
    if(strcmp(topic, "id") == 0) {
      debugI("Match id");
    }
    // callback for controller wifiSSid
    if(strcmp(topic, "wifiSSid") == 0) {
      debugI("Match ssid");
    }
    // callback for controller wifiPass
    if(strcmp(topic, "wifiPass") == 0) {
      debugI("Match pass");
    }
    // callback for controller mqttServer
    if(strcmp(topic, "mqttServer") == 0) {
      debugI("Match mqtt");
    }
    // callback for controller name
    if(strcmp(topic, "name") == 0) {
      debugI("Match name");
    }
}

void configMoisturizer(char* topic, String content) {

  configTimer = millis() + delayBeforeRestarting;
}