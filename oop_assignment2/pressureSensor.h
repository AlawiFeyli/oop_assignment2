#pragma once
#include "sensor.h"
#include <string>

// PressureSensor class inheriting from Sensor
class PressureSensor : public Sensor {
public:
	PressureSensor(const std::string& id, double minV, double maxV);
	double read() const override;
	std::string getName() const override;
	std::string getUnit() const override;

private:
	std::string id;
	double minV, maxV;
};
