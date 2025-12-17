#include "include/eepromReader.hpp"

std::vector<uint8_t> eepromReader::readConfiguration() {
    // First byte is 0 (revision), next 7 bytes are 'A', 'B', 'C', '1', '2', '3', '4'
    return {static_cast<uint8_t>(0), 'A', 'B', 'C', '1', '2', '3', '4'}; // Revision 0, Serial "ABC1234", Revision 0 uses scaling factor 1, Revision 1 would use scaling factor 10
}