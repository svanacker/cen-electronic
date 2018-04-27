#include "strategyDeviceInterface2018.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceStrategy2018GetName(void) {
    return "strategy2018";
}

int deviceStrategy2018GetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == STRATEGY_2018_DISTRIBUTOR_DEBUG_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Strategy 2018 Distributor Debug");;
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    if (commandHeader == STRATEGY_2018_READ_BALL_COLOR_TYPE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Strategy 2018 Read Color Type");;
        }
        return commandLengthValueForMode(mode, 0, 0);
    }    
    else if (commandHeader == STRATEGY_2018_UNICOLOR_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Strategy 2018 Unicolor");;
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = STRATEGY_2018_DEVICE_HEADER,
    .deviceGetName = &deviceStrategy2018GetName,
    .deviceGetInterface = &deviceStrategy2018GetInterface
};

DeviceInterface* getStrategy2018DeviceInterface(void) {
    return &deviceInterface;
}
