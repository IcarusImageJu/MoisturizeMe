#ifdef USE_ARDUINO_OTA
  // Initialize o Arduino OTA
  void initializeOTA() {
    // TODO: option to authentication (password)
    #if defined ESP8266
      ArduinoOTA.onStart([]() {
        Serial.println("* OTA: Start");
      });
      ArduinoOTA.onEnd([]() {
        Serial.println("\n*OTA: End");
      });
      ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("*OTA: Progress: %u%%\r", (progress / (total / 100)));
      });
      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("*OTA: Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });
    #elif defined ESP32
      // ArduinoOTA
      ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
          type = "sketch";
        else // U_SPIFFS
          type = "filesystem";
          Serial.println("Start updating " + type);
        }).onEnd([]() {
        Serial.println("\nEnd");
      }).onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      }).onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });
    #endif
    // Begin
    ArduinoOTA.begin();
  }
#endif

void setupOta() {
    // Update over air (OTA)
    #ifdef USE_ARDUINO_OTA
        initializeOTA();
    #endif
}

void loopOta() {
  #ifdef USE_ARDUINO_OTA
    // Update over air (OTA)
    ArduinoOTA.handle();
  #endif
}