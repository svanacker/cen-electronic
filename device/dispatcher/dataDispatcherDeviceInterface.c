#include "dataDispatcherDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceDataDispatcherDebugGetName(void) {
    return "dataDispatcher";
}

int deviceDataDispatcherGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_DISPATCHER_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showDispatcherList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_PING_DISPATCHER_INDEX) {
        if (fillDeviceArgumentList) {
            setFunction("PingDispatcherIndex", 1, 1);
            setArgumentUnsignedHex2(0, "pingIndex");
            setResultUnsignedHex2(0, "pingIndex");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceDataDispatcherDebugGetName,
    .deviceHeader = DATA_DISPATCHER_DEVICE_HEADER,
    .deviceGetInterface = &deviceDataDispatcherGetInterface
};

DeviceInterface* getDataDispatcherDeviceInterface(void) {
    return &deviceInterface;
}
