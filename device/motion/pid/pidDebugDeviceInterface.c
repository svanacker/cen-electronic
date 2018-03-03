#include <stdbool.h>

#include "pidDebugDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getPidDebugDeviceName(void) {
    return "Pid Debug";
}

int devicePidDebugGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // MOTION PARAMETERS DEBUG
    if (commandHeader == COMMAND_MOTION_PARAMETERS_DEBUG) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("debugParameters");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
    // PID DEBUG
    if (commandHeader == COMMAND_END_MOTION_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("motionEndDebug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_DEBUG_DATA_PID_CONSOLE) {
        if (fillDeviceArgumentList) {
            setFunction("sendDbgDataPidConsole", 0, 0);
        }
        return commandLengthValueForMode(mode, 0, 0);
	} else if (commandHeader == COMMAND_PID_MOTION_PARAMETER_DEBUG) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("pidMotionParameterDebug");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	else if (commandHeader == COMMAND_DEBUG_PID_PARAMETERS) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("pidParametersDebug");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PID_DEBUG_DEVICE_HEADER,
    .deviceGetName = &getPidDebugDeviceName,
    .deviceGetInterface = &devicePidDebugGetInterface
};

DeviceInterface* getPidDebugDeviceInterface() {
    return &deviceInterface;
}
