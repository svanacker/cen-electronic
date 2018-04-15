#ifndef LAUNCHER_DEVICE_INTERFACE_2018_H
#define LAUNCHER_DEVICE_INTERFACE_2018_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

// Common 
// Sense are seen with an observer behind the robot (he see the LCD Panel)
#define LAUNCHER_LEFT_INDEX          0
#define LAUNCHER_RIGHT_INDEX         1
#define LAUNCHER_BEE_INDEX           2

// BALL LAUNCHER

/**
 * Prepare the launch of one ball
 */
#define LAUNCHER_PREPARE_BALL_COMMAND  'p'

/**
 * Send the ball
 */
#define LAUNCHER_SEND_BALL_COMMAND     's'


// SWITCH SERVO MOTORS

/**
 * Turn the SERVO to hurt the switch, and back to the normal position
 * @return 
 */
#define LAUNCHER_LIGHT_ON_SERVO_MOVE   'l'

/**
 * Get the device interface for launcher 2018.
 */
DeviceInterface* getLauncher2018DeviceInterface(void);

#endif
