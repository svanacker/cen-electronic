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
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunction("showLocation", 1, 0);
            setArgumentUnsignedChar1(0, "off(0) / on (1)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_PATH) {
        if (fillDeviceArgumentList) {
            setFunction("showPath", 1, 0);
            setArgumentUnsignedChar1(0, "off(0) / on (1)");
        }
        return commandLengthValueForMode(mode, 1, 0);
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
