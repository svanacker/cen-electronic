#include "systemDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

static char* picName;

void setPicName(char* aPicName) {
    picName = aPicName;
}

char* getPicName(void) {
    return picName;
}

const char* deviceSystemGetName(void) {
    return "system";
}

int deviceSystemGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // getPicName()
    if (commandHeader == COMMAND_PIC_NAME) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("getPicName");
        }
        return 0;
    }
    // getPicName()
    else if (commandHeader == COMMAND_DEVICE_LIST) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("deviceList");
        }
        return 0;
    }
    else if (commandHeader == COMMAND_PING) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("ping");
        }
        return 0;
    }// wait
    else if (commandHeader == COMMAND_WAIT) {
        if (fillDeviceArgumentList) {
            setFunction("wait", 1, 0);
            setArgumentUnsignedHex4(0, "ms");                
        }
        return commandLengthValueForMode(mode, 4, 0);
    }// usage
    else if (commandHeader == COMMAND_USAGE) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("usage");
        }
        return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = SYSTEM_DEVICE_HEADER,
    .deviceGetName = &deviceSystemGetName,
    .deviceGetInterface = &deviceSystemGetInterface
};

DeviceInterface* getSystemDeviceInterface(void) {
    return &deviceInterface;
}
