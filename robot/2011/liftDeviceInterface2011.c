#include "liftDeviceInterface2011.h"

#include "../../device/deviceInterface.h"

const char* deviceLift2011GetName() {
    return "lift2011";
}

unsigned int deviceLift2011GetSotwareRevision() {
    return 1;
}

int deviceLift2011GetInterface(char commandHeader, DeviceInterfaceMode mode, DeviceArgumentList* deviceArgumentList) {
    if (commandHeader == COMMAND_LIFT_2011_BOTTOM) {
        if (mode == DEVICE_MODE_INPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftBottom";
                deviceArgumentList->size = 0;
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftBottom";
                deviceArgumentList->size = 0;
            }
            return 0;
        }
    }
    if (commandHeader == COMMAND_LIFT_2011_UP) {
        if (mode == DEVICE_MODE_INPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftUp";
                deviceArgumentList->size = 0;
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftUp";
                deviceArgumentList->size = 0;
            }
            return 0;
        }
    } else if (commandHeader == COMMAND_LIFT_2011_DOWN) {
        if (mode == DEVICE_MODE_INPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftDown";
                deviceArgumentList->size = 0;
            }
            return 0;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (deviceArgumentList) {
                deviceArgumentList->functionName = "liftDown";
                deviceArgumentList->size = 0;
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceLift2011GetName,
    .deviceGetSoftwareRevision = &deviceLift2011GetSotwareRevision,
    .deviceGetInterface = &deviceLift2011GetInterface
};

DeviceInterface* getLift2011DeviceInterface() {
    return &deviceInterface;
}
