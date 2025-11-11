#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "sensor.h"
#include "temperatureSensor.h"
#include "humiditySensor.h"
#include "pressureSensor.h"
#include "measurement.h"
#include "measurementStorage.h"
#include "threshold.h"

// Function to get current timestamp as string
std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_struct;
    localtime_s(&tm_struct, &now_c);
    std::stringstream ss;
    ss << std::put_time(&tm_struct, "%Y-%m-%d %H:%M");
    return ss.str();
}
//  Function to display menu
void showMenu() {
    std::cout << "\n--- MENU ---\n";
    std::cout << "1. Add Measurement\n";
    std::cout << "2. Show statistics for a Sensor\n";
    std::cout << "3. Show all Measurements\n";
    std::cout << "4. Save Measurements to File\n";
    std::cout << "5. Load Measurements from File\n";
    std::cout << "6. Configure Threshold Alarm\n";
    std::cout << "7. Show Triggered Alarms\n";
    std::cout << "8. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
	// Create sensors
    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<TemperatureSensor>("t1", 18.0, 24.0));
    sensors.push_back(std::make_unique<HumiditySensor>("h1", 30.0, 60.0));
    sensors.push_back(std::make_unique<PressureSensor>("p1", 980.0, 1050.0));

	// Create measurement storage
    MeasurementStorage storage;
    std::map<std::string, Threshold> thresholds;
    std::vector<Measurement> triggeredAlarms;

    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            for (const auto& sensor : sensors) {
                double value = sensor->read();
                std::string name = sensor->getName();
                std::string unit = sensor->getUnit();
                std::string timestamp = getCurrentTimestamp();

                storage.addMeasurement({ name, unit, value, timestamp });

                if (thresholds.count(name)) {
                    const auto& rule = thresholds[name];
                    if ((rule.over && value > rule.limit) || (!rule.over && value < rule.limit)) {
                        triggeredAlarms.push_back({ name, unit, value, timestamp });
                    }
                }
            }
            std::cout << "Measurements added.\n";
            break;
        }
        case 2: {
            std::string sensorName;
            std::cout << "Temperature = t1\n";
			std::cout << "Humidity    = h1\n";
			std::cout << "Pressure    = p1\n";
			std::cout << "Enter sensor name - t1/h1/p1: ";
            std::cin >> sensorName;
            storage.printStatistics(sensorName);
            break;
        }
        case 3:
            storage.printAll();
            break;
        case 4:
            storage.saveToFile("data.txt");
            break;
        case 5:
            storage.loadFromFile("data.txt");
            break;
        case 6: {
            std::string name;
            double limit;
            char direction;
            std::cout << "Enter sensor name, t1/h1/p1: ";
            std::cin >> name;
            std::cout << "Enter threshold value: ";
            std::cin >> limit;
            std::cout << "Trigger alarm when value is (o)ver or (u)nder the limit? ";
            std::cin >> direction;
            thresholds[name] = { name, limit, direction == 'o' };
            break;
        }
        case 7: {
            if (triggeredAlarms.empty()) {
                std::cout << "No alarms triggered.\n";
            }
            else {
                for (const auto& alarm : triggeredAlarms) {
                    const auto& rule = thresholds[alarm.sensorName];
                    std::string ruleText = rule.over ? ">" : "<";
                    std::cout << alarm.timestamp << " | " << alarm.sensorName << " | "
                        << alarm.value << " " << alarm.unit << " | Rule: value "
                        << ruleText << " " << rule.limit << "\n";
                }
            }
            break;
        }
        case 8:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
