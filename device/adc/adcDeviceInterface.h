#ifndef ADC_DEVICE_INTERFACE_H
#define ADC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define ADC_DEVICE_HEADER			'd'

/** Get the value of an ADC. */
#define COMMAND_GET_ADC_VALUE 		'r'

/**
* Interface for the Device
*/
DeviceInterface* getADCDeviceInterface();

#endif
