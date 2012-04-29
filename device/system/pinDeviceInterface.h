#ifndef PIN_DEVICE_INTERFACE_H
#define PIN_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to read the value of a Pin. */
#define COMMAND_GET_PIN_VALUE 'v'

/** Command to set the value of a pin. */
#define COMMAND_SET_PIN_VALUE 'V'

/**
* Get the system device interface.
*/
DeviceInterface* getPinDeviceInterface();

#endif
