#pragma once
#include "sensor.h"
#include <string>

// HumiditySensor class inheriting from Sensor
class HumiditySensor : public Sensor {
public:
	HumiditySensor(const std::string& id, double minV, double maxV);
	double read() const override;
	std::string getName() const override;
	std::string getUnit() const override;

private:
	std::string id;
	double minV, maxV;
};
