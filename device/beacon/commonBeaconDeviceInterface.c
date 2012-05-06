#include "commonBeaconDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* commonBeaconDeviceGetName() {
    return "commonBeacon";
}

unsigned int commonBeaconDeviceGetSoftwareRevision() {
    return 1;
}

int commonBeaconDeviceGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
	// Redirection
    if (header == COMMAND_REDIRECT_TO_JENNIC) {
		// same output / input
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("redirectToJennic");
		}
		return 0;
    }
	else if (header == COMMAND_LOCAL_LIGHT_ON) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("LocalLightOn");
		}
		return 0;
	}
	else if (header == COMMAND_LOCAL_LIGHT_OFF) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("LocalLightOff");
		}
		return 0;
	}
	else if (header == COMMAND_SHOW_DATA_FROM_JENNIC) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("showDataFromJennic");
		}
		return 0;
	}
	else if (header == COMMAND_RESET_JENNIC) {
		// both input/output
		if (fillDeviceArgumentList) {
			setFunctionNoArgument("resetJennic");
		}
		return 0;
	}

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &commonBeaconDeviceGetName,
//    .deviceGetSoftwareRevision = &commonBeaconDeviceGetSoftwareRevision,
    .deviceGetInterface = &commonBeaconDeviceGetInterface
};

DeviceInterface* getCommonBeaconDeviceInterface() {
    return &deviceInterface;
}
