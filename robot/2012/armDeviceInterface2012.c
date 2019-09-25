#include "armDeviceInterface2012.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceArm2012GetName(void) {
    return "arm2012";
}

int deviceArm2012GetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_ARM_2012_UP) {
        if (fillDeviceArgumentList) {
            setFunction("armUp", 1, 0);
            setArgumentUnsignedHex2(0, "armIdx");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_ARM_2012_DOWN) {
        if (fillDeviceArgumentList) {
            setFunction("armDown", 1, 0);
            setArgumentUnsignedHex2(0, "armIdx");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceArm2012GetName,
    .deviceHeader = ARM_DEVICE_2012_HEADER,
    .deviceGetInterface = &deviceArm2012GetInterface
};

DeviceInterface* getArm2012DeviceInterface(void) {
    return &deviceInterface;
}
