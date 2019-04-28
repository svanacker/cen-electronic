#include "testDeviceInterface.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceTestGetName(void) {
    return "test";
}

int deviceTestGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("test", 2, 1);
            setArgumentUnsignedHex2(0, "a");
            setArgumentUnsignedHex2(1, "b");
            setResultUnsignedHex2(0, "result");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }
    else if (commandHeader == COMMAND_SIMPLE_TEST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("simpleTest");
        }
        return commandLengthValueForMode(mode, 0, 0);
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
    // Debug Test
    else if (commandHeader == COMMAND_DEBUG_TEST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("debugTest");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_GENERATE_NOTIFY_TEST) {
        if (fillDeviceArgumentList) {
            setFunction("generateNotifyTest", 1, 0);
            setArgumentUnsignedHex2(0, "notifyTestValue");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    // Handle a notification test
    else if (mode == DEVICE_MODE_NOTIFY) {
        if (commandHeader == NOTIFY_TEST) {
            if (fillDeviceArgumentList) {
                setNotification("notifyTest", 1);
                setArgumentUnsignedHex2(0, "notifyArg0");
            }
            return 2;
        }
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
