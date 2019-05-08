#include "electronLauncherDeviceInterface2019.h"

#include <stdbool.h>

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceElectronLauncher2019GetName(void) {
    return "electronLauncher2019";
}

int deviceElectronLauncher2019GetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // DEBUG
    if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // INIT
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_INIT) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Init");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // LAUNCH
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_LAUNCH) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Launch");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // SHOW
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SHOW) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Show");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // SIMULATE ROBOT PLACED
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Simulate Robot Placed");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // SIMULATE ROBOT PLACED
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED_AND_MOVED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Simulate Robot Placed And Moved");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = ELECTRON_LAUNCHER_2019_DEVICE_HEADER,
    .deviceGetName = &deviceElectronLauncher2019GetName,
    .deviceGetInterface = &deviceElectronLauncher2019GetInterface
};

DeviceInterface* getElectronLauncher2019DeviceInterface(void) {
    return &deviceInterface;
}
