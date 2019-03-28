#ifndef CURRENT_H
#define CURRENT_H

// forward declaration
struct Current;
typedef struct Current Current;

/**
 * Get the value from the current sensor
 * @return current  the value from the current sensor
 */
typedef int CurrentReadSensorValueFunction (Current* current);

/** 
 * Set the current to know if we are above the value.
 * @param currentSensorAlert the new limit for the current
 */
typedef void CurrentWriteAlertLimitFunction(Current* current, int currentSensorAlert);

/**
 * Current sensor wrapping.
 */
struct Current {
    /** The function which must be used to read the value of the current (in celcius degree). */
    CurrentReadSensorValueFunction* readSensorValue;
    /** The function which must be used to write the alert limit of the current sensor (in celcius degree). */
    CurrentWriteAlertLimitFunction* writeAlertLimit;
    /** A pointer on generic object (for example to store I2cBus ...). */
    void* object;
};

/**
 * Initialize the current object wrapper.
 * @param current the pointer on current object (POO Programming)
 * @param readSensorValue the pointer on the callback function to read the value of the current (in celcius degree).
 * @param writeAlertLimit the pointer on the callback function to write the alert limit of the current sensor (in celcius degree).
 */
void initCurrent(Current* current,
                     CurrentReadSensorValueFunction* readSensorValue,
                     CurrentWriteAlertLimitFunction* writeAlertLimit,
                     void* object);

#endif
