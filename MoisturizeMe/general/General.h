// Includes
#include "Libs.h"
#include "Persistence.h"
#include "WifiConfig.h"
#include "Ota.h"
#include "Mdns.h"
#include "Debug.h"
#include "Mqtt.h"

void sayHello() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void setupGeneral() {
  // Say Hello
  sayHello();
  // Run persistence
  setupPersistence();
  // // Connect WiFi
  setupWificonfig();
  // // OTA
  setupOta();
  // // Register host name in mDNS
  setupMdns();
  // // Debug
  setupDebug();
  // // MQTT
  setupMqtt();
}

void loopGeneral() {
  preLoopDebug();
  loopOta();
  loopMqtt();
  loopDebug();
  // Give a time for ESP
  yield();
  postLoopDebug();
}
