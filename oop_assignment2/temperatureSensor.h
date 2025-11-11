#pragma once
#include "sensor.h"
#include <string>

// TemperatureSensor class inheriting from Sensor
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(const std::string& id, double minV, double maxV);
    double read() const override;
    std::string getName() const override;
    std::string getUnit() const override;

private:
    std::string id;
    double minV, maxV;
};
