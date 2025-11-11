#pragma once
#include <string>

// Structure to define threshold rules for sensors
struct Threshold {
    std::string sensorName;
    double limit;
    bool over;
};
