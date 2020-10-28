#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H

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

		void loop() {

		}

		float getValue() {
			return 100 - (((currentValue() - waterValue) / (airValue - waterValue)) * 100);
		}

		bool askWatering() {
			bool ask = getValue() < minMoistRatio;
			return ask;
		}

    float currentValue() {
      return analogRead(pin);
    }

	protected:
		

	private:
		String data;
		
};

#endif
