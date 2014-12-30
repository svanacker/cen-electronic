#include "timerDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

const char* deviceTimerGetName(void) {
    return "timer";
}

int deviceTimerGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TIMER_LIST) {
        // Same INPUT/OUTPUT
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showTimerList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = TIMER_DEVICE_HEADER,
    .deviceGetName = &deviceTimerGetName,
    .deviceGetInterface = &deviceTimerGetInterface
};

DeviceInterface* getTimerDeviceInterface(void) {
    return &deviceInterface;
}
