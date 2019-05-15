#ifndef GAME_BOARD_DEVICE_INTERFACE_H
#define GAME_BOARD_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_GAME_BOARD_PRINT                      'd'

// Location
#define COMMAND_GAME_BOARD_SHOW_LOCATION              'L'
#define COMMAND_GAME_BOARD_HIDE_LOCATION              'l'

// Path
#define COMMAND_GAME_BOARD_SHOW_PATH                  'P'
#define COMMAND_GAME_BOARD_HIDE_PATH                  'p'

// Unaivalable Path
#define COMMAND_GAME_BOARD_SHOW_UNAVAILABLE_PATH      'V'
#define COMMAND_GAME_BOARD_HIDE_UNAVAILABLE_PATH      'v'

// Outgoing Path
#define COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH         'O'
#define COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH         'o'

// Show Robot
#define COMMAND_GAME_BOARD_SHOW_ROBOT                 'R'
#define COMMAND_GAME_BOARD_HIDE_ROBOT                 'r'

// Show Robot Tof Cone with angle
#define COMMAND_GAME_BOARD_SHOW_ROBOT_TOF_CONE        'T'
#define COMMAND_GAME_BOARD_HIDE_ROBOT_TOF_CONE        't'

// Show Unreachable Path
#define COMMAND_GAME_BOARD_SHOW_UNREACHABLE_AREA      'U'
#define COMMAND_GAME_BOARD_HIDE_UNREACHABLE_AREA      'u'

/**
* Interface for Device
*/
DeviceInterface* getGameboardDeviceInterface(void);

#endif
