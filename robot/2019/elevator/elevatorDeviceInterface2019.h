#ifndef ELEVATOR_DEVICE_INTERFACE_2019_H
#define ELEVATOR_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// Elevator at the bottom to get the pucks
#define COMMAND_2019_ELEVATOR_BOTTOM               'B'

#define COMMAND_2019_ELEVATOR_DISTRIBUTOR_SCAN     'D'

// Elevator at the middle to get the double puck
#define COMMAND_2019_ELEVATOR_GOLDENIUM_POSITION   'G'

// Elevator to get the puck distributor
#define COMMAND_2019_ELEVATOR_INIT_POSITION        'I'

// Command to specify a specific value for the Elevator
#define COMMAND_2019_ELEVATOR_VALUE                'E'

// Elevator at the up to release after the first puck in the accelerator
#define COMMAND_2019_ELEVATOR_ACCELERATOR_SECOND_DROP  'S'

// Elevator at the up to release the pucks
#define COMMAND_2019_ELEVATOR_UP                   'U'

// LEFT / RIGHT / MIDDLE
#define COMMAND_2019_ELEVATOR_LEFT                 'L'

#define COMMAND_2019_ELEVATOR_MIDDLE               'M'

#define COMMAND_2019_ELEVATOR_RIGHT                'R'

/**
 * Get the device interface for Elevator 2019.
 */
DeviceInterface* getElevator2019DeviceInterface(void);

#endif
