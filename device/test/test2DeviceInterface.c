#include "test2DeviceInterface.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTest2GetName(void) {
    return "test2";
}

int deviceTest2GetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TEST2) {
        if (fillDeviceArgumentList) {
            setFunction("test2", 2, 1);
            setArgumentUnsignedHex2(0, "a");
            setArgumentUnsignedHex2(1, "b");
            setResultUnsignedHex2(0, "result");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }
    else if (commandHeader == COMMAND_INTENSIVE_TEST_DRIVER) {
        if (fillDeviceArgumentList) {
            setFunction("testDriverIntensive", 1, 0);
            setArgumentUnsignedHex4(0, "count");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = TEST2_DEVICE_HEADER,
    .deviceGetName = &deviceTest2GetName,
    .deviceGetInterface = &deviceTest2GetInterface
};

DeviceInterface* getTest2DeviceInterface() {
    return &deviceInterface;
}
