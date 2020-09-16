#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "credentials.h"

/* Set these to your desired credentials. */
// char ssid[] = "XXX"; //Enter your WIFI ssid
// char pass[] = "XXX"; //Enter your WIFI password
// char auth[] = "XXX"; //Enter your Blynk auth code
BlynkTimer timer; // Announcing the timer

String data;

WidgetLED ledAsk0(V3);
WidgetLED ledAsk1(V4);
WidgetLED ledAsk2(V5);
WidgetLED ledWatering0(V6);
WidgetLED ledWatering1(V7);
WidgetLED ledWatering2(V8);


void update() {
  Serial.println(F("U"));
  data = Serial.readString();
//  humidity sensors data
  Blynk.virtualWrite(V0, data.substring(3, 7));
  Blynk.virtualWrite(V1, data.substring(23, 28));
  Blynk.virtualWrite(V2, data.substring(43, 48));
//  Sensors ask watering
  data.substring(12, 13) == "1" ? ledAsk0.on() : ledAsk0.off();
  data.substring(32, 33) == "1" ? ledAsk1.on() : ledAsk1.off();
  data.substring(52, 53) == "1" ? ledAsk2.on() : ledAsk2.off();
//  Is watering
  data.substring(17, 18) == "1" ? ledWatering0.on() : ledWatering0.off();
  data.substring(37, 38) == "1" ? ledWatering1.on() : ledWatering1.off();
  data.substring(57, 58) == "1" ? ledWatering2.on() : ledWatering2.off();
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, update);
}

void loop()
{
  Blynk.run();
  timer.run();
}
