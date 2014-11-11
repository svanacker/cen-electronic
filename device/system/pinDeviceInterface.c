#include "pinDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* devicePinGetName() {
    return "pin";
}

unsigned int devicePinGetSoftwareRevision() {
    return 1;
}

int devicePinGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    // setPin
    if (header == COMMAND_SET_PIN_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("setPin", 2, 0);
            setArgumentUnsignedHex2(0, "pinIxx");
            setArgumentUnsignedHex2(1, "value"); 
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (header == COMMAND_GET_PIN_VALUE) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
                setFunction("getPin", 1, 1);
                setArgumentUnsignedHex2(0, "pinIdx"); 
                setResultUnsignedHex2(0, "value");
            }
            return commandLengthValueForMode(mode, 2, 2);
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &devicePinGetName,
	.deviceHeader = PIN_DEVICE_HEADER,
    .deviceGetInterface = &devicePinGetInterface
};

DeviceInterface* getPinDeviceInterface() {
    return &deviceInterface;
}
