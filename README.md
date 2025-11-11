# oop_assignment2

# SensorSystem – Objektorienterat mätsystem i C++
# Projektbeskrivning
SensorSystem är ett objektorienterat program som simulerar ett mätsystem med flera sensorer. Systemet använder arv och polymorfism för att hantera olika sensortyper (temperatur, luftfuktighet, tryck) och lagrar mätvärden med tidsstämplar. Det stödjer även tröskelbaserade larm som utlöses när ett sensorvärde över- eller underskrider en definierad gräns.

# Klassstruktur
Sensor (abstrakt klass): definierar gränssnittet för alla sensorer.

TemperatureSensor, HumiditySensor, PressureSensor: konkreta sensorer som ärver från Sensor.

Measurement (struct): innehåller sensorvärde, enhet, namn och tidsstämpel.

MeasurementStorage: lagrar och hanterar mätningar, inklusive statistik och filhantering.

Threshold (struct): definierar tröskelregler för larm.

main.cpp: innehåller menyflöde, sensorinstanser, tröskelhantering och larmlogik.


# Funktioner
Samla mätningar från alla sensorer

Visa statistik (medelvärde, min, max, standardavvikelse)

Spara/ladda mätningar till/från fil

Konfigurera tröskelvärden för larm

Visa utlösta larm med tidsstämplar och regelbeskrivning

# Filstruktur
plaintext
SensorSystem/
├── main.cpp
├── sensor.h
├── temperatureSensor.h
├── temperatureSensor.cpp
├── humiditySensor.h
├── humiditySensor.cpp
├── pressureSensor.h
├── pressureSensor.cpp
├── measurement.h
├── measurementStorage.h
├── measurementStorage.cpp
├── threshold.h
├── data.txt                # (skapas vid filsparning)
├── README.md               # (denna fil)
