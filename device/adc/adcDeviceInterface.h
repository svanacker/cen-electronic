#ifndef ADC_DEVICE_INTERFACE_H
#define ADC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Get the value of an ADC. */
#define COMMAND_GET_ADC_VALUE         'r'

/**
* Interface for the Device
* @return the Interface for the ADC device.
*/
DeviceInterface* getADCDeviceInterface();

#endif
