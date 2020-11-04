void setupPersistence() {
  if (!EEPROM.begin(2048)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
}