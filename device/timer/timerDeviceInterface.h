#ifndef TIMER_DEVICE_INTERFACE_H
#define TIMER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"


/** Command to see the count of timer. */
#define COMMAND_TIMER_COUNT             'c'

/** Command to see the list of Timer List (but in debug console). */
#define COMMAND_TIMER_LIST              'L'

/** Command to read all values about a timer . */
#define COMMAND_TIMER_READ              'r'

/** Command to write values about a timer . */
#define COMMAND_TIMER_ENABLE_DISABLE      'e'

/** Command to read the time since last mark . */
#define COMMAND_TIMER_TIME_SINCE_LAST_MARK 'm'

/** Command to mark a timer . */
#define COMMAND_TIMER_MARK              'M'

/** Command to know if a timer has timeout . */
#define COMMAND_TIMER_TIMEOUT           't'

/** Command to stop or start the Timer Demo (add it if it does not exist). */
#define COMMAND_TIMER_DEMO             'D'

/**
* Get the timer device interface.
* @return a pointer on the timer device Interface.
*/
DeviceInterface* getTimerDeviceInterface(void);

#endif
