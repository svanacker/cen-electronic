#include "lcdDeviceInterface.h"

#include "../../common/commons.h"
#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceLCDGetName(void) {
    return "LCD";
}

int deviceLCDGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_LCD) {
        if (fillDeviceArgumentList) {
            setFunction("writeLCD", 1, 0);
            setArgumentFixedCharArray(0, "char Array");
        }
        return commandLengthValueForMode(mode, (LCD_CHAR_COUNT_BY_MESSAGE * 2), 0);
    }
    else if (commandHeader == COMMAND_CLEAR_LCD) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("clear");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_BACKLIGHT_LCD) {
        if (fillDeviceArgumentList) {
            setFunction("backlight", 1, 0);
            setArgumentUnsignedChar1(0, "on/off");
        }
        return commandLengthValueForMode(mode, 1, 0);
    }
    else if (commandHeader == COMMAND_LCD_TEST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("test");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LCD_DEVICE_HEADER,
    .deviceGetName = &deviceLCDGetName,
    .deviceGetInterface = &deviceLCDGetInterface
};

DeviceInterface* getLCDDeviceInterface(void) {
    return &deviceInterface;
}
