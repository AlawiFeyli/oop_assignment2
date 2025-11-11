#include "measurementStorage.h"
#include <iostream> 
#include <iomanip>
#include <fstream> 
#include <sstream> 
#include <cmath>
#include <limits>

// Adds a new measurement to the storage
void MeasurementStorage::addMeasurement(const Measurement& m) {
    measurements.push_back(m);
}
// Prints all measurements to the console
void MeasurementStorage::printAll() const {
    for (const auto& m : measurements) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << m.timestamp << ", " << m.sensorName << ", " << m.value << " " << m.unit << std::endl;
    }
}
// Prints statistics (min, max, average) for a specific sensor
void MeasurementStorage::printStatistics(const std::string& sensorName) const {
    std::vector<double> values;
    std::string unit;

    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            values.push_back(m.value);
            unit = m.unit;
        }
    }

    if (values.empty()) {
        std::cout << "No measurements for sensor: " << sensorName << std::endl;
        return;
    }

    double sum = 0.0;
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();

    for (double v : values) {
        sum += v;
        if (v < minVal) minVal = v;
        if (v > maxVal) maxVal = v;
    }

    double mean = sum / values.size();

    double variance = 0.0;
    for (double v : values) {
        variance += (v - mean) * (v - mean);
    }
    double stddev = std::sqrt(variance / values.size());

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Statistics for sensor: " << sensorName << std::endl;
    std::cout << "Number of measurements: " << values.size() << std::endl;
    std::cout << "Mean: " << mean << " " << unit << std::endl;
    std::cout << "Min: " << minVal << " " << unit << std::endl;
    std::cout << "Max: " << maxVal << " " << unit << std::endl;
    std::cout << "Standard deviation: " << stddev << " " << unit << std::endl;
}
// Saves all measurements to a file
void MeasurementStorage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for writing.\n";
        return;
    }

    for (const auto& m : measurements) {
        file << m.timestamp << ", " << m.sensorName << ", " << m.value << ", " << m.unit << "\n";
    }

    file.close();
    std::cout << "Measurement data saved to " << filename << std::endl;
}
// Loads measurements from a file
void MeasurementStorage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestamp, name, valueStr, unit;

        if (std::getline(ss, timestamp, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, valueStr, ',') &&
            std::getline(ss, unit)) {

            try {
                double value = std::stod(valueStr);
                measurements.push_back({ name, unit, value, timestamp });
            }
            catch (...) {
                std::cerr << "Wrong line ignored; " << line << std::endl;
            }
        }
    }

    file.close();
    std::cout << "Measurement data loaded from " << filename << std::endl;
}
