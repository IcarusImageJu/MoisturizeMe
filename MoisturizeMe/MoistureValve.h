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
                    if (checkTimer <= millis()) {
                      state = CLOSED;
                      checkTimer = millis() + allowCheckTimer;
                    }
                    break;
            }
        }

        void watering() {
            if(isAllowed == ALLOWED) {
              state = OPEN;
              isAllowed = NOT_ALLOWED;
              checkTimer = millis() + valveTimer;
            } else if(checkTimer + valveTimer <= millis()) {
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
//      Allow to water the plant every hour
        unsigned long allowCheckTimer = 1 * 60 * 60 * 1000;


        enum IsAllowed {
            ALLOWED = 0,
            NOT_ALLOWED = 1,
        } isAllowed = ALLOWED;
};

#endif
