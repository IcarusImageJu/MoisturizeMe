#ifndef MOISTURIZER_H
#define MOISTURIZER_H

#include <ArduinoJson.h>
StaticJsonDocument<200> doc;

#include "MoistureSensor.h";
#include "MoistureValve.h";

class Moisturizer {
    public:
        Moisturizer() {
        }

        void setup() {
          
        }

        void loop() {

        }

        void config(String content) {
          pinMode(LED_BUILTIN, OUTPUT);
          delay(500);
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN, LOW);
//          ESP.restart();
        }

        JsonArray print() {
//          char buffer[256];
//          size_t n = serializeJson(doc, buffer);
//          debugA("hey - pub %d", buffer);
//          client.publish(MQTT_VALUES_PUB, buffer, n);
//          doc["raw"] = raw();
//          doc["value"] = humidity();
        }
};

#endif
