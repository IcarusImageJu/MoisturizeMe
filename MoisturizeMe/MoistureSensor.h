// Enter the Analog Chan number for the moisture sensor
// [] = {analog input, airValue, waterValue}
class MoistureSensor {
  public:
    MoistureSensor(int pin, int waterValue, int airValue):
      pin(pin),
      waterValue(waterValue),
      airValue(airValue)
      {}
      
    int pin;
    int waterValue;
    int airValue;
};