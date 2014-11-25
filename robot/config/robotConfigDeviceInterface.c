#include "robotConfigDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* getConfigDeviceName(void) {
    return "config";
}

unsigned int getConfigSoftwareRevision(void) {
    return 1;
}

int deviceRobotConfigGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_CONFIG) {
        if (fillDeviceArgumentList) {
            setFunction("robotConfig", 0, 1);
            setResultUnsignedHex4(0, "value");
        }
        return commandLengthValueForMode(mode, 0, 4);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}


static DeviceInterface deviceInterface = {
    .deviceHeader = ROBOT_CONFIG_DEVICE_HEADER,
    .deviceGetName = &getConfigDeviceName,
    
//    .deviceGetSoftwareRevision = &getConfigSoftwareRevision,
    .deviceGetInterface = &deviceRobotConfigGetInterface
};

DeviceInterface* getRobotConfigDeviceInterface() {
    return &deviceInterface;
}
