#ifndef FORK_DEVICE_INTERFACE_2019_H
#define FORK_DEVICE_INTERFACE_2019_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

// ELEVATOR

// Elevator at the bottom to get the pucks
#define COMMAND_2019_ELEVATOR_BOTTOM               'B'

// Elevator at the middle to get the double puck
#define COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION 'D'

// Elevator to get the puck distributor
#define COMMAND_2019_ELEVATOR_INIT_POSITION        'I'

// Elevator at the up to release the pucks
#define COMMAND_2019_ELEVATOR_UP                   'U'

#define COMMAND_2019_ELEVATOR_LEFT                 'L'

#define COMMAND_2019_ELEVATOR_RIGHT                'R'

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

#define COMMAND_2019_FORK_TAKE_GOLDENIUM          'g'


// RELEASE
#define COMMAND_2019_FORK_RELEASE                 'r'

// SCAN
#define COMMAND_2019_FORK_SCAN                    'S'


// ARM ON
#define COMMAND_2019_ARM_ON                       '_'

// ARM OFF
#define COMMAND_2019_ARM_OFF                      '|'


/**
 * Get the device interface for Fork 2019.
 */
DeviceInterface* getFork2019DeviceInterface(void);

#endif
