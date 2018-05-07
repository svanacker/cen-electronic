#ifndef TRAJECTORY_DEVICE_REMOTE_INTERFACE_H
#define TRAJECTORY_DEVICE_REMOTE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/**
* Defines the header used to ask absolute position.
*/
#define COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION            'r'

/**
* Write in debug the absolute position .
*/
#define COMMAND_TRAJECTORY_DEBUG_GET_ABSOLUTE_POSITION      'd'

/**
* Write in debug coders history value.
*/
#define COMMAND_TRAJECTORY_DEBUG_CODERS					    'D'

/**
 * Command to disable the notification system.
 */
#define COMMAND_TRAJECTORY_NOTIFY_OFF                       'n'

/**
 * Command to enable the notification system.
 */
#define COMMAND_TRAJECTORY_NOTIFY_ON                        'N'

/**
 * Command to set the parameters of the notification
 * System.
 * @return 
 */
#define COMMAND_TRAJECTORY_NOTIFY_SET_PARAMETERS            'P'

/**
* Defines the header used to set the absolute position.
*/
#define COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION            'W'

/**
 * Set the angle to the closest value.
 * Ex : 0, 90, 180, 270 (in radians) ... 
*/
#define COMMAND_TRAJECTORY_ADJUST_ANGLE_TO_CLOSEST          't'

/**
 * Adjust X, but does not change Y.
 * @return 
 */
#define COMMAND_TRAJECTORY_ADJUST_X                         'x'

/**
 * Adjust Y, but does not change Y, set the angle to the closest value
 * Ex : 0, 90, 180, 270 ... 
 * @return 
 */
#define COMMAND_TRAJECTORY_ADJUST_Y                         'y'

// NOTIFICATION

/** Notification to indicates to the client of the MOTOR_BOARD that the trajectory has changed enough (Threshold) to notify the move. */
#define NOTIFY_TRAJECTORY_CHANGED                           'm'

/**
* Interface for Device
*/
DeviceInterface* getTrajectoryDeviceInterface();

#endif
