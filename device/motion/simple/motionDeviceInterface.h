#ifndef MOTION_DEVICE_INTERFACE_H
#define MOTION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/** Backward with value in mm. */
#define COMMAND_MOTION_BACKWARD_IN_MM         'b'

/** Stop and cancel the current motion, to cancel all, use COMMAND_MOTION_CANCEL_ALL. */
#define COMMAND_MOTION_STOP                   's'

/** Cancel all motion. */
#define COMMAND_MOTION_CANCEL_ALL             'c'

/** Forward with value in mm. */
#define COMMAND_MOTION_FORWARD_IN_MM          'f'

/** Turn to the left in degree. */
#define COMMAND_MOTION_LEFT_IN_DECI_DEGREE    'l'

/** Turn to the right in degree. */
#define COMMAND_MOTION_RIGHT_IN_DECI_DEGREE   'r'

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE '('

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE ')'



// CALIBRATION

/** Define the command used to do a square useful for calibration. */
#define COMMAND_SQUARE_CALIBRATION             '@'

// MOTION MODE

/** Indicates that the instruction must be added on a stack and not replace the current instruction. */
#define COMMAND_MOTION_MODE_ADD				   '+'

/** Indicates that the instruction must replace the stack and not be added on stack */
#define COMMAND_MOTION_MODE_REPLACE			   '_'

/** Function to get the motion mode (Add/stacking or replace). */
#define COMMAND_MOTION_MODE_GET				   '?'

// NOTIFICATION

/** Argument for the status of the robot when position reached. */
#define NOTIFY_MOTION_STATUS_REACHED           'R'

/** Argument for the status of the robot when robot was blocked when reaching the position. */
#define NOTIFY_MOTION_STATUS_BLOCKED           'k'

/** Argument for the status of the robot when robot was shocked when reaching the position. */
#define NOTIFY_MOTION_STATUS_SHOCKED           'S'

/** Argument for the status of the robot when there is an obstacle. */
#define NOTIFY_MOTION_STATUS_OBSTACLE          'o'

/** Argument for the status of the robot when position is in progress. */
#define NOTIFY_MOTION_STATUS_MOVING            'm'

/** Argument for the status of the robot when position was not reached inside the timeout. */
#define NOTIFY_MOTION_STATUS_FAILED            'f'

/** Obstacle : stop the current Motion and maintain Position. */
#define COMMAND_MOTION_OBSTACLE                '|'

/**
* Interface for Device
*/
DeviceInterface* getMotionDeviceInterface();

#endif
