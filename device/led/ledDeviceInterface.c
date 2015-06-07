#include "ledDeviceInterface.h"

#include "../../device/device.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getLedDeviceName(void) {
    return "LED";
}

int deviceLedGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_WRITE_LED) {
        if (fillDeviceArgumentList) {
            setFunction("Write Led", 2, 0);
            setArgumentUnsignedHex2(0, "Led_index");
            setArgumentUnsignedHex2(1, "Led_state");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    if (commandHeader == COMMAND_TEST_LED) {
        if (fillDeviceArgumentList) {
            setFunction("Test Led", 0, 0);
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LED_DEVICE_HEADER,
    .deviceGetName = &getLedDeviceName,
    .deviceGetInterface = &deviceLedGetInterface
};

DeviceInterface* getLedDeviceInterface() {
    return &deviceInterface;
}
