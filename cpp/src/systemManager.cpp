#include "include/systemManager.hpp"
#include "include/ledActuator.hpp"
#include "temperatureSensor.hpp"
#include <cstring>

systemManager::systemManager(const std::vector<uint8_t>& encodedConfiguration)
    : encodedConfiguration(encodedConfiguration)
{
    // Initialize revision with the first byte of encodedConfiguration, or 0 if empty
    revision = encodedConfiguration.empty() ? 0 : encodedConfiguration[0];
    decodeConfiguration();

    // Initialize three LEDs
    actuators.push_back(new ledActuator());
    actuators.push_back(new ledActuator());
    actuators.push_back(new ledActuator());

    // Initialize temperature sensor with scaling depending on revision
    if (revision == 0) {
        sensors.push_back(new temperatureSensor(1));
    } else if (revision == 1) {
        sensors.push_back(new temperatureSensor(10));
    }
}

// Get sensor by its number
sensor* systemManager::getSensor(uint16_t number) {
    if (number < sensors.size()) {
        return sensors[number];
    }
    return nullptr;
}

// Get actuator by its number
actuator* systemManager::getActuator(uint16_t number) {
    if (number < actuators.size()) {
        return actuators[number];
    }
    return nullptr;
}

const char* systemManager::getSerialnumber() {
    // Return the decoded serial number
    return serialNumber;
}

void systemManager::decodeConfiguration() {
    // encodedConfiguration[0] is revision, [1]..[7] is serial number (max 7 chars)
    std::memset(serialNumber, 0, sizeof(serialNumber));
    if (encodedConfiguration.size() > 1) {
        size_t serialLen = encodedConfiguration.size() - 1;
        if (serialLen > 7) serialLen = 7;
        std::memcpy(serialNumber, &encodedConfiguration[1], serialLen);
    }
}

// Get the hardware revision
uint8_t systemManager::getRevision() {
    return revision;
}