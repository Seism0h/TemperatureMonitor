#ifndef SENSOR_H
#define SENSOR_H

// Abstract base class
class sensor {
public:
    virtual ~sensor() = default;
};

template <typename SensorInputType, typename SensorOutputType> // SensorInputType is the raw type read from hardware, SensorOutputType is the processed type returned to the application
class sensorInterface : public sensor {
protected:
    SensorInputType rawValue;
    SensorOutputType sensorValue;

public:
    sensorInterface() : rawValue(), sensorValue() {}
    virtual ~sensorInterface() = default;
    
    virtual SensorOutputType read() = 0; 
    virtual void updateRawValue(SensorInputType rawValue) final { // implement this such that it cannot be overridden. Just updates the raw value from an interrupt routine.
        this->rawValue = rawValue;
    }
};

#endif // SENSOR_H