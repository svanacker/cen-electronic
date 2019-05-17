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

// TAKE
#define COMMAND_2019_FORK_TAKE_SIMPLE_PUCK        't'

#define COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM  'g'

#define COMMAND_2019_FORK_TAKE_GOLDENIUM          'h'

#define COMMAND_2019_FORK_DROP_GOLDENIUM          'j'

// ACCELERATOR DROP
#define COMMAND_2019_FORK_ACCELERATOR_DROP        'r'

// SCAN
#define COMMAND_2019_FORK_SCAN                    'S'

/**
 * Get the device interface for Fork 2019.
 */
DeviceInterface* getFork2019DeviceInterface(void);

#endif
