#include "include/temperatureMonitor.h"
#include "include/systemDefinition.h"
#include "include/hardwareInterfaces.h"
#include <stdio.h>
#include <unistd.h>     // for usleep
#include <termios.h>    // for terminal control
#include <fcntl.h>      // for non-blocking input>
#include <pthread.h>    // for threading

// Externally defined variables
extern volatile adcValue_t tempSensor;
extern volatile bitValue_t ledGreen;
extern volatile bitValue_t ledYellow;
extern volatile bitValue_t ledRed;
extern hwSpecUnion_t hwSpecUnion;

static int running = 1;

// Set terminal to non-canonical mode for non-blocking input
void setNonBlockingInput(int enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, 0);
    }
}

// Mock ISR to simulate temperature changes via keyboard input
void* ISR_mock(void* arg) {
    while (running) {
        int ch = getchar();
        if (ch == 'w' || ch == 'W') {
            tempSensor.value++;
            printf("Raw ADC Temperature increased: %u\n", tempSensor.value);
        } else if (ch == 's' || ch == 'S') {
            if (tempSensor.value > 0) tempSensor.value--;
            printf("Raw ADC Temperature decreased: %u\n", tempSensor.value);
        }
        usleep(100); // Poll every 100 ms
    }
    return NULL;
}

// Print the current states of the LEDs
void printLedStates(void) {
    printf("LED states: Green: %s, Yellow: %s, Red: %s\n",
           ledGreen.value ? "ON" : "OFF",
           ledYellow.value ? "ON" : "OFF",
           ledRed.value ? "ON" : "OFF");
}

// Main function
int main(void) {
    eepromRead(hwSpecUnion.eepromData);
    printf("Hardware Revision: %u, Name: %.7s\n", hwSpecUnion.spec.rev, hwSpecUnion.spec.name);
    tempSensor.value = 50;

    setNonBlockingInput(1);
    printf("Press 'w' to increase and 's' to decrease temperature. Ctrl+C to exit.\n");

    pthread_t keyboardThread;
    pthread_create(&keyboardThread, NULL, ISR_mock, NULL);

    while (1) {
        temperatureMonitorCyclic();
        printLedStates();
        usleep(3000 * 1000); // 3000 milliseconds = 3 seconds
    }

    running = 0;
    pthread_join(keyboardThread, NULL);
    setNonBlockingInput(0);
    return 0;
}