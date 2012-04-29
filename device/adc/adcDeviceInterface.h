#ifndef ADC_DEVICE_INTERFACE_H
#define ADC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Get the value of an ADC. */
#define COMMAND_GET_ADC_VALUE 		'>'

/**
* Interface for the Device
*/
DeviceInterface* getADCDeviceInterface();

#endif
