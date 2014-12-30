#include "relayDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceRelayGetName() {
    return "relay";
}

unsigned int deviceRelayGetSotwareRevision() {
    return 1;
}

int deviceRelayGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_SET_RELAY) {
        if (fillDeviceArgumentList) {
            setFunction("setRelay", 2, 0);
            setArgumentUnsignedHex2(0, "RelayIdx");
            setArgumentUnsignedChar1(1, "Value");
        }
        return commandLengthValueForMode(mode, 3, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = RELAY_DEVICE_HEADER,
    .deviceGetName = &deviceRelayGetName,
    .deviceGetInterface = &deviceRelayGetInterface
};

DeviceInterface* getRelayDeviceInterface() {
    return &deviceInterface;
}
