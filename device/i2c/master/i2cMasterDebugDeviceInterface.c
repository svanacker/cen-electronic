#include "i2cMasterDebugDeviceInterface.h"

#include "../../../device/deviceInterface.h"

const char* deviceI2cMasterDebugGetName() {
    return "i2cMasterDebug";
}

int deviceI2cMasterDebugGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_DEBUG_I2C) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebug");
        }
        return 0;
    }
    else if (header == COMMAND_SEND_CHAR_I2C_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("sendCharI2cSlave", 2, 0);
            setArgumentUnsignedHex2(0, "adress");
            setArgumentUnsignedHex2(1, "char");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (header == COMMAND_READ_CHAR_I2C_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("readCharI2cSlave", 1, 1);
            setArgumentUnsignedHex2(0, "readChar");
            setResultUnsignedHex2(0, "readChar");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceI2cMasterDebugGetName,
    .deviceHeader = I2C_MASTER_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceI2cMasterDebugGetInterface
};

DeviceInterface* getI2cMasterDebugDeviceInterface() {
    return &deviceInterface;
}
