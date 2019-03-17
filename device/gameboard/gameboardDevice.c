#include <stdbool.h>

#include "gameboardDevice.h"
#include "gameboardDeviceInterface.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

#include "../../robot/gameboard/gameboard.h"


// Forward declaration
GameBoard* getGameboardDeviceGameBoard(void);

// DEVICE INTERFACE

void initGameboardDevice(void) {
}

void stopGameboardDevice(void) {

}

bool isGameboardDeviceOk(void) {
    return true;
}

void deviceGameboardHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
	if (commandHeader == COMMAND_GAME_BOARD_PRINT) {
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_PRINT);
        
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        printGameboard(gameBoard, debugOutputStream);
    }
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_LOCATION) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_LOCATION);
        bool showLocation = readBool(inputStream);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showLocation = showLocation;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_PATH);
        bool showPath = readBool(inputStream);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showPath = showPath;
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initGameboardDevice,
    .deviceShutDown = &stopGameboardDevice,
    .deviceIsOk = &isGameboardDeviceOk,
    .deviceHandleRawData = &deviceGameboardHandleRawData,
};

DeviceDescriptor* getGameboardDeviceDescriptor(GameBoard* gameboard) {
    descriptor.object = (int*) gameboard;
    return &descriptor;
}

/**
* @private.
*/
GameBoard* getGameboardDeviceGameBoard(void) {
    return (GameBoard*)(descriptor.object);
}