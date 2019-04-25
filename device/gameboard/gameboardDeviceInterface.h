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

// Outgoing Path
#define COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH         'O'
#define COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH         'o'

/**
* Interface for Device
*/
DeviceInterface* getGameboardDeviceInterface(void);

#endif
