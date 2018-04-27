#ifndef STRATEGY_DEVICE_INTERFACE_2018_H
#define STRATEGY_DEVICE_INTERFACE_2018_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

#define STRATEGY_2018_DISTRIBUTOR_DEBUG_COMMAND              'D'

#define STRATEGY_2018_READ_BALL_COLOR_TYPE                   'c'

#define STRATEGY_2018_UNICOLOR_COMMAND                       'U'

#define STRATEGY_2018_MIXED_COLOR_PHASE_1_COMMAND            'm'
#define STRATEGY_2018_MIXED_COLOR_PHASE_2_COMMAND            'M'

/**
 * Get the device interface for strategy 2018.
 */
DeviceInterface* getStrategy2018DeviceInterface(void);

#endif
