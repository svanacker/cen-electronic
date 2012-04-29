#include "codersDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"

static char* CLEAR_CODERS_STRING = "clrCoders";
static char* CODERS_VALUE_STRING = "codersVal";
static char* DEBUG_CODERS_VALUE_STRING = "dbgCodersVal";

unsigned int getCodersSoftwareRevision(void) {
    return 1;
}

const char* getCodersDeviceName(void) {
    return "Hctl Coders";
}

int deviceCodersGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_CLEAR_CODERS) {
		// Same INPUT / OUTPUT
		if (fillDeviceArgumentList) {
			setFunctionNoArgument(CLEAR_CODERS_STRING);
		}
        return 0;
    } else if (header == COMMAND_GET_WHEEL_POSITION) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument(CODERS_VALUE_STRING);
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction(CODERS_VALUE_STRING, 3);
				setArgument(0, DEVICE_ARG_UNSIGNED_HEX_8, "left");
                setArgumentSeparator(1);
				setArgument(2, DEVICE_ARG_UNSIGNED_HEX_8, "right");
            }
            return 17;
        }
    } else if (header == COMMAND_DEBUG_GET_WHEEL_POSITION) {
		// Same INPUT / OUTPUT
		if (fillDeviceArgumentList) {
			setFunctionNoArgument(DEBUG_CODERS_VALUE_STRING);
		}
		return 0;
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &getCodersDeviceName,
    .deviceGetSoftwareRevision = &getCodersSoftwareRevision,
    .deviceGetInterface = &deviceCodersGetInterface
};

DeviceInterface* getCodersDeviceInterface() {
    return &deviceInterface;
}
