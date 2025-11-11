#pragma once
#include <string>

// Abstract Sensor class
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual double read() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getUnit() const = 0;
};
