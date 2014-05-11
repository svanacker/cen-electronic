#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* commonBeaconDeviceGetName() {
    return "commonBeacon";
}

int commonBeaconDeviceGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
	// Redirection
    if (commandHeader == COMMAND_REDIRECT_TO_JENNIC) {
		// same output / input
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("redirectToJennic");
		}
		return 0;
    }
	else if (commandHeader == COMMAND_LOCAL_LIGHT) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("localLight");
				setArgumentUnsignedHex4(2, "on/off");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("localLight", 0);
            }
            return 0;
        }
	}
	else if (commandHeader == COMMAND_SHOW_DATA_FROM_JENNIC) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("showDataFromJennic");
		}
		return 0;
	}
	else if (commandHeader == COMMAND_RESET_JENNIC) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("resetJennic");
		}
		return 0;
	}

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = COMMON_BEACON_DEVICE_HEADER,
    .deviceGetName = &commonBeaconDeviceGetName,
    .deviceGetInterface = &commonBeaconDeviceGetInterface
};

DeviceInterface* getCommonBeaconDeviceInterface() {
    return &deviceInterface;
}
