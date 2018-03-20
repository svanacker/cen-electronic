#ifndef EXTENDED_MOTION_DEVICE_INTERFACE_H
#define EXTENDED_MOTION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

#define BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT      0

// DIGIT FACTOR

#define BSPLINE_MOTION_SPEED_FACTOR_DIGIT                 1
#define BSPLINE_MOTION_ACCELERATION_FACTOR_DIGIT          1


// COMMAND

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_RELATIVE         's'

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_ABSOLUTE         'S'

/** Define the header used to follow a spline which is a simple forward */
#define COMMAND_MOTION_SPLINE_TEST_FORWARD     'f'

/** Define the header used to follow a spline which is a simple backward */
#define COMMAND_MOTION_SPLINE_TEST_BACKWARD    'b'

/** Define the header used to follow a spline test to the left. */
#define COMMAND_MOTION_SPLINE_TEST_LEFT        'l'

/** Define the header used to follow a spline test to the right. */
#define COMMAND_MOTION_SPLINE_TEST_RIGHT       'r'

/** Define the header used to follow a spline test to the left. */
#define COMMAND_MOTION_SPLINE_TEST_FORWARD_LEFT_FORWARD '}'

/** Define the header used to follow a spline test to the right. */
#define COMMAND_MOTION_SPLINE_TEST_FORWARD_RIGHT_FORWARD     '{'

/** Define the header used to follow a spline test to the left. */
#define COMMAND_MOTION_SPLINE_TEST_BACKWARD_LEFT_BACKWARD ')'

/** Define the header used to follow a spline test to the right. */
#define COMMAND_MOTION_SPLINE_TEST_BACKWARD_RIGHT_BACKWARD     '('


/**
* Interface for Device
*/
DeviceInterface* getExtendedMotionDeviceInterface();

#endif
