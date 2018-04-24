#include "launcherDeviceInterface2018.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceLauncher2018GetName(void) {
    return "launcher2018";
}

int deviceLauncher2018GetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // LAUNCHER
    if (commandHeader == LAUNCHER_PREPARE_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("prepare Ball", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == LAUNCHER_SEND_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Send Ball", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    // LIGHT
    else if (commandHeader == LAUNCHER_LIGHT_ON_SERVO_MOVE_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Switch Light", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    // DISTRIBUTOR
    else if (commandHeader == DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Distributor Eject Dirty Ball");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == DISTRIBUTOR_NEXT_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Distributor Next Clean Ball", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == LAUNCHER_SEQUENCE_CLEAN_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Sequence Clean Ball", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LAUNCHER_2018_DEVICE_HEADER,
    .deviceGetName = &deviceLauncher2018GetName,
    .deviceGetInterface = &deviceLauncher2018GetInterface
};

DeviceInterface* getLauncher2018DeviceInterface(void) {
    return &deviceInterface;
}
