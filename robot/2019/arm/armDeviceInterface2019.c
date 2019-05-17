#include "armDeviceInterface2019.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceArm2019GetName(void) {
    return "arm2019";
}

int deviceArm2019GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // ARM ON & OFF
    if (commandHeader == COMMAND_2019_ARM_ON) {
        if (fillDeviceArgumentList) {
            setFunction("Arm On", 1, 0);
            setArgumentUnsignedChar1(0, "servo Idx (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    } else if (commandHeader == COMMAND_2019_ARM_OFF) {
        if (fillDeviceArgumentList) {
            setFunction("Arm Off", 1, 0);
            setArgumentUnsignedChar1(0, "servo Idx (0:L/R, 1=L, 2=R)");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = ARM_2019_DEVICE_HEADER,
    .deviceGetName = &deviceArm2019GetName,
    .deviceGetInterface = &deviceArm2019GetInterface
};

DeviceInterface* getArm2019DeviceInterface(void) {
    return &deviceInterface;
}
