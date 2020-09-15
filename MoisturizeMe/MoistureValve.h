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
                      Serial.println(F("here"));
                      checkTimer = millis() + allowCheckTimer;
                      Serial.println(checkTimer);
                      Serial.println(allowCheckTimer);
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
              Serial.println(F("check this"));
              Serial.println(checkTimer);
              Serial.println(millis());
              isAllowed = ALLOWED;
            }
        }

        String print() {
          data = "V";
          data += pin;
          data += ":";
          data += state;
          return data;
        }

        enum State {
            OPEN = 0,
            CLOSED = 1
        } state;

    private:
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
