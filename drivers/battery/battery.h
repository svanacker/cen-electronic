#ifndef BATTERY_H
#define BATTERY_H

#include <stdbool.h>

/** 
The ADC index to get the value of the battery. 
0x01 corresponds to the pin AN9 / RB9
0x02 corresponds to the pin AN10 / RB10
...
*/
#define BATTERY_ADC_INDEX 0x09

// forward declaration
struct Battery;
typedef struct Battery Battery;

/**
* Returns a value between 0 and 65536 (max 65V) which represents the voltage in mV
* 1 V = 1000
* Ex : if the voltage = 16,5 V it returns 16500
*/
typedef unsigned int ReadBatteryVoltageFunction(Battery* battery);

/**
* Defines the contract for a battery object.
*/
struct Battery {
    /** The function which must be used to read the content in the hardware to read the value of the battery */
    ReadBatteryVoltageFunction* readBatteryValue;
};

/**
 * Check if the structure is well initialized.
 * @param battery POO Programming style
 */
bool isBatteryInitialized(Battery* battery);

/**
 * Initialize the battery structure with read Function.
 * @param battery POO Programming style
 */
void initBattery(Battery* battery, ReadBatteryVoltageFunction* readBatteryValue);

/**
 * Default implementation of battery Voltage read.
 */
unsigned int getBatteryVoltage(Battery* battery);

#endif

