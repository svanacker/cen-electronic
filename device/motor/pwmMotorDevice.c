#include <stdbool.h>

#include "pwmMotorDevice.h"
#include "pwmMotorDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/delay/cenDelay.h"

#include "../../common/motor/dualHBridgeMotor.h"
#include "../../common/pwm/motor/dualHBridgeMotorPwm.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/motor/dualHBridgeMotor.h"

#include "../../device/device.h"

// The underlying dual HBridge structure pointer
static DualHBridgeMotor* dualHBridgeMotorPwm;

// DEVICE INTERFACE

void devicePwmMotorInit(void) {
    dualHBridgeMotorPwm->dualHBridgeMotorInit(dualHBridgeMotorPwm);
    stopMotors(dualHBridgeMotorPwm);
}

void devicePwmMotorStop(void) {
    stopMotors(dualHBridgeMotorPwm);
}

bool isPwmMotorDeviceOk(void) {
    return true;
}

void devicePwmMotorHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_MOVE_MOTOR) {
        signed int left = readSignedHex2(inputStream);
        signed int right = readSignedHex2(inputStream);
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_MOVE_MOTOR);
        dualHBridgeMotorPwm->dualHBridgeMotorWriteValue(dualHBridgeMotorPwm, left * 2, right * 2);
    }
    else if (commandHeader == COMMAND_READ_MOTOR_VALUE) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_READ_MOTOR_VALUE);
        signed int left = dualHBridgeMotorPwm->dualHBridgeMotorReadValue(dualHBridgeMotorPwm, HBRIDGE_1);
        signed int right = dualHBridgeMotorPwm->dualHBridgeMotorReadValue(dualHBridgeMotorPwm, HBRIDGE_2);
        appendHex2(outputStream, left / 2);
        appendHex2(outputStream, right / 2);
    }
    else if (commandHeader == COMMAND_STOP_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_STOP_MOTOR);

        stopMotors(dualHBridgeMotorPwm);
    }
    else if (commandHeader == COMMAND_SMALL_TEST_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_SMALL_TEST_MOTOR);
        appendString(getAlwaysOutputStreamLogger(), "Both Forward\n");
        // Left forward
        dualHBridgeMotorPwm->dualHBridgeMotorWriteValue(dualHBridgeMotorPwm, 50, 50);
        delaymSec(2000);
        stopMotors(dualHBridgeMotorPwm);
    }
    else if (commandHeader == COMMAND_NORMAL_TEST_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_NORMAL_TEST_MOTOR);

        appendString(getAlwaysOutputStreamLogger(), "Left Forward\n");
        // Left forward
        setMotorSpeeds(dualHBridgeMotorPwm, 50, 0);
        delaymSec(2000);

        appendString(getAlwaysOutputStreamLogger(), "Right Forward\n");
        // Right forward
        setMotorSpeeds(dualHBridgeMotorPwm, 0, 50);
        delaymSec(2000);

        appendString(getAlwaysOutputStreamLogger(), "Left Backward\n");
        // Left backward
        setMotorSpeeds(dualHBridgeMotorPwm, -50, 0);
        delaymSec(2000);

        appendString(getAlwaysOutputStreamLogger(), "Right Forward\n");
        // Right backward
        setMotorSpeeds(dualHBridgeMotorPwm, 0, -50);
        delaymSec(2000);

        appendString(getAlwaysOutputStreamLogger(), "Both Forward\n");
        // Both forward
        setMotorSpeeds(dualHBridgeMotorPwm, 50, 50);
        delaymSec(2000);

        appendString(getAlwaysOutputStreamLogger(), "Both Backward\n");
        // Both backward
        setMotorSpeeds(dualHBridgeMotorPwm, -50, -50);
        delaymSec(2000);

        stopMotors(dualHBridgeMotorPwm);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &devicePwmMotorInit,
    .deviceShutDown = &devicePwmMotorStop,
    .deviceIsOk = &isPwmMotorDeviceOk,
    .deviceHandleRawData = &devicePwmMotorHandleRawData,
};

DeviceDescriptor* getMotorDeviceDescriptor(DualHBridgeMotor* dualHBrideMotorParam) {
    dualHBridgeMotorPwm = dualHBrideMotorParam;
    return &descriptor;
}
