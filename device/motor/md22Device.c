#include <stdbool.h>

#include "md22Device.h"
#include "md22DeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/delay/cenDelay.h"

#include "../../common/motor/dualHBridgeMotor.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../drivers/motor/dualHBridgeMotorMd22.h"

// The underlying dual HBridge structure pointer
static DualHBridgeMotor* dualHBridgeMotorMD22;

// DEVICE INTERFACE

void deviceMD22Init(void) {
    dualHBridgeMotorMD22->dualHBridgeMotorInit(dualHBridgeMotorMD22);
    stopMotors(dualHBridgeMotorMD22);
}

void deviceMD22Stop(void) {
    stopMotors(dualHBridgeMotorMD22);
}

bool isMD22DeviceOk(void) {
    return true;
}

void deviceMD22HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_MD22_MOVE) {
        signed int left = readSignedHex2(inputStream);
        signed int right = readSignedHex2(inputStream);
        ackCommand(outputStream, MD22_DEVICE_HEADER, COMMAND_MD22_MOVE);
        dualHBridgeMotorMD22->dualHBridgeMotorWriteValue(dualHBridgeMotorMD22, left, right);
    } else if (commandHeader == COMMAND_MD22_READ_VALUE) {
        ackCommand(outputStream, MD22_DEVICE_HEADER, COMMAND_MD22_READ_VALUE);
        signed int left = dualHBridgeMotorMD22->dualHBridgeMotorReadValue(dualHBridgeMotorMD22, HBRIDGE_1);
        signed int right = dualHBridgeMotorMD22->dualHBridgeMotorReadValue(dualHBridgeMotorMD22, HBRIDGE_2);
        appendHex2(outputStream, left);
        appendHex2(outputStream, right);
    } else if (commandHeader == COMMAND_MD22_STOP) {
        ackCommand(outputStream, MD22_DEVICE_HEADER, COMMAND_MD22_STOP);

        stopMotors(dualHBridgeMotorMD22);
    } else if (commandHeader == COMMAND_MD22_SOFTWARE_REVISION) {
        ackCommand(outputStream, MD22_DEVICE_HEADER, COMMAND_MD22_SOFTWARE_REVISION);
        unsigned softwareRevision = dualHBridgeMotorMD22->dualHBridgeMotorGetSoftwareRevision(dualHBridgeMotorMD22);
        appendHex2(outputStream, softwareRevision);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMD22Init,
    .deviceShutDown = &deviceMD22Stop,
    .deviceIsOk = &isMD22DeviceOk,
    .deviceHandleRawData = &deviceMD22HandleRawData,
};

DeviceDescriptor* getMD22DeviceDescriptor(DualHBridgeMotor* dualHBrideMotorParam) {
    dualHBridgeMotorMD22 = dualHBrideMotorParam;
    return &descriptor;
}
