#include "systemDebugDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceSystemDebugGetName() {
    return "systemDebug";
}

int deviceSystemDebugGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_WRITE_LOG_LEVEL) {
       if (fillDeviceArgumentList) {
            setFunction("setLog", 2, 0);
            setArgumentUnsignedHex2(0, "handlerIdx");
            setArgumentUnsignedHex2(1, "logLevel");
        }
        commandLengthValueForMode(mode, 4, 0);
    }
    else if (header == COMMAND_DISPATCHER_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showDispatcherList");
        }
        return 0;
    }
    else if (header == COMMAND_SERIAL_INPUT_BUFFERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showSerialInputBuffers");
        }
        return 0;
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSystemDebugGetName,
    .deviceHeader = SYSTEM_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceSystemDebugGetInterface
};

DeviceInterface* getSystemDebugDeviceInterface() {
    return &deviceInterface;
}
