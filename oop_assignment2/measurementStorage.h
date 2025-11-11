#pragma once
#include "measurement.h"
#include <vector>
#include <string>

// Class to store and manage measurements
class MeasurementStorage {
private:
	// Vector to hold all measurements
    std::vector<Measurement> measurements;

public: 
    void addMeasurement(const Measurement& m);
    void printAll() const;
    void printStatistics(const std::string& sensorName) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
