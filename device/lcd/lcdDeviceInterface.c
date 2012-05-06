#include "lcdDeviceInterface.h"

#include "../../common/commons.h"
#include "../../device/deviceInterface.h"

const char* deviceLCDGetName() {
    return "LCD";
}

unsigned int deviceLCDGetSoftwareRevision() {
    return 1;
}

int deviceLCDGetInterface(char header, int mode, BOOL fillDeviceArgumentList) {
    if (header == COMMAND_LCD) {
        if (mode == DEVICE_MODE_INPUT) {
            if (fillDeviceArgumentList) {
				setFunction("writeLCD", LCD_CHAR_COUNT_BY_MESSAGE + 2);
				setArgumentUnsignedHex2(0, "length");
                int i;
                for (i = 1; i <= LCD_CHAR_COUNT_BY_MESSAGE; i++) {
					setArgumentUnsignedHex2(i, "char x");
                }
            }
            return (LCD_CHAR_COUNT_BY_MESSAGE * 2) + 2;
        } else if (mode == DEVICE_MODE_OUTPUT) {
            if (fillDeviceArgumentList) {
				setFunctionNoArgument("writeLCD");
            }
            return 0;
        }
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceLCDGetName,
//    .deviceGetSoftwareRevision = &deviceLCDGetSoftwareRevision,
    .deviceGetInterface = &deviceLCDGetInterface
};

DeviceInterface* getLCDDeviceInterface() {
    return &deviceInterface;
}
