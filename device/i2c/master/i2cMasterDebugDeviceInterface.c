#include "i2cMasterDebugDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceI2cMasterDebugGetName(void) {
    return "i2cMasterDebug";
}

int deviceI2cMasterDebugGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_I2C_DEBUG_MASTER_DEBUG) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebug");
        }
        return 0;
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_ENABLE_DISABLE) {
        if (fillDeviceArgumentList) {        
            setFunction("enable/disable", 1, 0);
            setArgumentUnsignedHex2(0, "mode");
        }
        return commandLengthValueForMode(mode, 2, 0);        
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_SEND_CHAR_TO_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("sendCharI2cSlave", 2, 0);
            setArgumentUnsignedHex2(0, "adress");
            setArgumentUnsignedHex2(1, "char");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_READ_CHAR_FROM_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("readCharI2cSlave", 1, 1);
            setArgumentUnsignedHex2(0, "readChar");
            setResultUnsignedHex2(0, "readChar");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_INTENSIVE_CALL_TO_SLAVE) {
        if (fillDeviceArgumentList) {
            setFunction("intensive", 1, 0);
            setArgumentUnsignedHex4(0, "count");
        }
        return commandLengthValueForMode(mode, 4, 2);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceI2cMasterDebugGetName,
    .deviceHeader = I2C_MASTER_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceI2cMasterDebugGetInterface
};

DeviceInterface* getI2cMasterDebugDeviceInterface(void) {
    return &deviceInterface;
}
