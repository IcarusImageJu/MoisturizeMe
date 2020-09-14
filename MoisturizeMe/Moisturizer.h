#ifndef MOISTURIZER_H
#define MOISTURIZER_H

#include "MoistureSensor.h";
#include "Valve.h";

class Moisturizer {
    Valve valve;
    MoistureSensor moistureSensor;
    public:
        Moisturizer(int sensorPin, int waterValue, int airValue, int minMoistRatio, int valvePin, unsigned long valveTimer):
            valve(valvePin, valveTimer),
            moistureSensor(sensorPin, waterValue, airValue, minMoistRatio)
        {}

        void setup() {
            valve.setup();
        }

        void loop() {
            valve.loop();
            if(moistureSensor.askWatering()) {
                valve.watering();
            }
        }
};

#endif
