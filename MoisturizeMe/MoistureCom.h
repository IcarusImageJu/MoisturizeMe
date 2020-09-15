#ifndef MOISTURIZE_COM_H
#define MOISTURIZE_COM_H

#include "Moisturizer.h"

class MoistureCom {
  public:
    MoistureCom(int size, Moisturizer *moisturizers):
      size(size),
      moisturizers(moisturizers)
    {}

    void setup() {
      // Serial on the same port of nodemcu
      Serial.begin(115200);
      while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
      }
    }

    void loop() {
      update();
    }

    void update() {
      String value = Serial.readString();
//      When we receive U (as Update) from the serial port
      if(value == 'U'){
        print();
      }
    }

    void print() {
      for (int index = 0; index < size; index++) {
        Moisturizer currentMoisturizer = moisturizers[index];
        Serial.println(currentMoisturizer.print());
      }
    }

  private:
    Moisturizer *moisturizers;
    int size;
};

#endif
