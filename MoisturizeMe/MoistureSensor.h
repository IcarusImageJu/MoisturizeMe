// Enter the Analog Chan number for the moisture sensor
// [] = {analog input, airValue, waterValue}
class MoistureSensor {
  public:
    MoistureSensor(int pin, int waterValue, int airValue, int minMoistRatio):
      pin(pin),
      waterValue(waterValue),
      airValue(airValue),
      minMoistRatio(minMoistRatio)
      {}
      
    int pin;
    int waterValue;
    int airValue;
    int minMoistRatio;
};