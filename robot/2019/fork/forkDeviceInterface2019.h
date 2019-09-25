#ifndef FORK_DEVICE_INTERFACE_2019_H
#define FORK_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// FORK

// Fork is retracted
#define COMMAND_2019_FORK_BACK                    'b'

// Fork is configured to get a simple Puck
#define COMMAND_2019_FORK_SIMPLE_PUCK             's'

// Fork is configured to get a double Puck
#define COMMAND_2019_FORK_DOUBLE_PUCK             'd'

// Debug
#define COMMAND_2019_FORK_DEBUG                   'D'

// PUSH
// Push is on                              
#define COMMAND_2019_FORK_PUSH_ON                 'P'

// Push is off
#define COMMAND_2019_FORK_PUSH_OFF                'p'

// INIT
#define COMMAND_2019_FORK_INIT                    'i'

// SCAN
#define COMMAND_2019_FORK_SCAN                    'S'

/**
 * Get the device interface for Fork 2019.
 */
DeviceInterface* getFork2019DeviceInterface(void);

#endif
