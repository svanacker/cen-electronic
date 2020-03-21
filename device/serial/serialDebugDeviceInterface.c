#include <stdbool.h>

#include "serialDebugDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceSerialDebugGetName(void) {
    return "serialDebug";
}

/**
 * Function to fill usage when dealing with a function with one char value
 * @private
 */
void serialDebugCharFunctionArgument(char* functionName) {
    setFunction(functionName, 3, 0);
    setArgumentUnsignedHex2(0, "serialPort");
    setArgumentSeparator(1);
    setArgumentUnsignedHex2(2, "char");
}

/**
 * Function to fill usage when dealing with a function with a char array
 * @private
 */
void serialDebugCharArrayFunctionArgument(char* functionName) {
    setFunction(functionName, 9, 0);
    setArgumentUnsignedHex2(0, "serialPort");
    setArgumentSeparator(1);
    setArgumentUnsignedHex2(2, "char1");
    setArgumentSeparator(3);
    setArgumentUnsignedHex2(4, "char2");
    setArgumentSeparator(5);
    setArgumentUnsignedHex2(6, "char3");
    setArgumentSeparator(7);
    setArgumentUnsignedHex2(8, "char4");
}

int deviceSerialDebugGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_SERIAL_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunction("serial Port Debug", 1, 0);
            setArgumentUnsignedHex2(0, "serialPort");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_SERIAL_CLEAR) {
        if (fillDeviceArgumentList) {
            setFunction("serial Clear", 1, 0);
            setArgumentUnsignedHex2(0, "serialPort");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_SERIAL_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("show Serial Port List");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_SERIAL_CHAR_OUTPUT) {
        if (fillDeviceArgumentList) {
            serialDebugCharFunctionArgument("serial Char Output");
        }
        return commandLengthValueForMode(mode, 5, 0);
    } else if (commandHeader == COMMAND_SERIAL_CHAR_ARRAY_OUTPUT) {
        if (fillDeviceArgumentList) {
            serialDebugCharArrayFunctionArgument("serial Char Array Output");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_SERIAL_CHAR_INPUT) {
        if (fillDeviceArgumentList) {
            serialDebugCharFunctionArgument("serial Char Input");
        }
        return commandLengthValueForMode(mode, 5, 0);
    } else if (commandHeader == COMMAND_SERIAL_CHAR_ARRAY_INPUT) {
        if (fillDeviceArgumentList) {
            serialDebugCharArrayFunctionArgument("serial Char Array Input");
        }
        return commandLengthValueForMode(mode, 14, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceSerialDebugGetName,
    .deviceHeader = SERIAL_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceSerialDebugGetInterface
};

DeviceInterface* getSerialDebugDeviceInterface(void) {
    return &deviceInterface;
}
