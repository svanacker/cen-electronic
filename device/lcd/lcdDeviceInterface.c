#include "lcdDeviceInterface.h"

#include "../../common/commons.h"
#include "../../device/deviceInterface.h"

const char* deviceLCDGetName() {
    return "LCD";
}

int deviceLCDGetInterface(char commandHeader, int mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_LCD) {
        if (fillDeviceArgumentList) {
            setFunction("writeLCD", LCD_CHAR_COUNT_BY_MESSAGE + 2, 0);
            setArgumentUnsignedHex2(0, "length");
            int i;
            for (i = 1; i <= LCD_CHAR_COUNT_BY_MESSAGE; i++) {
                setArgumentUnsignedHex2(i, "char x");
            }
        }
        return commandLengthValueForMode(mode, (LCD_CHAR_COUNT_BY_MESSAGE * 2) + 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LCD_DEVICE_HEADER,
    .deviceGetName = &deviceLCDGetName,
    .deviceGetInterface = &deviceLCDGetInterface
};

DeviceInterface* getLCDDeviceInterface() {
    return &deviceInterface;
}
