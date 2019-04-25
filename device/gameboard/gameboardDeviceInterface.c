#include <stdbool.h>

#include "gameboardDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#include "../../robot/gameboard/gameboard.h"

const char* getGameboardDeviceName(void) {
    return "gameBoard";
}

int deviceGameBoardGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_GAME_BOARD_PRINT) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("printGameBoard");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Show/Hide Location
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Location");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Location");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Show/Hide Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("show Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Show/Hide Outgoing Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show OutgoingPath");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide OutgoingPath");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = GAME_BOARD_DEVICE_HEADER,
    .deviceGetName = &getGameboardDeviceName,
    .deviceGetInterface = &deviceGameBoardGetInterface
};

DeviceInterface* getGameboardDeviceInterface(void) {
    return &deviceInterface;
}
