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
	    if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getSonar", 1);
				setArgumentUnsignedHex2(0, "sonarIdx");
            }
            return 2;
    	} else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getSonar", 5);

				setArgumentUnsignedHex4(0, "distCM_1");
				setArgumentSeparator(1);

				setArgumentUnsignedHex4(2, "distCM_2");
				setArgumentSeparator(3);

				setArgumentUnsignedHex4(4, "distCM_3");
            }
            return 14;
        }
    }
	else if (header == COMMAND_SONAR_CHANGE_ADDRESS) {
	    if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("sonarChangeAddress", 2);
				setArgumentUnsignedHex2(0, "oldSonarAddress");
				setArgumentUnsignedHex2(1, "newSonarAddress");
            }
            return 4;
    	} else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("sonarChangeAddress");
			}
            return 0;
        }
	}
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSonarGetName,
//    .deviceGetSoftwareRevision = &deviceSonarGetSoftwareRevision,
    .deviceGetInterface = &deviceSonarGetInterface
};

DeviceInterface* getSonarDeviceInterface() {
    return &deviceInterface;
}
