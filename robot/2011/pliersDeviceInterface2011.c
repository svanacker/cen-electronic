#include "pliersDeviceInterface2011.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* devicePliers2011GetName() {
    return "pliers2011";
}

int devicePliers2011GetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_PLIERS_2011_CLOSE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pliersClose");
            return 0;
        }
    } else if (commandHeader == COMMAND_PLIERS_2011_INIT_CLOSE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("initPliersClose");
            return 0;
        }
    } else if (commandHeader == COMMAND_PLIERS_2011_OPEN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pliersOpen");
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
	.deviceHeader = PLIERS_DEVICE_2011_HEADER,
    .deviceGetName = &devicePliers2011GetName,
    .deviceGetInterface = &devicePliers2011GetInterface
};

DeviceInterface* getPliers2011DeviceInterface() {
    return &deviceInterface;
}
