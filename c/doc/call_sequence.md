\thispagestyle{empty}
``` {.mermaid width=1024 format=pdf}
sequenceDiagram
    participant Main
    participant KeyboardTask
    participant TempMonitor
    participant SwitchLEDs
    participant ReadTemp
    participant SetLED
    participant EEPROM
    participant ISR
    participant InterruptHandler

    Main->>EEPROM: eepromRead()
    Main->>KeyboardTask: start updateTemperatureFromKeyboardTask (thread)
    loop every 3s
        Main->>TempMonitor: temperatureMonitorCyclic()
        TempMonitor->>ReadTemp: readTempSensor()
        TempMonitor->>SwitchLEDs: switchLEDS(green, yellow, red)
        SwitchLEDs->>SetLED: setLED(0, ledGreenReq)
        SwitchLEDs->>SetLED: setLED(1, ledYellowReq)
        SwitchLEDs->>SetLED: setLED(2, ledRedReq)
    end
    InterruptHandler->>ISR: ISR_mock() (interrupt/event)
```