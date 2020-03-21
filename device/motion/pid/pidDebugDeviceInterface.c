#include <stdbool.h>

#include "pidDebugDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getPidDebugDeviceName(void) {
    return "Pid Debug";
}

int devicePidDebugGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // MOTION PARAMETERS DEBUG
    if (commandHeader == COMMAND_MOTION_PARAMETERS_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Motion Parameters Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    // PID DEBUG
    if (commandHeader == COMMAND_END_MOTION_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Motion End Detection Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_DEBUG_DATA_PID_CONSOLE) {
        if (fillDeviceArgumentList) {
            setFunction("PID Computation Values Table", 0, 0);
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_PID_MOTION_INSTRUCTION_TABLE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Motion Instruction Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_DEBUG_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("PID Parameters Table (by Pid Type)");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_PID_TRAJECTORY_TABLE) {
        if (fillDeviceArgumentList) {
            setFunction("PID Trajectory Table", 1, 0);
            setArgumentFloatHex4(0, "pidTime Interval (milliSeconds). > 5");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PID_DEBUG_DEVICE_HEADER,
    .deviceGetName = &getPidDebugDeviceName,
    .deviceGetInterface = &devicePidDebugGetInterface
};

DeviceInterface* getPidDebugDeviceInterface() {
    return &deviceInterface;
}
