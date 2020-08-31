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
  }
  // Need to fix the async call time if possible
  // this should be running in parallel
  if(currenState == LOW) {
    blink(2000);
  } else {
    blink(500);
  }
}
