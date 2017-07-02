#include "robotConfigDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getConfigDeviceName(void) {
    return "config";
}

unsigned int getConfigSoftwareRevision(void) {
    return 1;
}

int deviceRobotConfigGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_GET_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunction("getConfig", 0, 1);
            setResultUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    else if (commandHeader == COMMAND_SET_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunction("setConfig", 1, 0);
            setArgumentUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
	else if (commandHeader == COMMAND_CONFIG_DEBUG) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("debug");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}

    return DEVICE_HEADER_NOT_HANDLED;
}


static DeviceInterface deviceInterface = {
    .deviceHeader = ROBOT_CONFIG_DEVICE_HEADER,
    .deviceGetName = &getConfigDeviceName,
    .deviceGetInterface = &deviceRobotConfigGetInterface
};

DeviceInterface* getRobotConfigDeviceInterface() {
    return &deviceInterface;
}
