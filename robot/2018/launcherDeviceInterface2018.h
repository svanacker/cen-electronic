#ifndef LAUNCHER_DEVICE_INTERFACE_2018_H
#define LAUNCHER_DEVICE_INTERFACE_2018_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

// Common 

/**
 * NB : All Direction (LEFT / RIGHT) are seen with an observer behind the robot (he see the LCD Panel)
 */

#define LAUNCHER_LEFT_INDEX          0
#define LAUNCHER_RIGHT_INDEX         1

#define LAUNCHER_PREPARE_ON         true
#define LAUNCHER_LAUNCH             false

// BALL LAUNCHER

/**
 * Prepare the launch of one ball
 */
#define LAUNCHER_PREPARE_BALL_COMMAND              'P'

/**
 * Send the ball
 */
#define LAUNCHER_SEND_BALL_COMMAND                 'S'


// SWITCH SERVO MOTORS

/**
 * Turn the SERVO to hurt the switch, and back to the normal position
 * @return 
 */
#define LAUNCHER_LIGHT_ON_SERVO_MOVE_COMMAND      'L'

// DISTRIBUTOR

/**
 * Launch a clean Ball by rotating of 45° to the Launcher
 */
#define DISTRIBUTOR_LOAD_NEXT_BALL_COMMAND         'n'

 /**
 * 1. Prepare the launcher
 * 2. Rotate the distributor which lead to load the ball in the launcher
 * 3. Send the ball
 */
#define LAUNCHER_LOAD_AND_SEND_BALL_COMMAND      'N'

 /**
  * Do 8x the same sequence
  * 1. Prepare the launcher
  * 2. Rotate the distributor which lead to load the ball in the launcher
  * 3. Send the ball
  */
#define LAUNCHER_LOAD_AND_SEND_UNICOLOR_BALL_LIST         'U'

/**
 * Load 8 mixed balls
 * @return 
 */
#define LAUNCHER_LOAD_AND_SEND_MIXED_BALL_LIST            'M'

/**
 * Eject a a dirty Ball.
 */
#define DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND              'e'

/**
 * Get the device interface for launcher 2018.
 */
DeviceInterface* getLauncher2018DeviceInterface(void);

#endif
