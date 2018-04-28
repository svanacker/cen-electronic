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
    else if (commandHeader == DISTRIBUTOR_LOAD_NEXT_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Load Next Ball", 1, 1);
            setResultUnsignedHex2(0, "stop distance");
            setArgumentUnsignedHex2(0, "Load Direction : Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    // 1 ball right Color
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_BALL_COMMAND) {
        if (fillDeviceArgumentList) {
            setFunction("Load and send ball", 1, 0);
            setResultUnsignedHex2(0, "stop distance");
            setArgumentUnsignedHex2(0, "Load Direction : Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_UNICOLOR_BALL_LIST) {
        if (fillDeviceArgumentList) {
            setFunction("Load and send unicolor Ball List", 1, 0);
            setArgumentUnsignedHex2(0, "Left (00) / Right (01)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_MIXED_BALL_LIST) {
        if (fillDeviceArgumentList) {
            setFunction("Load and send mixed Ball List", 1, 0);
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
