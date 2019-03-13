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
            setArgumentUnsignedChar1(0, "servo Index (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        if (fillDeviceArgumentList) {
            setFunction("Fork Simple Puck", 1, 0);
            setArgumentUnsignedChar1(0, "servo Idx (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        if (fillDeviceArgumentList) {
            setFunction("Fork Double Puck", 1, 0);
            setArgumentUnsignedChar1(0, "servo Idx (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    // FORK PUSH
    else if (commandHeader == COMMAND_2019_FORK_PUSH_OFF) {
        if (fillDeviceArgumentList) {
            setFunction("Push Off", 1, 0);
            setArgumentUnsignedChar1(0, "servo Index (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_PUSH_ON) {
        if (fillDeviceArgumentList) {
            setFunction("Push On", 1, 0);
            setArgumentUnsignedChar1(0, "servo Idx (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    // INIT
    else if (commandHeader == COMMAND_2019_FORK_INIT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Fork Init");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }    
    // TAKE
    else if (commandHeader == COMMAND_2019_FORK_TAKE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Take");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }    
    // DROP
    else if (commandHeader == COMMAND_2019_FORK_RELEASE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Release");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // SCAN
    else if (commandHeader == COMMAND_2019_FORK_SCAN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Scan");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
