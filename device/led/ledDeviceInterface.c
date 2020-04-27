#include <stdbool.h>

#include "ledDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"
#include "ledDeviceInterface.h"

const char* deviceLedGetName(void) {
    return "LED";
}

int deviceLedGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_LED_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("write Led", 7, 0);
            setArgumentUnsignedHex2(0, "ledIndex");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "R");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "G");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "B");
        }
        return commandLengthValueForMode(mode, 11, 0);
    }
    else if (commandHeader == COMMAND_LED_RED) {
        if (fillDeviceArgumentList) {
            setFunction("write Led RED", 1, 0);
            setArgumentUnsignedHex2(0, "ledIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_LED_GREEN) {
        if (fillDeviceArgumentList) {
            setFunction("write Led GREEN", 1, 0);
            setArgumentUnsignedHex2(0, "ledIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_LED_BLUE) {
        if (fillDeviceArgumentList) {
            setFunction("write Led BLUE", 1, 0);
            setArgumentUnsignedHex2(0, "ledIndex");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    // ALL LEDS
    else if (commandHeader == COMMAND_LED_CLEAR_ALL) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Clear All Led");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_LED_ALL_ON) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Led All On");
        }
        return commandLengthValueForMode(mode, 0, 0);    
    }
    // Specific Color
    else if (commandHeader == COMMAND_LED_ALL_RED) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Led All Red");
        }
        return commandLengthValueForMode(mode, 0, 0);    
    }
    else if (commandHeader == COMMAND_LED_ALL_GREEN) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Led All Green");
        }
        return commandLengthValueForMode(mode, 0, 0);    
    }
    else if (commandHeader == COMMAND_LED_ALL_BLUE) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Led All Blue");
        }
        return commandLengthValueForMode(mode, 0, 0);    
    }
    // DISTANCE
    else if (commandHeader == COMMAND_LED_ALL_AS_DISTANCE) {
        if (fillDeviceArgumentList) {
            setFunction("All Led as distance", 1, 0);
            setArgumentUnsignedHex2(0, "distance (0..255)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LED_DEVICE_HEADER,
    .deviceGetName = &deviceLedGetName,
    .deviceGetInterface = &deviceLedGetInterface
};

DeviceInterface* getLedDeviceInterface(void) {
    return &deviceInterface;
}
