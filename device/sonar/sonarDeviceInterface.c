#include <stdbool.h>

#include "sonarDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceSonarGetName() {
    return "sonar";
}

int deviceSonarGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_GET_SONAR) {
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
    } else if (commandHeader == COMMAND_SONAR_CHANGE_ADDRESS) {
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
    .deviceGetInterface = &deviceSonarGetInterface
};

DeviceInterface* getSonarDeviceInterface() {
    return &deviceInterface;
}
