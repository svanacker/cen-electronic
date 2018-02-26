#include "i2cMasterDebugDevice.h"
#include "i2cMasterDebugDeviceInterface.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cBusConnectionList.h"
#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/i2c/master/i2cMaster.h"

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

/**
 * @private
 */
I2cBusConnection* getI2cMasterDebugBusConnection(InputStream* inputStream) {
    int slaveAddress = readHex2(inputStream);
    return getI2cBusConnectionBySlaveAddress(slaveAddress);
}

void deviceI2cMasterDebugHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // I2C Management
    if (header == COMMAND_I2C_MASTER_DEBUG_PRINT_BUFFER) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_PRINT_BUFFER);
        printI2cDebugBuffers();
    }
    else if (header == COMMAND_I2C_MASTER_DEBUG_ENABLE_DISABLE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_ENABLE_DISABLE);

        unsigned char enable = readHex2(inputStream);
        setDebugI2cEnabled(enable != 0);
    }
    // start / stop
    else if (header == COMMAND_I2C_MASTER_DEBUG_START_I2C_BUS) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_START_I2C_BUS);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        portableMasterStartI2C(i2cBusConnection);
    }
    else if (header == COMMAND_I2C_MASTER_DEBUG_STOP_I2C_BUS) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_STOP_I2C_BUS);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        portableMasterStopI2C(i2cBusConnection);
    }
    // ack / nack
    else if (header == COMMAND_I2C_MASTER_DEBUG_ACK) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_ACK);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        portableMasterAckI2C(i2cBusConnection);
    }
    else if (header == COMMAND_I2C_MASTER_DEBUG_NACK) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_NACK);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        portableMasterNackI2C(i2cBusConnection);
    }
    // read / write data
    else if (header == COMMAND_I2C_MASTER_DEBUG_SEND_CHAR_TO_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_SEND_CHAR_TO_SLAVE);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        int c = readHex2(inputStream);
        i2cMasterWriteChar(i2cBusConnection, i2cBusConnection->i2cAddress, c);
    }
    else if (header == COMMAND_I2C_MASTER_DEBUG_READ_CHAR_FROM_SLAVE) {
        ackCommand(outputStream, I2C_MASTER_DEBUG_DEVICE_HEADER, COMMAND_I2C_MASTER_DEBUG_READ_CHAR_FROM_SLAVE);
        I2cBusConnection* i2cBusConnection = getI2cMasterDebugBusConnection(inputStream);
        char c = i2cMasterReadChar(i2cBusConnection);
        appendHex2(outputStream, c);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceI2cMasterDebugInit,
    .deviceShutDown = &deviceI2cMasterDebugShutDown,
    .deviceIsOk = &deviceI2cMasterDebugIsOk,
    .deviceHandleRawData = &deviceI2cMasterDebugHandleRawData,
};

DeviceDescriptor* getI2cMasterDebugDeviceDescriptor(void) {
    return &descriptor;
}
