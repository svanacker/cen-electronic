#include <stdbool.h>

#include "ioDeviceInterface.h"

#include "../../common/io/pin.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceIOGetName(void) {
    return "IO";
}

int deviceIOGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_IO_WRITE) {
        if (fillDeviceArgumentList) {
            setFunction("Write Pin", 3, 0);
            setArgumentUnsignedHex2(0, "Pin Index");
            setArgumentSeparator(1);
            setArgumentUnsignedChar1(2, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 4, 0);
    } else if (commandHeader == COMMAND_IO_READ) {
        if (fillDeviceArgumentList) {
            setFunction("Read Bit", 1, 1);
            setArgumentUnsignedHex2(0, "Pin Expander Index");
            setResultUnsignedChar1(0, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 2, 1);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = IO_HEADER,
    .deviceGetName = &deviceIOGetName,
    .deviceGetInterface = &deviceIOGetInterface
};

DeviceInterface* getIODeviceInterface(void) {
    return &deviceInterface;
}
