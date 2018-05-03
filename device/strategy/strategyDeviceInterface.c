#include <stdbool.h>

#include "strategyDeviceInterface.h"

#include "../../common/commons.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getStrategyDeviceName(void) {
    return "Strategy";
}

int deviceStrategyGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // Robot opponent position
    if (commandHeader == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("setOpponentRobotPos", 3, 0);
            setArgumentUnsignedHex4(0, "x (mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "y (mm)");
        }
        return commandLengthValueForMode(mode, 9, 0);
    }
    // Config
    else if (commandHeader == COMMAND_STRATEGY_SET_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunction("setConfig", 1, 0);
            setArgumentUnsignedHex4(0, "config");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
	// Print Strategy List
	else if (commandHeader == COMMAND_STRATEGY_LIST) {
		// same input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("strategyList");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	// Print Strategy Item
	else if (commandHeader == COMMAND_STRATEGY_ITEM) {
		if (fillDeviceArgumentList) {
			setFunction("strategyItem", 1, 0);
			setArgumentUnsignedHex2(0, "index");
		}
		return commandLengthValueForMode(mode, 2, 0);
	}
    // Print Location List
    else if (commandHeader == COMMAND_LOCATION_LIST) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("locationList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Print Path List
    else if (commandHeader == COMMAND_PATH_LIST) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pathList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Next step
    else if (commandHeader == COMMAND_STRATEGY_NEXT_STEP) {
        if (fillDeviceArgumentList) {
            setFunction("nextStep", 0, 1);
            setResultUnsignedHex2(0, "status");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    // Notify position
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("strategySetRobotPosition", 7, 0);
            setArgumentUnsignedHex2(0, "status");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "x(mm)");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "y(mm)");
            setArgumentSeparator(5);
            setArgumentUnsignedHex4(6, "ang(1/10)deg");
        }
        return commandLengthValueForMode(mode, 17, 0);
    }    
    // Get the global score
    else if (commandHeader == COMMAND_STRATEGY_GET_GLOBAL_SCORE) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunction("Get Global Score", 0, 1);
            setResultUnsignedHex4(0, "score");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = STRATEGY_DEVICE_HEADER,
    .deviceGetName = &getStrategyDeviceName,
    .deviceGetInterface = &deviceStrategyGetInterface
};

DeviceInterface* getStrategyDeviceInterface(void) {
    return &deviceInterface;
}
