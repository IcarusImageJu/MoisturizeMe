#ifndef MOISTURIZER_H
#define MOISTURIZER_H

#include <ArduinoJson.h>
#include "MoistureSensor.h";
#include "MoistureValve.h";

class Moisturizer {
    public:
        Moisturizer() {
        }

        void setup() {
//          DynamicJsonDocument doc(2048);
//          String configString = EEPROM.readString(0);
//          debugA("Yo %d", configString );
//          // {"_id":"0","controller":{"id":0,"wifiSSid":"BELL693","wifiPass":"EF3A7CC4","mqttServer":"192.168.2.37","name":"Controller test"},"moisturizers":[{"id":0,"sensorPin":36,"waterValue":1000,"airValue":3450,"minMoistRatio":30,"valvePin":39,"valveTimer":2500,"name":"Moisturizer test"}]}
//          if(sizeof(configString) > 0) {
//            deserializeJson(doc, configString);
//            JsonObject config = doc.as<JsonObject>();
//            moisturizers = config["moisturizers"].as<JsonArray>();
//            }
        }

        void loop() {
          if(millis() - targetTime >= PERIOD) {
            targetTime += PERIOD;
            for(JsonVariant moisturizer: moisturizers) {
              MoistureSensor sensor(moisturizer["sensorPin"].as<int>(), moisturizer["waterValue"].as<int>(), moisturizer["airValue"].as<int>(), moisturizer["minMoistRatio"].as<int>());
              debugA("HEY %d", sensor.currentValue() );
            }
          }
        }

        void config(String content) {
          pinMode(LED_BUILTIN, OUTPUT);
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
          digitalWrite(LED_BUILTIN, LOW);
//          EEPROM.writeString(0, content);
          setup();
        }

        JsonArray print() {
//          char buffer[256];
//          size_t n = serializeJson(doc, buffer);
//          debugA("hey - pub %d", buffer);
//          client.publish(MQTT_VALUES_PUB, buffer, n);
//          doc["raw"] = raw();
//          doc["value"] = humidity();
        }
        
    private:
      JsonArray moisturizers;
      unsigned long PERIOD = 1*60*1000UL;
      unsigned long targetTime = 0UL;
};

#endif
