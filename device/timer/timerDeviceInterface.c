#include <stdbool.h>

#include "timerDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceConstants.h"

const char* deviceTimerGetName(void) {
    return "timer";
}

int deviceTimerGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_TIMER_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showTimerList");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_TIMER_COUNT) {
        if (fillDeviceArgumentList) {
            setFunction("timerCount", 0, 1);
            setResultUnsignedHex2(0, "count");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == COMMAND_TIMER_READ) {
        if (fillDeviceArgumentList) {
            setFunction("timerRead", 1, 11);
            setArgumentUnsignedHex2(0, "timerIndex");
            setResultUnsignedHex2(0, "timerIndex");
            setResultSeparator(1);
            setResultUnsignedHex4(2, "timeDiviser");
            setResultSeparator(3);
            setResultUnsignedHex4(4, "timeInternalCounter");
            setResultSeparator(5);
            setResultUnsignedHex6(6, "time");
            setResultSeparator(7);
            setResultUnsignedHex6(8, "markTime");
            setResultSeparator(9);
            setResultUnsignedChar1(10, "enabled");
        }
        return commandLengthValueForMode(mode, 2, 28);
    }
    else if (commandHeader == COMMAND_TIMER_ENABLE_DISABLE) {
        if (fillDeviceArgumentList) {
            setFunction("timerEnable", 3, 0);
            setArgumentUnsignedHex2(0, "timerIndex");
            setArgumentSeparator(1);
            setArgumentUnsignedChar1(2, "enable/disable");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    // Mark
    else if (commandHeader == COMMAND_TIMER_TIME_SINCE_LAST_MARK) {
        if (fillDeviceArgumentList) {
            setFunction("timeSinceLastMark", 1, 1);
            setArgumentUnsignedHex2(0, "timerIndex");
            setResultUnsignedHex6(0, "mark");
        }
        return commandLengthValueForMode(mode, 2, 6);
    }
    else if (commandHeader == COMMAND_TIMER_MARK) {
        if (fillDeviceArgumentList) {
            setFunction("mark Timer !", 1, 0);
            setArgumentUnsignedHex2(0, "timerIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_TIMER_TIMEOUT) {
        if (fillDeviceArgumentList) {
            setFunction("timeout check", 3, 3);
            setArgumentUnsignedHex2(0, "timerIndex");
            setArgumentSeparator(1);
            setArgumentUnsignedHex6(2, "time to check");
            setResultUnsignedHex2(0, "timerIndex");
            setResultSeparator(1);
            setResultUnsignedChar1(2, "timeout or not");
        }
        return commandLengthValueForMode(mode, 9, 4);
    }
    
    // Demo
    else if (commandHeader == COMMAND_TIMER_DEMO) {
        if (fillDeviceArgumentList) {
            setFunction("enableDisableTimerDemo", 1, 0);
            setArgumentUnsignedChar1(0, "enable/disable");
        }
        return commandLengthValueForMode(mode, 1, 0);
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
