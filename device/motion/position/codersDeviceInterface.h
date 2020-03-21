#ifndef CODERS_DEVICE_INTERFACE_H
#define CODERS_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/** The command header to get the wheel position (left / right). */
#define COMMAND_GET_WHEEL_POSITION                    'r'

/** The command header to clear the coders value. */
#define COMMAND_CLEAR_CODERS                          'c'

/** The command header to see the wheel position as debug info. */
#define COMMAND_DEBUG_GET_WHEEL_POSITION              'd'

/** The command header to Acquire the wheel position the coder for a period of time */
#define COMMAND_DEBUG_ACQUIRE_SAMPLE_WHEEL_POSITION   'D'

/** The command header to show the wheel position history list. */
#define COMMAND_DEBUG_PRINT_SAMPLE_WHEEL_POSITION     'P'

/**
 * Get the coders interface
 */
DeviceInterface* getCodersDeviceInterface();

#endif
