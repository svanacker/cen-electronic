#ifndef MOTION_DEVICE_INTERFACE_H
#define MOTION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"

/** Goto with value in coder pulse. */
#define COMMAND_MOTION_GOTO_IN_PULSE 'g'

/** Forward with value in mm. */
#define COMMAND_MOTION_FORWARD_IN_MM 'f'

/** Backward with value in mm. */
#define COMMAND_MOTION_BACKWARD_IN_MM 'b'

/** Turn to the left in degree. */
#define COMMAND_MOTION_LEFT_IN_DECI_DEGREE 'l'

/** Turn to the right in degree. */
#define COMMAND_MOTION_RIGHT_IN_DECI_DEGREE 'r'

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE '('

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE ')'

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_RELATIVE 		'%'

/** Define the header used to follow a spline with relative coordinates. */
#define COMMAND_MOTION_SPLINE_ABSOLUTE 		'&'

/** Define the header used to follow a spline test. */
#define COMMAND_MOTION_SPLINE_TEST_LEFT	'+'

/** Define the header used to follow a spline test. */
#define COMMAND_MOTION_SPLINE_TEST_RIGHT	'-'

/** Defines the COMMAND used to get speed / acceleration parameters for different motion type. */
#define COMMAND_GET_MOTION_PARAMETERS 			'?'

/** Defines the COMMAND used to set speed / acceleration parameters for different motion type. */
#define COMMAND_SET_MOTION_PARAMETERS 			':'

/** Define the command used to do a square useful for calibration. */
#define COMMAND_SQUARE_CALIBRATION '@'

/** Cancel all current motion. */
#define COMMAND_MOTION_CANCEL 'Z'

/** Obstacle : stop the current Motion and maintain Position. */
#define COMMAND_MOTION_OBSTACLE ','

/** Notify the status of the robot. */
#define NOTIFY_MOTION_STATUS 'k'

/** Argument for the status of the robot when position reached. */
#define NOTIFY_MOTION_ARG_REACHED 	0

/** Argument for the status of the robot when robot failed to reach. */
#define NOTIFY_MOTION_ARG_FAILED 	1

/** Argument for the status of the robot when there is an obstacle. */
#define NOTIFY_MOTION_ARG_OBSTACLE 	2

/** Argument for the status of the robot when position is in progress. */
#define NOTIFY_MOTION_ARG_MOVING 	3


/**
* Interface for Device
*/
DeviceInterface* getMotionDeviceInterface();

#endif
