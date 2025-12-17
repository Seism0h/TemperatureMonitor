#include "include/hardwareInterfaces.h"
#include "include/systemDefinition.h"

extern volatile adcValue_t tempSensor;
extern volatile bitValue_t ledGreen;
extern volatile bitValue_t ledYellow;
extern volatile bitValue_t ledRed;
extern hwSpecUnion_t hwSpecUnion;

// Sets the state of the specified LED
void setLED(uint8_t number, ledRequest_t request) {
    // 0 = green, 1 = yellow, 2 = red
    switch (number) {
        case 0:
            ledGreen.value = request.state;
            break;
        case 1:
            ledYellow.value = request.state;
            break;
        case 2:
            ledRed.value = request.state;
            break;
        default:
            // Invalid actuator number
            break;
    }
}

// Reads the temperature sensor value and adjusts based on hardware revision
void readTempSensor(temperatureSensor_t* sensor) {
    if (hwSpecUnion.spec.rev == 0) {
        sensor->value = (int16_t)(tempSensor.value);
    } else if (hwSpecUnion.spec.rev == 1) {
        sensor->value = (int16_t)(tempSensor.value / 10);
    }
}
// Reads the state of the specified LED
void readLEDState(ledState_t* led, uint8_t number) {
    if (!led) return;
    switch (number) {
        case 0:
            led->state = ledGreen.value;
            break;
        case 1:
            led->state = ledYellow.value;
            break;
        case 2:
            led->state = ledRed.value;
            break;
        default:
            led->state = false;
            break;
    }
}

// Reads hardware specifications from EEPROM
void eepromRead(uint8_t* dest) {
    uint8_t sampleData[8] = {1, 'A', 'B', 'C', '1', '2', '3', '4'};
    for (int i = 0; i < 8; ++i) {
        dest[i] = sampleData[i];
    }
}