#include "i2cSlaveDebugDevice.h"
#include "i2cSlaveDebugDeviceInterface.h"

// #include <plib.h>

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
    if (header == COMMAND_DEBUG_I2C) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_DEBUG_I2C);
        printI2cDebugBuffers();
    }
    else if (header == COMMAND_SEND_CHAR_I2C_TO_MASTER) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_SEND_CHAR_I2C_TO_MASTER);
        int c = readHex2(inputStream);
    
        // TODO : Non Portable Function
        // TODO SlaveWriteI2C1(c);
    }
    else if (header == COMMAND_READ_CHAR_I2C_FROM_MASTER) {
        ackCommand(outputStream, I2C_SLAVE_DEBUG_DEVICE_HEADER, COMMAND_READ_CHAR_I2C_FROM_MASTER);
    
        // TODO : Non Portable Function
        // char c = SlaveReadI2C1();

        // appendHex2(outputStream, c);
		appendHex2(outputStream, 0x00);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceI2cSlaveDebugInit,
    .deviceShutDown = &deviceI2cSlaveDebugShutDown,
    .deviceIsOk = &deviceI2cSlaveDebugIsOk,
    .deviceHandleRawData = &deviceI2cSlaveDebugHandleRawData,
};

DeviceDescriptor* getI2cSlaveDebugDeviceDescriptor() {
    return &descriptor;
}
