#include "lightHouseDeviceInterface2020.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceLightHouse2020GetName(void) {
    return "lightHouse2020";
}

int deviceLightHouse2020GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // DEBUG
    if (commandHeader == COMMAND_LIGHT_HOUSE_2020_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// INIT
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_INIT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Init");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// UP
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BOTTOM
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_BOTTOM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Bottom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// SHOW
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_SHOW) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// SIMULATE ROBOT PLACED
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_SIMULATE_ROBOT_PLACED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Simulate Robot Placed");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// SIMULATE ROBOT NEAR
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_SIMULATE_ROBOT_NEAR) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Simulate Robot Near");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LIGHT_HOUSE_2020_DEVICE_HEADER,
    .deviceGetName = &deviceLightHouse2020GetName,
    .deviceGetInterface = &deviceLightHouse2020GetInterface
};

DeviceInterface* getLightHouse2020DeviceInterface(void) {
    return &deviceInterface;
}
