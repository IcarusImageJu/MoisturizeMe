const byte cable = 7;
const byte boardLed = LED_BUILTIN;
byte lastState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(cable, INPUT_PULLUP);
  pinMode(boardLed, OUTPUT);
}

void loop() {
  byte currenState = !digitalRead(cable);
  if(currenState != lastState) {
    lastState = currenState;
    Serial.println(currenState == LOW ? "Not connected" : "Connected");
    digitalWrite(boardLed, currenState == LOW ? LOW : HIGH);
  }
  delay(1);
}
