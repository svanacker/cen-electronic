#include "systemDeviceInterface.h"

#include "../../device/deviceInterface.h"

static char* picName;

void setPicName(char* aPicName) {
    picName = aPicName;
}

char* getPicName() {
    return picName;
}

const char* deviceSystemGetName() {
    return "system";
}

int deviceSystemGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    // getPicName()
    if (header == COMMAND_PIC_NAME) {
		// Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("getPicName");
        }
        return 0;
    } else if (header == COMMAND_PING) {
		// Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("ping");
        }
        return 0;
    }// wait
    else if (header == COMMAND_WAIT) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("wait", 1);
				setArgumentUnsignedHex4(0, "ms");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("wait");
            }
            return 0;
        }
    }// usage
    else if (header == COMMAND_USAGE) {
		// Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
			setFunctionNoArgument("usage");
        }
        return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSystemGetName,
    .deviceGetInterface = &deviceSystemGetInterface
};

DeviceInterface* getSystemDeviceInterface() {
    return &deviceInterface;
}
