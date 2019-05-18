#include "i2cMasterDebugDeviceInterface.h"

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* deviceI2cMasterDebugGetName(void) {
    return "i2cMasterDebug";
}

int deviceI2cMasterDebugGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    // MULTIPLEXER
    if (commandHeader == COMMAND_I2C_MULTIPLEXER_SET_CHANNEL) {
        if (fillDeviceArgumentList) {
            setFunction("multiplexer set channel", 1, 0);
            setArgumentUnsignedHex2(0, "channel (0->7)");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_I2C_MULTIPLEXER_GET_CHANNEL) {
        if (fillDeviceArgumentList) {
            setFunction("multiplexer get channel", 0, 1);
            setResultUnsignedHex2(0, "channel (0->7)");
        }
        return commandLengthValueForMode(mode, 0, 2);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_PRINT_BUFFER) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebug");
        }
        return commandLengthValueForMode(mode, 0, 0);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_ENABLE_DISABLE) {
        if (fillDeviceArgumentList) {        
            setFunction("enable/disable", 1, 0);
            setArgumentUnsignedHex2(0, "mode");
        }
        return commandLengthValueForMode(mode, 2, 0);        
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_SEND_CHAR_TO_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("sendCharI2cSlave", 2, 0);
            setArgumentUnsignedHex2(0, "adress");
            setArgumentUnsignedHex2(1, "char");
        }
        return commandLengthValueForMode(mode, 4, 0);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_READ_CHAR_FROM_SLAVE) {
        if (fillDeviceArgumentList) {        
            setFunction("readCharI2cSlave", 1, 1);
            setArgumentUnsignedHex2(0, "readChar");
            setResultUnsignedHex2(0, "readChar");
        }
        return commandLengthValueForMode(mode, 2, 2);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_START_I2C_BUS) {
		if (fillDeviceArgumentList) {
            setFunction("masterStartI2cBus", 1, 0);
            setArgumentUnsignedHex2(0, "slaveAdress");
		}
		return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_STOP_I2C_BUS) {
		if (fillDeviceArgumentList) {
            setFunction("masterStopI2cBus", 1, 0);
            setArgumentUnsignedHex2(0, "slaveAdress");
		}
		return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_ACK) {
		if (fillDeviceArgumentList) {
            setFunction("masterAckI2cBus", 1, 0);
            setArgumentUnsignedHex2(0, "slaveAdress");
		}
		return commandLengthValueForMode(mode, 2, 0);
    }
    else if (commandHeader == COMMAND_I2C_MASTER_DEBUG_NACK) {
		if (fillDeviceArgumentList) {
            setFunction("masterNackI2cBus", 1, 0);
            setArgumentUnsignedHex2(0, "slaveAdress");
		}
		return commandLengthValueForMode(mode, 2, 0);
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
