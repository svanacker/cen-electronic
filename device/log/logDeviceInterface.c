#include "logDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

const char* deviceLogGetName(void) {
    return "log";
}

int deviceLogGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_GET_LOG_COUNT) {
       if (fillDeviceArgumentList) {
            setFunction("getLogCount", 0, 1);
            setResultUnsignedHex2(0, "logCount");
       }
       return commandLengthValueForMode(mode, 0, 2);
    }
    if (commandHeader == COMMAND_WRITE_HANDLER_LOG_LEVEL) {
       if (fillDeviceArgumentList) {
            setFunction("setLogHandlerLevel", 2, 0);
            setArgumentUnsignedHex2(0, "handlerIdx");
            setArgumentUnsignedHex2(1, "logLevel");
       }
       return commandLengthValueForMode(mode, 4, 0);
    }
    else if (commandHeader == COMMAND_WRITE_GLOBAL_LOG_LEVEL) {
       if (fillDeviceArgumentList) {
            setFunction("setLogGlobalLevel", 1, 0);
            setArgumentUnsignedHex2(0, "logLevel");
       }
       return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_LOG_HANDLER_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showLog");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_TEST_LOG) {
       setFunction("setTestLog", 1, 0);
       setArgumentUnsignedHex2(0, "logLevel");
       return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LOG_DEVICE_HEADER,
    .deviceGetName = &deviceLogGetName,
    .deviceGetInterface = &deviceLogGetInterface
};

DeviceInterface* getLogDeviceInterface(void) {
    return &deviceInterface;
}
