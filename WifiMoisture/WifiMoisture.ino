#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

/* Set these to your desired credentials. */
// char ssid[] = "XXX"; //Enter your WIFI ssid
// char pass[] = "XXX"; //Enter your WIFI password
// char auth[] = "XXX"; //Enter your Blynk auth code

//BLYNK_READ(V0)
//{
//  
//  // This command writes Arduino's uptime in seconds to Virtual Pin (5)
//  String value = Serial.readString();
//  Serial.println(value);
//  Blynk.virtualWrite(V0, Serial.readString());
//}


void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(16, OUTPUT);
//  Blynk.begin(auth, ssid, pass);
}

void loop()
{
//  Blynk.run();
  Serial.println(F("U"));
  delay(2000);
}
