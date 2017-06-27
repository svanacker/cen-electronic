#include <stdbool.h>

#include "systemDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

const char* deviceSystemGetName(void) {
    return "system";
}

int deviceSystemGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // BoardName
    if (commandHeader == COMMAND_BOARD_NAME) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("getBoardName");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // lastError
    else if (commandHeader == COMMAND_GET_LAST_ERROR) {
        if (fillDeviceArgumentList) {
            setFunction("getLastError", 0, 1);
            setResultUnsignedHex4(0, "error");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    if (commandHeader == COMMAND_CLEAR_LAST_ERROR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("clearLastError");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }

    // DeviceList
    else if (commandHeader == COMMAND_DEVICE_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("deviceList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Ping
    else if (commandHeader == COMMAND_PING) {
        if (fillDeviceArgumentList) {
            setFunction("ping", 1, 1);
            setArgumentUnsignedHex2(0, "pingIndex");
            setResultUnsignedHex2(0, "pingIndex");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    // wait
    else if (commandHeader == COMMAND_WAIT) {
        if (fillDeviceArgumentList) {
            setFunction("wait", 1, 0);
            setArgumentUnsignedHex4(0, "ms");                
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    // usage
    else if (commandHeader == COMMAND_USAGE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("usage");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_USAGE_PROBLEM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("usage (only Problems)");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Usage Specific
    else if (commandHeader == COMMAND_USAGE_SPECIFIC_DEVICE) {
        if (fillDeviceArgumentList) {
            setFunction("usageSpecificDevice", 1, 0);
            setArgumentUnsignedChar1(0, "deviceHeaderChar");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
	else if (commandHeader == COMMAND_CLS) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("clearScreen");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
    // Notification
    else if (commandHeader == COMMAND_NOTIFICATION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("notification");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = SYSTEM_DEVICE_HEADER,
    .deviceGetName = &deviceSystemGetName,
    .deviceGetInterface = &deviceSystemGetInterface
};

DeviceInterface* getSystemDeviceInterface(void) {
    return &deviceInterface;
}
