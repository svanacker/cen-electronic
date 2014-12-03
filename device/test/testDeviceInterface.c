#include "testDeviceInterface.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTestGetName(void) {
    return "test";
}

int deviceTestGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("test", 2, 1);
            setArgumentUnsignedHex2(0, "a");
            setArgumentUnsignedHex2(1, "b");
            setResultUnsignedHex2(0, "result");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }// Describe a notification test
    else if (commandHeader == COMMAND_NOTIFY_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("notifyTest", 1, 1);
            setArgumentUnsignedHex2(0, "arg");
            setResultUnsignedHex2(0, "arg");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = TEST_DEVICE_HEADER,
    .deviceGetName = &deviceTestGetName,
    .deviceGetInterface = &deviceTestGetInterface
};

DeviceInterface* getTestDeviceInterface() {
    return &deviceInterface;
}
