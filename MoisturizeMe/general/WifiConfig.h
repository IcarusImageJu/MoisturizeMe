// WiFi credentials
// Note: if commented, is used the smartConfig
// That allow to it in mobile app
// See more details in http://www.iotsharing.com/2017/05/how-to-use-smartconfig-on-esp32.html
#include "WifiCredentials.h"
#ifndef WIFI_SSID
  #define WIFI_SSID "SSID"  // your network SSID (name)
#endif
#ifndef WIFI_PASS
  #define WIFI_PASS "PASSWORD"  // your network key
#endif

WiFiClient wifiClient;

////// WiFi
void connectWiFi() {
  ////// Connect WiFi
  #ifdef EM_DEPURACAO
    Serial.println("*** connectWiFi: begin conection ...");
  #endif
  #ifdef ESP32
    // ESP32 // TODO: is really necessary ?
    WiFi.enableSTA(true);
    delay(100);
  #endif
  // Connect with SSID and password stored
  #ifndef WIFI_SSID
    WiFi.begin();
  #else
    WiFi.begin(WIFI_SSID, WIFI_PASS);
  #endif
  // Wait connection
  uint32_t timeout = millis() + 20000; // Time out
  while (WiFi.status() != WL_CONNECTED && millis() < timeout) {
    delay(250);
    Serial.print(".");
  }
  // Not connected yet?
  if (WiFi.status() != WL_CONNECTED) {
    #ifndef WIFI_SSID
      // SmartConfig
      WiFi.beginSmartConfig();
      // Wait for SmartConfig packet from mobile
      Serial.println("connectWiFi: Waiting for SmartConfig.");
      while (!WiFi.smartConfigDone()) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.println("connectWiFi: SmartConfig received.");
      // Wait for WiFi to connect to AP
      Serial.println("connectWiFi: Waiting for WiFi");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
    #else
        Serial.println("Not possible connect to WiFi, rebooting");
        ESP.restart();
    #endif
  }
  // End
  Serial.println("");
  Serial.print("connectWiFi: connect a ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP().toString());
}

void setupWificonfig() {
    connectWiFi();
    // Host name of WiFi
    #ifdef ESP8266
        WiFi.hostname(HOST_NAME);
    #endif
}

