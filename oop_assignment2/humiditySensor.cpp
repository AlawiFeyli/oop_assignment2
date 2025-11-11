#include "humiditySensor.h"
#include <random>

// Constructor to initialize HumiditySensor with ID and value range
HumiditySensor::HumiditySensor(const std::string& id, double minV, double maxV)
	: id(id), minV(minV), maxV(maxV) {}

double HumiditySensor::read() const {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(minV, maxV);
	return dis(gen);
}

std::string HumiditySensor::getName() const {
	return id;
}

std::string HumiditySensor::getUnit() const {
	return "%";
}
