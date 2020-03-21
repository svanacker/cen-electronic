#include "i2cSlaveDebugDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceI2cSlaveDebugGetName(void) {
    return "i2cSlaveDebug";
}

int deviceI2cSlaveDebugGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_I2C_DEBUG_SLAVE_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMANG_I2C_DEBUG_SLAVE_ADDRESS) {
        if (fillDeviceArgumentList) {
            setFunction("i2cSlaveAddress", 0, 1);
            setResultUnsignedHex2(0, "i2cAddress");
        }
        return commandLengthValueForMode(mode, 0, 2);
    } else if (commandHeader == COMMAND_I2C_DEBUG_SLAVE_ENABLE_DISABLE) {
        if (fillDeviceArgumentList) {
            setFunction("enable/disable", 1, 0);
            setArgumentUnsignedHex2(0, "mode");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_I2C_DEBUG_SLAVE_SEND_CHAR_I2C_TO_MASTER) {
        if (fillDeviceArgumentList) {
            setFunction("sendCharI2cToMaster", 1, 0);
            setArgumentUnsignedHex2(0, "char");
        }
        return commandLengthValueForMode(mode, 2, 0);
    } else if (commandHeader == COMMAND_I2C_DEBUG_SLAVE_READ_CHAR_I2C_FROM_MASTER) {
        if (fillDeviceArgumentList) {
            setFunction("readCharI2cFromMaster", 0, 1);
            setResultUnsignedHex2(0, "result");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceI2cSlaveDebugGetName,
    .deviceHeader = I2C_SLAVE_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceI2cSlaveDebugGetInterface
};

DeviceInterface* getI2cSlaveDebugDeviceInterface(void) {
    return &deviceInterface;
}
