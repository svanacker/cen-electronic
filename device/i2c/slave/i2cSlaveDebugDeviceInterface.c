#include "i2cSlaveDebugDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceI2cSlaveDebugGetName() {
    return "i2cSlaveDebug";
}

int deviceI2cSlaveDebugGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_DEBUG_I2C) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebug");
        }
        return 0;
    }
    else if (header == COMMAND_SEND_CHAR_I2C_TO_MASTER) {
        if (fillDeviceArgumentList) {        
            setFunction("sendCharI2cToMaster", 1, 0);
            setArgumentUnsignedHex2(0, "char");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (header == COMMAND_READ_CHAR_I2C_FROM_MASTER) {
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

DeviceInterface* getI2cSlaveDebugDeviceInterface() {
    return &deviceInterface;
}
