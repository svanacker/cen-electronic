#ifndef GAME_BOARD_DEVICE_H
#define GAME_BOARD_DEVICE_H

#include "../../device/deviceDescriptor.h"

#include "../../robot/gameboard/gameboard.h"

/**
 * Returns a descriptor on the device for Gameboard.
 */
DeviceDescriptor* getGameboardDeviceDescriptor(GameBoard* gameBoard);

#endif
