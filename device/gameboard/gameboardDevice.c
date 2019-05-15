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

void deviceGameboardHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
	if (commandHeader == COMMAND_GAME_BOARD_PRINT) {
        OutputStream* debugOutputStream = getInfoOutputStreamLogger();
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_PRINT);
        
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        printGameboard(gameBoard, debugOutputStream);
    }
    // Show/Hide Location
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_LOCATION) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_LOCATION);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showLocation = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_LOCATION) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_LOCATION);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showLocation = false;
    }
    // Show/Hide Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showPath = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showPath = false;
    }
    // Show/Hide Unavailable Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_UNAVAILABLE_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_UNAVAILABLE_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showUnavailablePath = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_UNAVAILABLE_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_UNAVAILABLE_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showUnavailablePath = false;
    }
    // Show/Hide Outgoing Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showOutgoingPath = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showOutgoingPath = false;
    }
    // Show/Hide Robot
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_ROBOT) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_ROBOT);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showRobot = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_ROBOT) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_ROBOT);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showRobot = false;
    }
    // Show/Hide Robot Tof Cone
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_ROBOT_TOF_CONE) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_ROBOT_TOF_CONE);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showRobotTofsCones = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_ROBOT_TOF_CONE) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_ROBOT_TOF_CONE);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showRobotTofsCones = false;
    }
    // Show/Hide Unreachable Area
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_UNREACHABLE_AREA) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_SHOW_UNREACHABLE_AREA);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showUnreachableArea = true;
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_UNREACHABLE_AREA) {
        ackCommand(outputStream, GAME_BOARD_DEVICE_HEADER, COMMAND_GAME_BOARD_HIDE_UNREACHABLE_AREA);
        GameBoard* gameBoard = getGameboardDeviceGameBoard();
        gameBoard->showUnreachableArea = false;
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