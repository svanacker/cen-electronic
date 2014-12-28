#include "i2cMasterDebugDevice.h"
#include "i2cMasterDebugDeviceInterface.h"

#include "../../../common/i2c/master/i2cMaster.h"
#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/logHandler.h"
#include "../../../common/log/loggerDebug.h"

#include "../../../device/device.h"
#include "../../../device/deviceUsage.h"

#include "../../../drivers/test/testDriver.h"

void deviceI2cMasterDebugInit(void) {
}

void deviceI2cMasterDebugShutDown(void) {
}

bool deviceI2cMasterDebugIsOk(void) {
    return true;
}

void deviceI2cMasterDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    // I2C Management
    if (header == COMMAND_I2C_DEBUG_MASTER_DEBUG) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_MASTER_DEBUG);
        printI2cDebugBuffers();
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_ENABLE_DISABLE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_MASTER_ENABLE_DISABLE);

        unsigned char enable = readHex2(inputStream);
        setDebugI2cEnabled(enable != 0);
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_SEND_CHAR_TO_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_MASTER_SEND_CHAR_TO_SLAVE);
        int address = readHex2(inputStream);
        int c = readHex2(inputStream);
    
        i2cMasterWriteChar(address, c);
    }
    else if (header == COMMAND_I2C_DEBUG_MASTER_READ_CHAR_FROM_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_MASTER_READ_CHAR_FROM_SLAVE);
        int address = readHex2(inputStream);
        char c = i2cMasterReadChar(address);
        appendHex2(outputStream, c);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceI2cMasterDebugInit,
    .deviceShutDown = &deviceI2cMasterDebugShutDown,
    .deviceIsOk = &deviceI2cMasterDebugIsOk,
    .deviceHandleRawData = &deviceI2cMasterDebugHandleRawData,
};

DeviceDescriptor* getI2cMasterDebugDeviceDescriptor() {
    return &descriptor;
}
