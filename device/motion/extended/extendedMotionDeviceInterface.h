#ifndef EXTENDED_MOTION_DEVICE_INTERFACE_H
#define EXTENDED_MOTION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_RELATIVE         's'

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_ABSOLUTE         'S'

/** Define the header used to follow a spline test. */
#define COMMAND_MOTION_SPLINE_TEST_LEFT        '{'

/** Define the header used to follow a spline test. */
#define COMMAND_MOTION_SPLINE_TEST_RIGHT       '}'

/**
* Interface for Device
*/
DeviceInterface* getExtendedMotionDeviceInterface();

#endif
