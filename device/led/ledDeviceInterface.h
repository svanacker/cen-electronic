#ifndef LED_DEVICE_INTERFACE_H
#define LED_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_LED_CLEAR_ALL         'c'

#define COMMAND_LED_WRITE             'w'

#define COMMAND_LED_ALL_ON            'o'

// Specific Color

#define COMMAND_LED_BLUE              'b'

#define COMMAND_LED_RED               'r'

#define COMMAND_LED_GREEN             'g'

// Specific Color for ALL

#define COMMAND_LED_ALL_BLUE          'B'

#define COMMAND_LED_ALL_RED           'R'

#define COMMAND_LED_ALL_GREEN         'G'

/**
 * Interface for Led Device.
 */
DeviceInterface* getLedDeviceInterface(void);

#endif

