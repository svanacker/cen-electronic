#ifndef BATTERY_H
#define BATTERY_H

/**
* Device to handle the battery
*/
#include "../device.h"

/** 
The ADC index to get the value of the battery. 
0x01 corresponds to the pin AN9 / RB9
0x02 corresponds to the pin AN10 / RB10
...
*/
#define BATTERY_ADC_INDEX 0x09

/**
* Returns the descriptor for the battery device.
*/
DeviceDescriptor getBatteryDeviceDescriptor();

/**
* Init the device
*/
void initBattery();

/**
 * Returns the revision of the Software.
 */
unsigned int getBatterySoftwareRevision();

//  char* getDeviceName() {
    //return DEVICE_NAME;
//  }

unsigned int isBatteryDeviceOk();

/**
* Returns a value between 0 and 65536 (max 65V) which represents the voltage in mV
* 1 V = 1000
* Ex : if the voltage = 16,5 V it returns 16500
* @param batteryIndex the battery of which we want the level
*/
int getBatteryVoltage(int batteryIndex);

/**
* Returns a mask value to show the level of the battery with 4 levels
* We consider that we have NiMh battery.
* Battery full = 17 V
* Battery 2/3 = 16 V
* Battery 1/3 = 15 V
* Battery empty (0) = 14 V
* @param batteryIndex the battery of which we want the level
*/
// int getMaskBatteryLevel(int batteryIndex);

/**
* Shows the level of the battery on the dedicated pin.
*/
// void showBatteryLevel(int batteryIndex);


#endif

