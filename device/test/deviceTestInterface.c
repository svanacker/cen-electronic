#include "deviceTestInterface.h"

#include "../../common/commons.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTestGetName() {
    return "test";
}

int deviceTestGetInterface(char header, int mode,
        bool fillDeviceArgumentList) {
    if (header == COMMAND_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("test", 2, 1);
            setArgumentUnsignedHex2(0, "a");
            setArgumentUnsignedHex2(1, "b");
            setResultUnsignedHex2(0, "result");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }// Describe a notification test
    else if (header == COMMAND_NOTIFY_TEST) {
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
    .deviceHeader = DEVICE_TEST_HEADER,
    .deviceGetName = &deviceTestGetName,
    .deviceGetInterface = &deviceTestGetInterface
};

DeviceInterface* getTestDeviceInterface() {
    return &deviceInterface;
}
