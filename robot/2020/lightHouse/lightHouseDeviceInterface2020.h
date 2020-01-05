#ifndef LIGHT_HOUSE_DEVICE_INTERFACE_2020_H
#define LIGHT_HOUSE_DEVICE_INTERFACE_2020_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

#include "../../../common/pwm/servo/servoList.h"

// Light House Debug
#define COMMAND_LIGHT_HOUSE_2020_DEBUG                                    'd'

// Light House Up
#define COMMAND_LIGHT_HOUSE_2020_UP                                       'u'

// Light House Up
#define COMMAND_LIGHT_HOUSE_2020_BOTTOM                                   'b'


// Light House Show Experience !
#define COMMAND_LIGHT_HOUSE_2020_SHOW                                     'S'

// Light House Init
#define COMMAND_LIGHT_HOUSE_2020_INIT                                     'I'

// Light House Simulate Robot is Placed
#define COMMAND_LIGHT_HOUSE_2020_SIMULATE_ROBOT_PLACED                    'p'

// Light House Simulate Robot is Near from the Light House
#define COMMAND_LIGHT_HOUSE_2020_SIMULATE_ROBOT_NEAR                      'n'

/**
 * Get the device interface for Light House 2020.
 */
DeviceInterface* getLightHouse2020DeviceInterface(void);

#endif
