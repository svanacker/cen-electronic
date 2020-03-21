#include "i2cCommonDebugDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceI2cCommonDebugGetName(void) {
    return "i2cCommonDebug";
}

int deviceI2cCommonDebugGetInterface(unsigned char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_I2C_COMMON_DEBUG_LIST_BUS) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebugListBus");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_I2C_COMMON_DEBUG_LIST_BUS_CONNECTION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebugListBusConnection");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_I2C_COMMON_DEBUG_LIST_BUS_CONNECTION) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("i2cDebugListBusConnection");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_I2C_COMMON_DEBUG_WAIT) {
        if (fillDeviceArgumentList) {
            setFunction("waitI2cBus", 1, 0);
            setArgumentUnsignedHex2(0, "slaveAdress");
        }
        return commandLengthValueForMode(mode, 2, 0);
    }
    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceI2cCommonDebugGetName,
    .deviceHeader = I2C_COMMON_DEBUG_DEVICE_HEADER,
    .deviceGetInterface = &deviceI2cCommonDebugGetInterface
};

DeviceInterface* getI2cCommonDebugDeviceInterface(void) {
    return &deviceInterface;
}
