#include "i2cMasterDebugDevice.h"
#include "i2cMasterDebugDeviceInterface.h"

#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/stream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/logHandler.h"
#include "../../../common/log/loggerDebug.h"

#include "../../../device/device.h"
#include "../../../device/deviceUsage.h"

void deviceI2cMasterDebugInit() {
}

void deviceI2cMasterDebugShutDown() {
}

bool deviceI2cMasterDebugIsOk() {
    return true;
}

void deviceI2cMasterDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    // I2C Management
    if (header == COMMAND_DEBUG_I2C) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_DEBUG_I2C);
        printI2cDebugBuffers();
    }
    else if (header == COMMAND_SEND_CHAR_I2C_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_SEND_CHAR_I2C_SLAVE);
        int address = readHex2(inputStream);
        int c = readHex2(inputStream);
    
        i2cMasterWriteChar(address, c);
    }
    else if (header == COMMAND_READ_CHAR_I2C_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_READ_CHAR_I2C_SLAVE);
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
