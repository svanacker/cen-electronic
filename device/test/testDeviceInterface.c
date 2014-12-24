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
    }
	else if (commandHeader == COMMAND_HEAVY_TEST) {
		if (fillDeviceArgumentList) {
			setFunction("heavyTest", 10, 1);
			setArgumentUnsignedHex2(0, "a");
			setArgumentUnsignedHex2(1, "b");
			setArgumentUnsignedHex4(2, "c");
			setArgumentUnsignedHex4(3, "d");
			setArgumentUnsignedHex2(4, "e");
			setArgumentSeparator(5);
			setArgumentUnsignedHex2(6, "f");
			setArgumentUnsignedHex4(7, "g");
			setArgument(8, DEVICE_ARG_UNSIGNED_HEX_6, "h");
			setArgumentUnsignedHex2(9, "i");
			setResult(0, DEVICE_ARG_UNSIGNED_HEX_6, "result");
		}
		return commandLengthValueForMode(mode, 29, 6);
	}
	// Describe a notification test
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
