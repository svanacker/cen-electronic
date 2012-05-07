#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_SET_OPPONENT_ROBOT_POSITION		'y'

#define COMMAND_SET_CONFIG						'Y'

#define COMMAND_PRINT_GAME_BOARD				'G'

/** ask the robot to go to the next step. */	
#define COMMAND_NEXT_STEP						'Q'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface();

#endif
