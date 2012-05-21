#include "systemDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceSystemDebugGetName() {
    return "systemDebug";
}

int deviceSystemDebugGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_LOG) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setLog", 2);
				setArgumentUnsignedHex2(0, "handlerIdx");
				setArgumentUnsignedHex2(1, "logLevel");
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setLog");
            }
            return 0;
        }
    }
	else if (header == COMMAND_DEBUG_I2C) {
        // NO difference between INPUT and OUTPUT : No Argument
        if (fillDeviceArgumentList) {
			setFunction("i2cDebug", 0);
        }
        return 0;
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSystemDebugGetName,
    .deviceGetInterface = &deviceSystemDebugGetInterface
};

DeviceInterface* getSystemDebugDeviceInterface() {
    return &deviceInterface;
}
