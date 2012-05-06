#include "robotConfigDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* getConfigDeviceName(void) {
    return "config";
}

unsigned int getConfigSoftwareRevision(void) {
    return 1;
}

int deviceRobotConfigGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (mode == DEVICE_MODE_INPUT) {
        if (header == COMMAND_CONFIG) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("robotConfig");
            }
            return 0;
        }
    } else if (mode == DEVICE_MODE_OUTPUT) {
        if (header == COMMAND_CONFIG) {
            if (fillDeviceArgumentList) {
				setFunction("robotConfig", 1);
				setArgumentUnsignedHex4(0, "value");
            }
            return 4;
        }

    }
    return DEVICE_HEADER_NOT_HANDLED;
}


static DeviceInterface deviceInterface = {
    .deviceGetName = &getConfigDeviceName,
//    .deviceGetSoftwareRevision = &getConfigSoftwareRevision,
    .deviceGetInterface = &deviceRobotConfigGetInterface
};

DeviceInterface* getRobotConfigDeviceInterface() {
    return &deviceInterface;
}
