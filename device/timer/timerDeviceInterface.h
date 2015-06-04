#ifndef TIMER_DEVICE_INTERFACE_H
#define TIMER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to see the list of Timer List. */
#define COMMAND_TIMER_LIST              'L'

/** Command to add Timer Demo (print each seconds a timer index) by his index. */
#define COMMAND_TIMER_ENABLE_DEMO       'e'

/** Command to stop the Timer Demo. */
#define COMMAND_TIMER_DISABLE_DEMO        'd'


/**
* Get the timer device interface.
* @return a pointer on the timer device Interface.
*/
DeviceInterface* getTimerDeviceInterface(void);

#endif
