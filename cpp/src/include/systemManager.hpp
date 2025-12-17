#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include <cstdint>
#include "sensor.hpp"
#include "actuator.hpp"

class systemManager {
private:
    std::vector<uint8_t> encodedConfiguration; // copy the encoded configuration locally into our class, in case we need it later. So we do not have to query the eeprom again.

    // List of sensors
    std::vector<sensor*> sensors;

    // List of actuators
    std::vector<actuator*> actuators;

    // Fixed-length serial number as a character array (7 characters)
    char serialNumber[7]{};

    // One-byte unsigned int for revision
    uint8_t revision{0};

    void decodeConfiguration();

public:
    systemManager(const std::vector<uint8_t>& encodedConfiguration);
    ~systemManager() {
        for (auto* s : sensors) delete s;
        for (auto* a : actuators) delete a;
    }

    sensor* getSensor(uint16_t number); // Better: use some other qualifier besides the number
    actuator* getActuator(uint16_t number);
    const char* getSerialnumber();
    uint8_t getRevision(); 
};

#endif // SYSTEM_MANAGER_H