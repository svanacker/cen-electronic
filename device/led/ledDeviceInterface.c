#include <stdbool.h>

#include "ledDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"
#include "ledDeviceInterface.h"

const char* deviceLedGetName(void) {
    return "LED";
}

int deviceLedGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_LED_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("write Led", 7, 0);
            setArgumentUnsignedHex2(0, "ledIndex");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "R");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "G");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "B");
        }
        return commandLengthValueForMode(mode, 11, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LED_DEVICE_HEADER,
    .deviceGetName = &deviceLedGetName,
    .deviceGetInterface = &deviceLedGetInterface
};

DeviceInterface* getLedDeviceInterface(void) {
    return &deviceInterface;
}
