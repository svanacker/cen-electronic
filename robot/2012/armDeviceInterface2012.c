#include "armDeviceInterface2012.h"

#include "../../device/deviceInterface.h"

const char* deviceArm2012GetName() {
    return "arm2012";
}

unsigned int deviceArm2012GetSoftwareRevision() {
    return 1;
}

int deviceArm2012GetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_ARM_2012_UP) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("armUp", 1);
				setArgumentUnsignedHex2(0, "armIdx");
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("armUp");
            }
            return 0;
        }
    } else if (header == COMMAND_ARM_2012_DOWN) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("armDown", 1);
				setArgumentUnsignedHex2(0, "armIdx");
           }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("armDown");
            }
            return 0;
        }
	}
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceArm2012GetName,
//    .deviceGetSoftwareRevision = &deviceArm2012GetSoftwareRevision,
    .deviceGetInterface = &deviceArm2012GetInterface
};

DeviceInterface* getArm2012DeviceInterface() {
    return &deviceInterface;
}
