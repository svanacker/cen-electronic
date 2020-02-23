#include <stdbool.h>

#include "lcdDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"
#include "ledDeviceInterface.h"

const char* deviceLcdGetName(void) {
    return "LCD";
}

int deviceLcdGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_LED_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("write Led", 0, 5);
            setArgumentUnsignedHex2(0, "R");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "G");
            setArgumentSeparator(3);
            setArgumentUnsignedHex4(4, "B");
        }
        return commandLengthValueForMode(mode, 0, 14);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = LCD_DEVICE_HEADER,
    .deviceGetName = &deviceLcdGetName,
    .deviceGetInterface = &deviceLcdGetInterface
};

DeviceInterface* getLcdDeviceInterface(void) {
    return &deviceInterface;
}
