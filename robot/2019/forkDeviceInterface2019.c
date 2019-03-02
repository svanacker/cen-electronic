#include "forkDeviceInterface2019.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceFork2019GetName(void) {
    return "fork2019";
}

int deviceFork2019GetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // ELEVATOR
    if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Elevator Bottom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Elevator Double Puck Pos.");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Elevator Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // FORK
    else if (commandHeader == COMMAND_2019_FORK_BACK) {
        if (fillDeviceArgumentList) {
            setFunction("Fork Back", 1, 0);
            setArgumentUnsignedChar1(0, "servo Index");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        if (fillDeviceArgumentList) {
            setFunction("Fork Simple Puck", 1, 0);
            setArgumentUnsignedChar1(0, "servo Index");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        if (fillDeviceArgumentList) {
            setFunction("Fork Double Puck", 1, 0);
            setArgumentUnsignedChar1(0, "servo Index");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = FORK_2019_DEVICE_HEADER,
    .deviceGetName = &deviceFork2019GetName,
    .deviceGetInterface = &deviceFork2019GetInterface
};

DeviceInterface* getFork2019DeviceInterface(void) {
    return &deviceInterface;
}
