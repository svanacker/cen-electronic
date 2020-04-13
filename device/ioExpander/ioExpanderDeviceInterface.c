#include <stdbool.h>

#include "ioExpanderDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceIOExpanderGetName(void) {
    return "IO EXPANDER";
}

int deviceIOExpanderGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT) {
        if (fillDeviceArgumentList) {
            setFunction("Write Single Bit", 5, 0);
            setArgumentUnsignedHex2(0, "IO Expander Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "IO Index");
            setArgumentSeparator(3);
            setArgumentUnsignedChar1(4, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 7, 0);
    }
    if (commandHeader == COMMAND_IO_EXPANDER_WRITE_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("Write Value", 3, 0);
            setArgumentUnsignedHex2(0, "IO Expander Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Value");
        }
        return commandLengthValueForMode(mode, 5, 0);
    } else if (commandHeader == COMMAND_IO_EXPANDER_READ_SINGLE_BIT) {
        if (fillDeviceArgumentList) {
            setFunction("Read Single Bit", 3, 1);
            setArgumentUnsignedHex2(0, "IO Expander Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "IO Index");

            setResultUnsignedChar1(0, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 5, 1);
    } else if (commandHeader == COMMAND_IO_EXPANDER_READ_VALUE) {
        if (fillDeviceArgumentList) {
            setFunction("Read Value", 1, 1);
            setArgumentUnsignedHex2(0, "IO Expander Index");
            setResultUnsignedHex2(0, "Value");
        }
        return commandLengthValueForMode(mode, 2, 2);
    } else if (commandHeader == COMMAND_IO_EXPANDER_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug as Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = IO_DEVICE_EXPANDER_HEADER,
    .deviceGetName = &deviceIOExpanderGetName,
    .deviceGetInterface = &deviceIOExpanderGetInterface
};

DeviceInterface* getIOExpanderDeviceInterface(void) {
    return &deviceInterface;
}
