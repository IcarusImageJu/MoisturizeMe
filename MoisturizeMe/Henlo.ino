// Moisturize Me Config
String const VERSION_NAME = "v0.3.0";

void henlo(void) {
  // Clear the screen from previous values
  display.clearDisplay();
  // Set a text size
  display.setTextSize(2);
  // Set the text color to white
  display.setTextColor(SSD1306_WHITE);
  // Set our cursor to the starting point
  display.setCursor(0,0);
  // Print on 1st line
  display.print(F("Moisturize"));
  // Print on 2nd line
  display.print(F("Me"));
  // Print version
  display.setTextSize(1);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(60, (SCREEN_HEIGHT / 2) + 6);
  display.print(VERSION_NAME);
  // Display our values
  display.display();
  // Go for the programm after this delay in MS
  delay(5000);
}