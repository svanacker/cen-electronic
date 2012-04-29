#include "pinDeviceInterface.h"

#include "../../device/deviceInterface.h"

const char* devicePinGetName() {
    return "pin";
}

unsigned int devicePinGetSoftwareRevision() {
    return 1;
}

int devicePinGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
	// setPin
    if (header == COMMAND_SET_PIN_VALUE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("setPin", 2);
				setArgumentUnsignedHex2(0, "pinIxx");
				setArgumentUnsignedHex2(1, "value"); 
            }
            return 4;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("setPin"); 
            }
            return 0;
        }
    } else if (header == COMMAND_GET_PIN_VALUE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getPin", 1);
				setArgumentUnsignedHex2(0, "pinIdx"); 
            }
            return 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunction("getPin", 1);
				setArgumentUnsignedHex2(0, "value"); 
            }
            return 2;
        }
    }
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &devicePinGetName,
    .deviceGetSoftwareRevision = &devicePinGetSoftwareRevision,
    .deviceGetInterface = &devicePinGetInterface
};

DeviceInterface* getPinDeviceInterface() {
    return &deviceInterface;
}
