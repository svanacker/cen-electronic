#ifndef GAME_BOARD_DEVICE_INTERFACE_H
#define GAME_BOARD_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_GAME_BOARD_PRINT                      'd'

#define COMMAND_GAME_BOARD_SHOW_LOCATION              'L'

#define COMMAND_GAME_BOARD_SHOW_PATH                  'P'

/**
* Interface for Device
*/
DeviceInterface* getGameboardDeviceInterface(void);

#endif
