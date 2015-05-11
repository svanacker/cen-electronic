#include <stdbool.h>

#include "motionSimulationDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceMotionSimulationGetName(void) {
    return "motionSimulation";
}

int deviceMotionSimulationGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_MOTION_SIMULATION_GET) {
        if (fillDeviceArgumentList) {
            setFunction("getMotionSimulation", 0, 3);
            setResultUnsignedChar1(0, "simulateMotor");
            setResultUnsignedChar1(1, "simulateCoder");
            setResultUnsignedChar1(2, "simulatePosition");
            
        }
        return commandLengthValueForMode(mode, 0, 3);
    }
    else if (commandHeader == COMMAND_MOTION_SIMULATION_SET) {
        if (fillDeviceArgumentList) {
            setFunction("setMotionSimulation", 3, 0);
            setArgumentUnsignedChar1(0, "simulateMotor");
            setArgumentUnsignedChar1(1, "simulateCoder");
            setArgumentUnsignedChar1(2, "simulatePosition");
        }
        return commandLengthValueForMode(mode, 3, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MOTION_SIMULATION_DEVICE_HEADER,
    .deviceGetName = &deviceMotionSimulationGetName,
    .deviceGetInterface = &deviceMotionSimulationGetInterface
};

DeviceInterface* getMotionSimulationDeviceInterface(void) {
    return &deviceInterface;
}
