#include "include/systemManager.hpp"
#include "include/temperatureMonitor.hpp"
#include "eepromReader.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <termios.h>
#include <unistd.h>

#define SLOWTASK_CYCLE_MS 3000

// Helper function to set terminal to raw mode for key detection
void setTerminalRawMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// Task that repeatedly calls monitor->cyclic()
void cyclicTask_mock(std::chrono::milliseconds interval, temperatureMonitor* monitor, std::atomic<bool>& running) {
    while (running.load()) {
        monitor->cyclic();
        std::this_thread::sleep_for(interval);
    }
}

// Modified cyclic to also handle key input. Mocks a hardware ISR.
void ISR_mock(temperatureSensor* tempSensor, int16_t& tempValue, std::atomic<bool>& running) {
    while (running.load()) {
        // Handle key input (non-blocking)
        fd_set set;
        struct timeval timeout;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);
        if (rv > 0) {
            char c = getchar();
            if (c == 'q') {
                running.store(false);
                break;
            }
            if (c == 'w') {
                ++tempValue;
            } else if (c == 's') {  
                --tempValue;
            }
            // Update the temperature sensor value
            if (tempSensor) {
                tempSensor->updateRawValue(static_cast<uint16_t>(tempValue));
            }
        }
        
    }

}

void consoleOutput(systemManager* sysManager, int16_t& tempValue, std::atomic<bool>& running) {
    setTerminalRawMode(true);
    std::cout << "Temperature Monitor Application Started\n";
    std::cout << "---------------------------------------\n";
    std::cout << "Press UP (w) to increase temperature, DOWN (s) to decrease. Press q to quit.\n";
    std::cout << "---------------------------------------\n";


    while (running.load()) {

        auto redLED = dynamic_cast<ledActuator*>(sysManager->getActuator(0));
        auto yellowLED = dynamic_cast<ledActuator*>(sysManager->getActuator(1));
        auto greenLED = dynamic_cast<ledActuator*>(sysManager->getActuator(2));
        std::cout << "\rRaw Temperature value: " << tempValue
                    << " | Red: " << (redLED && redLED->read() ? "ON" : "OFF")
                    << " | Yellow: " << (yellowLED && yellowLED->read() ? "ON" : "OFF")
                    << " | Green: " << (greenLED && greenLED->read() ? "ON" : "OFF")
                    << "   " << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Prevent flickering
    }
    setTerminalRawMode(false);
}

int main() {
    eepromReader* reader = new eepromReader();;

    // Read configuration from EEPROM
    std::vector<uint8_t> config = reader->readConfiguration();

    // Initialize system manager
    systemManager* sysManager = new systemManager(config);

    temperatureMonitor* monitor = new temperatureMonitor(*sysManager);
    // Print serial number and revision for demonstration
    std::cout << "Serial Number: " << sysManager->getSerialnumber() << std::endl;
    std::cout << "Revision: " << static_cast<int>(sysManager->getRevision()) << std::endl;
    // Initialize temperature monitor app
    monitor->init();

    // Shared temperature value
    int16_t tempValue{0};
    std::atomic<bool> running{true};

    // Start monitor->cyclic() in a separate thread
    std::thread monitorThread(cyclicTask_mock, std::chrono::milliseconds(SLOWTASK_CYCLE_MS), monitor, std::ref(running));
    std::thread consoleThread(consoleOutput, sysManager, std::ref(tempValue), std::ref(running));
    auto tempSensor = dynamic_cast<temperatureSensor*>(sysManager->getSensor(0));
    // Start cyclic + key input function in main thread
    ISR_mock(tempSensor, tempValue, running);
    // Wait for monitor thread to finish
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
    if (consoleThread.joinable()) {
        consoleThread.join();
    }

    monitor->terminate();
    delete monitor;
    delete sysManager;
    delete reader;
    return 0;
}

