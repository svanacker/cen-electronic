#include "deviceTestInterface.h"

#include "../../common/commons.h"

#include "../../device/deviceInterface.h"

const char* deviceTestGetName() {
    return "test";
}

int deviceTestGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_TEST) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("test", 2);
				setArgumentUnsignedHex2(0, "arg1");
				setArgumentUnsignedHex2(1, "arg2");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("test", 1);
				setArgumentUnsignedHex2(0, "result");
            }
            return 2;
        }
    }// Describe a notification test
    else if (header == COMMAND_NOTIFY_TEST) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("notifyTest", 1);
				setArgumentUnsignedHex2(0, "arg");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("notifyTest", 1);
				setArgumentUnsignedHex2(0, "arg");
            }
            return 2;
        }

    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = DEVICE_TEST_HEADER,
    .deviceGetName = &deviceTestGetName,
    .deviceGetInterface = &deviceTestGetInterface
};

DeviceInterface* getTestDeviceInterface() {
    return &deviceInterface;
}
