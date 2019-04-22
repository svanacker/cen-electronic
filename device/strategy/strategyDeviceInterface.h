#ifndef STRATEGY_DEVICE_INTERFACE_H
#define STRATEGY_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Returns the global score */
#define COMMAND_STRATEGY_GET_GLOBAL_SCORE                  'M'

/** ask the robot to go to the next step. */    
#define COMMAND_STRATEGY_NEXT_STEP                         'n'

// Opponent Position

#define COMMAND_STRATEGY_GET_OPPONENT_ROBOT_POSITION       'o'

#define COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION       'O'

#define COMMAND_STRATEGY_SHOW_TOF_LIST_WITH_PROJECTION     'L'

// Robot Position
#define COMMAND_STRATEGY_GET_ROBOT_POSITION                'r'

#define COMMAND_STRATEGY_SET_ROBOT_POSITION                'R'

#define COMMAND_STRATEGY_SET_ROBOT_POSITION_AS_FIRST_LOCATION_OF_PATH_INDEX 'P'

// ELEMENTARY ACTION

#define COMMAND_TARGET_ACTION_DO_ALL_ITEMS                 'I'

// DEBUG

/** Debug the strategy context. */
#define COMMAND_STRATEGY_DEBUG                             'd'

/** Debug the list of strategies. */
#define COMMAND_STRATEGY_LIST_DEBUG						   'S'

/** Debug the current strategy (other strategies are not loaded). */
#define COMMAND_CURRENT_STRATEGY_ITEM_LIST_DEBUG	       's'

/** Debug the list of target (but not linked to any Strategy. */
#define COMMAND_TARGET_LIST_DEBUG                          'T'

/** Get the next target. */
#define COMMAND_TARGET_NEXT                                't'

/**
* Interface for Device
*/
DeviceInterface* getStrategyDeviceInterface(void);

#endif
