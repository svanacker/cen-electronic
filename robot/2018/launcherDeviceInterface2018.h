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

// DISTRIBUTOR

/**
 * Launch a clean Ball by rotating of 45° to the Launcher
 */
#define LAUNCHER_DISTRIBUTOR_NEXT_CLEAN_BALL    'n'

/**
 * 1. Prepare the launcher
 * 2. Rotate the distributor which lead to load the ball in the launcher
 * 3. Send the ball
 */
#define LAUNCHER_SEQUENCE_CLEAN_BALL           'N'

/**
 * Get the device interface for launcher 2018.
 */
DeviceInterface* getLauncher2018DeviceInterface(void);

#endif
