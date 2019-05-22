#include <stdbool.h>

#include "multiplexerDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceMultiplexerGetName(void) {
    return "MULTIPLEXER";
}

int deviceMultiplexerGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_MULTIPLEXER_WRITE_SINGLE_CHANNEL) {
        if (fillDeviceArgumentList) {
            setFunction("Write Single Channel", 5, 0);
            setArgumentUnsignedHex2(0, "Multiplexer Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Channel Index");
            setArgumentSeparator(3);
            setArgumentUnsignedChar1(4, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 7, 0);
    }
    if (commandHeader == COMMAND_MULTIPLEXER_WRITE_CHANNELS_MASK) {
        if (fillDeviceArgumentList) {
            setFunction("Write Channel Masks", 3, 0);
            setArgumentUnsignedHex2(0, "Multiplexer Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Channels Mask");
        }
        return commandLengthValueForMode(mode, 5, 0);
    }
    else if (commandHeader == COMMAND_MULTIPLEXER_READ_SINGLE_CHANNEL) {
        if (fillDeviceArgumentList) {
            setFunction("Read Single Channel", 3, 1);
            setArgumentUnsignedHex2(0, "Multiplexer Index");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "Channel Index");

            setResultUnsignedChar1(0, "Value (bool)");
        }
        return commandLengthValueForMode(mode, 5, 1);
    }
    else if (commandHeader == COMMAND_MULTIPLEXER_READ_CHANNELS_MASK) {
        if (fillDeviceArgumentList) {
            setFunction("Read Channel Mask", 1, 1);
            setArgumentUnsignedHex2(0, "Multiplexer Index");
            setResultUnsignedHex2(0, "Channels Mask");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    else if (commandHeader == COMMAND_MULTIPLEXER_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("Debug as Table");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = MULTIPLEXER_HEADER,
    .deviceGetName = &deviceMultiplexerGetName,
    .deviceGetInterface = &deviceMultiplexerGetInterface
};

DeviceInterface* getMultiplexerDeviceInterface(void) {
    return &deviceInterface;
}
