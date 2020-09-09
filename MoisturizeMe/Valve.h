class Valve {
    const int pin;
    enum State {
        OPEN = 0,
        CLOSED = 1
    } state;
    public:
        Valve(int pin):
            pin(pin)
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
                    delay(2000);
                    state = CLOSED;
                    break;
            }
        }

        void watering() {
            state = OPEN;
        }
};
