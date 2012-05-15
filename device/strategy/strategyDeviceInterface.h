#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION		'y'

#define COMMAND_STRATEGY_SET_CONFIG						'Y'

#define COMMAND_STRATEGY_PRINT_GAME_BOARD				'G'

/** ask the robot to go to the next step. */	
#define COMMAND_STRATEGY_NEXT_STEP						'Q'

/** Set the strategy the current position of the robot. */
#define COMMAND_STRATEGY_SET_ROBOT_POSITION		']'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface();

#endif
