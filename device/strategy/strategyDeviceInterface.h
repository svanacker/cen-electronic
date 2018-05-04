#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_STRATEGY_SET_CONFIG                        'c'

#define COMMAND_STRATEGY_DEBUG                             'd'

/** Returns the global score */
#define COMMAND_STRATEGY_GET_GLOBAL_SCORE                  'M'

#define COMMAND_LOCATION_LIST							   'L'

#define COMMAND_PATH_LIST							       'P'

/** ask the robot to go to the next step. */    
#define COMMAND_STRATEGY_NEXT_STEP                         'n'

#define COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION       'o'

/** Set the strategy the current position of the robot. */
#define COMMAND_STRATEGY_SET_ROBOT_POSITION                'r'

#define COMMAND_STRATEGY_LIST							   'S'

#define COMMAND_STRATEGY_ITEM							   's'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface(void);

#endif
