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
            setFunctionNoArgumentAndNoResult("LightHouse Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// INIT
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_INIT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("LightHouse Init");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// UP
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("LightHouse Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// BOTTOM
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_BOTTOM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("LightHouse Bottom");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// SHOW
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_SHOW) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Light Show");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // OFF
    else if (commandHeader == COMMAND_LIGHT_HOUSE_2020_OFF) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Light Off");
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
