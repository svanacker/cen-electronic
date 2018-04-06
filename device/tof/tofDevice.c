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

#include "../../drivers/tof/tof.h"

static I2cBusConnection* tofDeviceI2cBusConnection;

// DEVICE INTERFACE

void deviceTofInit(void) {
    tof_vl53l0x_begin(tofDeviceI2cBusConnection->i2cAddress >> 1, true);
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
        VL53L0X_RangingMeasurementData_t data;
        getSingleRangingMeasurement(&data, true);
        appendHex4(outputStream, data.RangeMilliMeter);
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
