// Board especific librarieson
#if defined ESP8266 || defined ESP32
  #define USE_MDNS true
  #define USE_ARDUINO_OTA true
#else
  #error "The board must be ESP8266 or ESP32"
#endif // ESP

////// Includes
#if defined ESP8266
  // Includes of ESP8266
  #include <ESP8266WiFi.h>
  #ifdef USE_MDNS
    #include <DNSServer.h>
    #include <ESP8266mDNS.h>
  #endif
  #ifdef WEB_SERVER_ENABLED
    #include <ESP8266WebServer.h>
  #endif
#elif defined ESP32
// Includes of ESP32
  #include <WiFi.h>
  #ifdef USE_MDNS
    #include <DNSServer.h>
    #include "ESPmDNS.h"
  #endif
#else
#error "For now, RemoteDebug support only boards Espressif, as ESP8266 and ESP32"
#endif // ESP

// Arduino OTA
#ifdef USE_ARDUINO_OTA
  #include <ArduinoOTA.h>
#endif

// EEPROM
#include "EEPROM.h"

//#define DEBUG_DISABLED true
//#define DEBUG_DISABLE_AUTO_FUNC true
//#define WEBSOCKET_DISABLED true

#ifndef WEBSOCKET_DISABLED // Only if Web socket enabled (RemoteDebugApp)
  //#define WEBSOCKET_PORT 8232
  //#define USE_LIB_WEBSOCKET true
#endif

// Include libraries
#include "RemoteDebug.h"        //https://github.com/JoaoLopesF/RemoteDebug
#ifndef DEBUG_DISABLED // Only if debug is not disabled (for production/release)
  // Instance of RemoteDebug
    RemoteDebug Debug;
#endif
#include <PubSubClient.h>
