#include "goldeniumDeviceInterface2019.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceGoldenium2019GetName(void) {
    return "Goldenium 2019";
}

int deviceGoldenium2019GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Prep Take Gold.");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_2019_FORK_TAKE_GOLDENIUM) {
        if (fillDeviceArgumentList) {
            setFunction("Take Goldenium", 1, 1);
            setArgumentUnsignedChar1(0, "Side (1=L, 2=R)");
            setResultUnsignedChar1(0, "not found=0, found=1");
        }
        return commandLengthValueForMode(mode, 1, 1);
    }
    else if (commandHeader == COMMAND_2019_FORK_DROP_GOLDENIUM) {
        if (fillDeviceArgumentList) {
            setFunction("Drop Goldenium", 1, 0);
            setArgumentUnsignedChar1(0, "Side (1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = GOLDENIUM_2019_DEVICE_HEADER,
    .deviceGetName = &deviceGoldenium2019GetName,
    .deviceGetInterface = &deviceGoldenium2019GetInterface
};

DeviceInterface* getGoldenium2019DeviceInterface(void) {
    return &deviceInterface;
}
