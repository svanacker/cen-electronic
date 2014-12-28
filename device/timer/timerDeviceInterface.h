#ifndef TIMER_DEVICE_INTERFACE_H
#define TIMER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to see the list of Timer List. */
#define COMMAND_TIMER_LIST 'T'

/**
* Get the timer device interface.
* @return a pointer on the timer device Interface.
*/
DeviceInterface* getTimerDeviceInterface(void);

#endif
