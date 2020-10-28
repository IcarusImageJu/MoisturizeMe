//    debugA("This is a any (always showed) - var %d", var);
//    debugV("This is a verbose - var %d", var);
//    debugD("This is a debug - var %d", var);
//    debugI("This is a information - var %d", var);
//    debugW("This is a warning - var %d", var);
//    debugE("This is a error - var %d", var);

#define HOST_NAME "Moisturizers0"

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

// WiFi credentials
// Note: if commented, is used the smartConfig
// That allow to it in mobile app
// See more details in http://www.iotsharing.com/2017/05/how-to-use-smartconfig-on-esp32.html
#define WIFI_SSID "BELL693"  // your network SSID (name)
#define WIFI_PASS "EF3A7CC4"  // your network key

// MQTT Configuration
const char* mqtt_server = "192.168.2.37";
#define mqtt_port 1883
#define MQTT_CONTROLLERS_STATES_PUB "Moisturizers/controllers/states/0"
#define MQTT_CONTROLLERS_CONFIGS_SUB "Moisturizers/controllers/configs/0"
#define MQTT_VALUES_PUB "Moisturizers/values/0"
WiFiClient wifiClient;
PubSubClient client(wifiClient);

/////// Variables
// Time
uint32_t mTimeToSec = 0;
uint32_t mTimeSeconds = 0;

// Moisturizer
#include "Moisturizer.h"
Moisturizer moisturizer;

////// Setup
void setup() {
  // Initialize the Serial (use only in setup codes)
  Serial.begin(230400);

  // Connect WiFi
  connectWiFi();

  // Host name of WiFi
  #ifdef ESP8266
    WiFi.hostname(HOST_NAME);
  #endif

  // Update over air (OTA)
  #ifdef USE_ARDUINO_OTA
    initializeOTA();
  #endif

  // Register host name in mDNS

  #if defined USE_MDNS && defined HOST_NAME
    if (MDNS.begin(HOST_NAME)) {
      Serial.print("* MDNS responder started. Hostname -> ");
      Serial.println(HOST_NAME);
    }
    // Register the services
    #ifndef DEBUG_DISABLED
      MDNS.addService("telnet", "tcp", 23); // Telnet server of RemoteDebug, register as telnet
    #endif
  #endif // MDNS

  #ifndef DEBUG_DISABLED // Only for development
    // Initialize RemoteDebug
    Debug.begin(HOST_NAME); // Initialize the WiFi server
    //Debug.setPassword("r3m0t0."); // Password for WiFi client connection (telnet or webapp)  ?
    Debug.setResetCmdEnabled(true); // Enable the reset command
    Debug.showProfiler(true); // Profiler (Good to measure times, to optimize codes)
    Debug.showColors(true); // Colors
    // Debug.setSerialEnabled(true); // if you wants serial echo - only recommended if ESP is plugged in USB
    // Project commands
    String helpCmd = "bench1 - Benchmark 1\n";
    helpCmd.concat("bench2 - Benchmark 2");
    Debug.setHelpProjectsCmds(helpCmd);
    Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
    // End of setup - show IP
    Serial.println("* Arduino RemoteDebug Library");
    Serial.println("*");
    Serial.print("* WiFI connected. IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("*");
    Serial.println("* Please use the telnet client (telnet for Mac/Unix or putty and others for Windows)");
    Serial.println("* or the RemoteDebugApp (in browser: http://joaolopesf.net/remotedebugapp)");
    Serial.println("*");
    Serial.println("* This sample will send messages of debug in all levels.");
    Serial.println("*");
    Serial.println("* Please try change debug level in client (telnet or web app), to see how it works");
    Serial.println("*");
  #endif
  
  // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
  mqttReconnect();

}

void loop() {
  #ifndef DEBUG_DISABLED
    // Time of begin of this loop
    uint32_t timeBeginLoop = millis();
  #endif
  client.loop();

  // Moisturizers
  moisturizer.loop();

  ////// Services on Wifi

  #ifdef USE_ARDUINO_OTA
    // Update over air (OTA)
    ArduinoOTA.handle();
  #endif

  #ifndef DEBUG_DISABLED
    // RemoteDebug handle (for WiFi connections)
    Debug.handle();
  #endif

  // Give a time for ESP
  yield();

  #ifndef DEBUG_DISABLED
    // Show a debug - warning if time of these loop is over 50 (info) or 100 ms (warning)
    uint32_t time = (millis() - timeBeginLoop);
    if (time > 100) {
      debugI("* Time elapsed for the loop: %u ms.", time);
    } else if (time > 200) {
      debugW("* Time elapsed for the loop: %u ms.", time);
    }
  #endif
}

void mqttReconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    debugI("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = HOST_NAME;
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_CONTROLLERS_STATES_PUB, 0, true, "{\"online\": false}")) {
      debugI("MQTT connected");
      //Once connected, publish an announcement...
      client.publish(MQTT_CONTROLLERS_STATES_PUB, "{\"online\": true}");
      // ... and resubscribe
      client.subscribe(MQTT_CONTROLLERS_CONFIGS_SUB);
    } else {
      debugW("failed, rc=", client.state());
      debugW("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte *payload, unsigned int length) {
    payload[length] = '\0';
    String content = String((char*)payload);
  
    debugI("-------new message from broker-----");
    debugI("topic: %s", topic);
    debugI("payload: %d", payload);
    debugI("content: %s", content.c_str());
    debugI("length: %d", length);
    moisturizer.config(content);
}

#ifndef DEBUG_DISABLED
  // Process commands from RemoteDebug
  void processCmdRemoteDebug() {
    String lastCmd = Debug.getLastCommand();
    if (lastCmd == "bench1") {
      // Benchmark 1 - Printf
      debugA("* Benchmark 1 - one Printf");
      uint32_t timeBegin = millis();
      uint8_t times = 50;
      for (uint8_t i = 1; i <= times; i++) {
        debugA("%u - 1234567890 - AAAA", i);
      }
      debugA("* Time elapsed for %u printf: %ld ms.\n", times,
            (millis() - timeBegin));
    } else if (lastCmd == "bench2") {
      // Benchmark 2 - Print/println
      debugA("* Benchmark 2 - Print/Println");
      uint32_t timeBegin = millis();
      uint8_t times = 50;
      for (uint8_t i = 1; i <= times; i++) {
        if (Debug.isActive(Debug.ANY)) {
          Debug.print(i);
          Debug.print(" - 1234567890");
          Debug.println(" - AAAA");
        }
      }
      debugA("* Time elapsed for %u printf: %ld ms.\n", times,
            (millis() - timeBegin));
    }
  }
#endif

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

/////////// End
