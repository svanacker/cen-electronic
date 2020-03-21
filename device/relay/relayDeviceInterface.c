#include <stdbool.h>

#include "relayDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceRelayGetName(void) {
    return "relay";
}

int deviceRelayGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_WRITE_RELAY) {
        if (fillDeviceArgumentList) {
            setFunction("write Relay", 3, 0);
            setArgumentUnsignedHex2(0, "Relay Index");
            setArgumentSeparator(1);
            setArgumentUnsignedChar1(2, "Value");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (commandHeader == COMMAND_READ_RELAY) {
        if (fillDeviceArgumentList) {
            setFunction("read Relay", 1, 1);
            setArgumentUnsignedHex2(0, "Relay Index");
            setResultUnsignedChar1(0, "Value");
        }
        return commandLengthValueForMode(mode, 2, 1);
    } else if (commandHeader == COMMAND_RELAY_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug Relay");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = RELAY_DEVICE_HEADER,
    .deviceGetName = &deviceRelayGetName,
    .deviceGetInterface = &deviceRelayGetInterface
};

DeviceInterface* getRelayDeviceInterface(void) {
    return &deviceInterface;
}
