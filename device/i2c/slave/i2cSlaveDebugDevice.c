#include "i2cSlaveDebugDevice.h"
#include "i2cSlaveDebugDeviceInterface.h"

#include "../../../common/i2c/slave/i2cSlave.h"
#include "../../../common/i2c/slave/i2cSlaveSetup.h"
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

void deviceI2cSlaveDebugInit(void) {
}

void deviceI2cSlaveDebugShutDown(void) {
}

bool deviceI2cSlaveDebugIsOk(void) {
    return true;
}

void deviceI2cSlaveDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    // I2C Management
    if (header == COMMAND_I2C_DEBUG_SLAVE_DEBUG) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_SLAVE_DEBUG);
        printI2cDebugBuffers();
    }
    else if (header == COMMANG_I2C_DEBUG_SLAVE_ADDRESS) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMANG_I2C_DEBUG_SLAVE_ADDRESS);
    
        char c = getI2cWriteAddress();
        appendHex2(outputStream, c);
    }
    else if (header == COMMAND_I2C_DEBUG_SLAVE_ENABLE_DISABLE) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_SLAVE_ENABLE_DISABLE);

        unsigned char enable = readHex2(inputStream);
        setDebugI2cEnabled(enable != 0);
    }
    else if (header == COMMAND_I2C_DEBUG_SLAVE_SEND_CHAR_I2C_TO_MASTER) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_SLAVE_SEND_CHAR_I2C_TO_MASTER);

        int c = readHex2(inputStream);
        portableSlaveWriteI2C(c);
    }
    else if (header == COMMAND_I2C_DEBUG_SLAVE_READ_CHAR_I2C_FROM_MASTER) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_I2C_DEBUG_SLAVE_READ_CHAR_I2C_FROM_MASTER);
    
        char c = portableSlaveReadI2C();
        appendHex2(outputStream, c);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceI2cSlaveDebugInit,
    .deviceShutDown = &deviceI2cSlaveDebugShutDown,
    .deviceIsOk = &deviceI2cSlaveDebugIsOk,
    .deviceHandleRawData = &deviceI2cSlaveDebugHandleRawData,
};

DeviceDescriptor* getI2cSlaveDebugDeviceDescriptor(void) {
    return &descriptor;
}
