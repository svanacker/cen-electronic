#ifndef PIN_DEVICE_INTERFACE_H
#define PIN_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to read the value of a Pin. */
#define COMMAND_GET_PIN_VALUE 'v'

/** Command to set the value of a pin. */
#define COMMAND_SET_PIN_VALUE 'V'

/**
* Get the pin device interface.
* @return the pointer on device Interface.
*/
DeviceInterface* getPinDeviceInterface();

#endif
