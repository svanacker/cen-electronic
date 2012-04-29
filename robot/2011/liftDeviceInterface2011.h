#ifndef LIFT_DEVICE_INTERFACE_2011_H
#define LIFT_DEVICE_INTERFACE_2011_H

#include "../../device/device.h"

// Up / Down

#define COMMAND_LIFT_2011_BOTTOM	'_'

#define COMMAND_LIFT_2011_UP		'U'

#define COMMAND_LIFT_2011_DOWN	'V'

/**
* Get the device interface for lift 2011.
*/
DeviceInterface* getLift2011DeviceInterface();

#endif
