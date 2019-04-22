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
    if (commandHeader == COMMAND_STRATEGY_GET_OPPONENT_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("get Opponent Robot Position", 0, 3);
            setResultUnsignedHex4(0, "x (mm)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "y (mm)");
        }
        return commandLengthValueForMode(mode, 0, 9);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_OPPONENT_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("set Opponent Robot Position", 3, 0);
            setArgumentUnsignedHex4(0, "x (mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "y (mm)");
        }
        return commandLengthValueForMode(mode, 9, 0);
    }
    else if (commandHeader == COMMAND_STRATEGY_SHOW_TOF_LIST_WITH_PROJECTION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show Tof List With Projection");
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
    // Do All Action Items
    else if (commandHeader == COMMAND_TARGET_ACTION_DO_ALL_ITEMS) {
        if (fillDeviceArgumentList) {
            setFunction("do All Actions Items of a Target", 3, 0);
            setArgumentUnsignedHex2(0, "Target Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Action Index");

        }
        return commandLengthValueForMode(mode, 5, 0);
    }
    // Robot position
    else if (commandHeader == COMMAND_STRATEGY_GET_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("strategy Get Robot Position", 0, 5);
            setResultUnsignedHex4(0, "x(mm)");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "y(mm)");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "ang(1/10)deg");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION) {
        if (fillDeviceArgumentList) {
            setFunction("strategy Set Robot Position", 5, 0);
            setArgumentUnsignedHex4(0, "x(mm)");
            setArgumentSeparator(1);
            setArgumentUnsignedHex4(2, "y(mm)");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "ang(1/10)deg");
        }
        return commandLengthValueForMode(mode, 14, 0);
    }
    else if (commandHeader == COMMAND_STRATEGY_SET_ROBOT_POSITION_AS_FIRST_LOCATION_OF_PATH_INDEX) {
        if (fillDeviceArgumentList) {
            setFunction("Set Robot Pos/Ang as Path[index]->loc1", 1, 0);
            setArgumentUnsignedHex2(0, "Path Index");

        }
        return commandLengthValueForMode(mode, 2, 0);
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
    // Debug
    else if (commandHeader == COMMAND_STRATEGY_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Strategy Context Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Print Strategy List
    else if (commandHeader == COMMAND_STRATEGY_LIST_DEBUG) {
        // same input/output
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Strategy List Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Print Current Strategy Item List
    else if (commandHeader == COMMAND_CURRENT_STRATEGY_ITEM_LIST_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Current Strategy Item List");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // Target
    else if (commandHeader == COMMAND_TARGET_LIST_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("targetList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_TARGET_NEXT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("target Next");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
