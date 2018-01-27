#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION       'o'

#define COMMAND_STRATEGY_SET_CONFIG                        'c'

#define COMMAND_STRATEGY_PRINT_GAME_BOARD                  'g'

#define COMMAND_STRATEGY_LIST							   'S'

#define COMMAND_STRATEGY_ITEM							   's'

/** ask the robot to go to the next step. */    
#define COMMAND_STRATEGY_NEXT_STEP                         'n'

/** Set the strategy the current position of the robot. */
#define COMMAND_STRATEGY_SET_ROBOT_POSITION                'r'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface(void);

#endif
