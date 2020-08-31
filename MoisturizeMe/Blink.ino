void blink(int time) {
    digitalWrite(boardLed, LOW);
    delay(time);
    digitalWrite(boardLed, HIGH);
    delay(time);
}
