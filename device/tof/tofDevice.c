#include <stdbool.h>

#include "tofDevice.h"
#include "tofDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/i2c/i2cBusConnectionList.h"

static I2cBusConnection* tofDeviceI2cBusConnection;

// DEVICE INTERFACE

void deviceTofInit(void) {

}

void deviceTofShutDown(void) {

}

bool isTofDeviceOk(void) {
    // SVA : TODO
    return true;
}

void deviceTofHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_TOF_GET_DISTANCE) {
        ackCommand(outputStream, TOF_DEVICE_HEADER, COMMAND_TOF_GET_DISTANCE);
        appendHex4(outputStream, 0);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceTofInit,
    .deviceShutDown = &deviceTofShutDown,
    .deviceIsOk = &isTofDeviceOk,
    .deviceHandleRawData = &deviceTofHandleRawData,
};

DeviceDescriptor* getTofDeviceDescriptor(I2cBusConnection* i2cBusConnection) {
    tofDeviceI2cBusConnection = i2cBusConnection;
    return &descriptor;
}
