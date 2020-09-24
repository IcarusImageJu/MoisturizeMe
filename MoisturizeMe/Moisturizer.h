#ifndef MOISTURIZER_H
#define MOISTURIZER_H

#include "MoistureSensor.h";
#include "MoistureValve.h";

class Moisturizer {
    MoistureValve moistureValve;
    MoistureSensor moistureSensor;
    public:
        Moisturizer(int sensorPin, int waterValue, int airValue, int minMoistRatio, int valvePin, unsigned long valveTimer):
            moistureValve(valvePin, valveTimer),
            moistureSensor(sensorPin, waterValue, airValue, minMoistRatio)
        {}

        void setup() {
            moistureValve.setup();
        }

        void loop() {
            moistureValve.loop();
            if((bool)moistureSensor.askWatering()) {
                moistureValve.watering();
            }
        }

        String humidity() {
          return String(moistureSensor.getValue());
        }

        bool askWatering() {
          return moistureSensor.askWatering();
        }

        bool isWatering() {
          return moistureValve.isWatering();
        }

        void waterItNow() {
          return moistureValve.waterItNow();
        }

        String print() {
          data = "";
          data += moistureSensor.print();
          data += ",";
          data += moistureValve.print();
          return data;
        }
    private:
      String data;
};

#endif
