#ifndef ADC_DEVICE_INTERFACE_H
#define ADC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Get the value of an ADC. */
#define COMMAND_GET_ADC_VALUE                   'r'

/** Get the value of an ADC for x sample for a defined period of x deciseconds (and debug to the console the info). */
#define COMMANG_GET_ADC_VALUE_DEBUG_PERIOD      's'

/** Get the value of all ADC. */
#define COMMAND_GET_ADC_ALL_VALUES              'R'

/** define the portBbits to be ADC.*/           
#define COMMAND_SET_ADC_PARAMETERS              'P'

/**
* Interface for the Device
* @return the Interface for the ADC device.
*/
DeviceInterface* getADCDeviceInterface();

#endif
