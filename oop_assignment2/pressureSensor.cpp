#include "pressureSensor.h"
#include <random>

// Constructor to initialize PressureSensor with ID and value range
PressureSensor::PressureSensor(const std::string& id, double minV, double maxV)
	: id(id), minV(minV), maxV(maxV) {
}

double PressureSensor::read() const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(minV, maxV);
	return dis(gen);
}

std::string PressureSensor::getName() const {
	return id;
}

std::string PressureSensor::getUnit() const {
	return "Pa";
}
