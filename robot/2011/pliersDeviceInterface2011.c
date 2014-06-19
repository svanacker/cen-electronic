#include "pliersDeviceInterface2011.h"

#include "../../device/deviceInterface.h"

const char* devicePliers2011GetName() {
    return "pliers2011";
}

int devicePliers2011GetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_PLIERS_2011_CLOSE) {
        // SAME INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pliersClose");
            return 0;
        }
    } else if (header == COMMAND_PLIERS_2011_INIT_CLOSE) {
        // SAME INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("initPliersClose");
            return 0;
        }
    } else if (header == COMMAND_PLIERS_2011_OPEN) {
        // SAME INPUT / OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("pliersOpen");
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &devicePliers2011GetName,
    .deviceGetInterface = &devicePliers2011GetInterface
};

DeviceInterface* getPliers2011DeviceInterface() {
    return &deviceInterface;
}
