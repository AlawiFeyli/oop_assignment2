#include "temperatureSensor.h"
#include <random>

// Constructor to initialize TemperatureSensor with ID and value range
TemperatureSensor::TemperatureSensor(const std::string& id, double minV, double maxV)
    : id(id), minV(minV), maxV(maxV) {
}

double TemperatureSensor::read() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minV, maxV);
    return dist(gen);
}

std::string TemperatureSensor::getName() const {
    return id;
}

std::string TemperatureSensor::getUnit() const {
    return "*C";
}
