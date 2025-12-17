#ifndef EEPROM_READER_H
#define EEPROM_READER_H

#include <vector>
#include <cstdint>

class eepromReader { // This is actually just a mock for EEPROM reading
public:
    eepromReader() = default;
    ~eepromReader() = default;

    std::vector<uint8_t> readConfiguration();
};

#endif // EEPROM_READER_H