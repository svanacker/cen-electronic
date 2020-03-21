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

int deviceGameBoardGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMANDE_GAME_BOARD_COLLISION) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunction("Check Collision", 3, 1);
            setArgumentFloatHex4(0, "x");
            setArgumentSeparator(1);
            setArgumentFloatHex4(2, "y");
            setResultUnsignedChar1(0, "0 = not in coll. area, 1 = in coll. Area ");
        }
        return commandLengthValueForMode(mode, 9, 1);
    }// Print
    else if (commandHeader == COMMAND_GAME_BOARD_PRINT) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("printGameBoard");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Location
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Location");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_LOCATION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Location");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("show Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Unavailable Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_UNAVAILABLE_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("show Unavailable Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_UNAVAILABLE_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Unavailable Path");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Robot
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_ROBOT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Robot");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_ROBOT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Robot");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Robot Cone
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_ROBOT_TOF_CONE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Robot Tofs Cone");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_ROBOT_TOF_CONE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide Robot Tofs Cone");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Outgoing Path
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_OUTGOING_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show OutgoingPath");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_OUTGOING_PATH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide OutgoingPath");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// Show/Hide Unreachable Area
    else if (commandHeader == COMMAND_GAME_BOARD_SHOW_UNREACHABLE_AREA) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Unreachable Area");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_GAME_BOARD_HIDE_UNREACHABLE_AREA) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Hide  Unreachable Area");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Show/Hide Robot
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
