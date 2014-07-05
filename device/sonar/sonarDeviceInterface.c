#include "sonarDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* deviceSonarGetName() {
    return "sonar";
}

unsigned int deviceSonarGetSoftwareRevision() {
    return 1;
}

int deviceSonarGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_GET_SONAR) {
        if (fillDeviceArgumentList) {
            setFunction("getSonar", 1, 5);
            setArgumentUnsignedHex2(0, "sonarIdx");

            setResultUnsignedHex4(0, "distCM_1");
            setResultSeparator(1);
            
            setResultUnsignedHex4(2, "distCM_2");
            setResultSeparator(3);
            
            setResultUnsignedHex4(4, "distCM_3");
        }
        return commandLengthValueForMode(mode, 2, 14);
    }
    else if (header == COMMAND_SONAR_CHANGE_ADDRESS) {
        if (fillDeviceArgumentList) {
            setFunction("sonarChangeAddress", 2, 0);
            setArgumentUnsignedHex2(0, "oldSonarAddress");
            setArgumentUnsignedHex2(1, "newSonarAddress");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSonarGetName,
    .deviceHeader = SONAR_DEVICE_HEADER,
//    .deviceGetSoftwareRevision = &deviceSonarGetSoftwareRevision,
    .deviceGetInterface = &deviceSonarGetInterface
};

DeviceInterface* getSonarDeviceInterface() {
    return &deviceInterface;
}
