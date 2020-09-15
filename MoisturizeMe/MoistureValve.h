#ifndef MOISTURE_VALVE_H
#define MOISUTRE_VALVE_H

class MoistureValve {
    public:
        MoistureValve(int pin, unsigned long valveTimer):
            pin(pin),
            valveTimer(valveTimer)
            {}

        void setup() {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, HIGH);
            state = CLOSED;
        }

        void loop() {
            switch (state){
                case CLOSED:
                    digitalWrite(pin, HIGH);
                    break;
                case OPEN:
                    digitalWrite(pin, LOW);
                    if ((unsigned long)(checkTimer <= millis())) {
                      state = CLOSED;
                      checkTimer = millis() + allowCheckTimer;
                    }
                    break;
            }
        }

        void watering() {
            if(isAllowed == ALLOWED && state == CLOSED) {
              state = OPEN;
              isAllowed = NOT_ALLOWED;
              checkTimer = millis() + valveTimer;
            } else if((unsigned long)(checkTimer + valveTimer <= millis())) {
              isAllowed = ALLOWED;
            }
        }

        bool isWatering() {
          return !digitalRead(pin);
        }

        String print() {
          data = "V";
          data += pin;
          data += ":";
          data += !digitalRead(pin);
          return data;
        }

    private:
        enum State {
            OPEN = 0,
            CLOSED = 1
        } state;
        int pin;
        String data;
        unsigned long valveTimer = 2000;
        unsigned long checkTimer;
//      Allow to water the plant every hour (1 * 60 * 60 * 1000) = 3.600.000
        unsigned long allowCheckTimer = 3600000;

        enum IsAllowed {
            ALLOWED = 0,
            NOT_ALLOWED = 1,
        } isAllowed = ALLOWED;
};

#endif
