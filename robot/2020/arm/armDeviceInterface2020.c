#include "armDeviceInterface2020.h"

#include <stdbool.h>

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceArm2020GetName(void) {
    return "arm2020";
}

int deviceArm2020GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // LATERAL ARM
    if (commandHeader == COMMAND_2020_ARM_CENTER) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Arm Center");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_ARM_LEFT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Arm Left");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_ARM_RIGHT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Arm Right");
        }
        return commandLengthValueForMode(mode, 0, 0);
        // FLAG
    } else if (commandHeader == COMMAND_2020_FLAG_DOWN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Flag Down");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_FLAG_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Flag Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// HOOK
    else if (commandHeader == COMMAND_2020_HOOK_DOWN) {
        if (fillDeviceArgumentList) {
            setFunction("Hook Down", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_DOWN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Hook Down");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_UP) {
        if (fillDeviceArgumentList) {
            setFunction("Hook Up", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Hook Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_TAKE) {
        if (fillDeviceArgumentList) {
            setFunction("Take", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_TAKE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Hook Take");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_RELEASE) {
        if (fillDeviceArgumentList) {
            setFunction("Release", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_RELEASE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Hook Release");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }// HOOK - COMPLEX COMMAND
    else if (commandHeader == COMMAND_2020_HOOK_PREPARE) {
        if (fillDeviceArgumentList) {
            setFunction("Prepare To Take", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_PREPARE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Prepare");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_TAKE_AND_UP) {
        if (fillDeviceArgumentList) {
            setFunction("Take And Up", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_TAKE_AND_UP) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Take And Up");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_DOWN_AND_RELEASE) {
        if (fillDeviceArgumentList) {
            setFunction("Down And Release", 1, 0);
            setArgumentUnsignedHex2(0, "hook index");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_DOWN_AND_RELEASE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("All Down And Release");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = ARM_2020_DEVICE_HEADER,
    .deviceGetName = &deviceArm2020GetName,
    .deviceGetInterface = &deviceArm2020GetInterface
};

DeviceInterface* getArm2020DeviceInterface(void) {
    return &deviceInterface;
}
