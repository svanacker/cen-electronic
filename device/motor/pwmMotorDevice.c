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

void devicePwmMotorHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_MOVE_MOTOR) {
        signed int left = readSignedHex2(inputStream);
        signed int right = readSignedHex2(inputStream);
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_MOVE_MOTOR);
        dualHBridgeMotorPwm->dualHBridgeMotorWriteValue(dualHBridgeMotorPwm, left * 2, right * 2);
    } else if (commandHeader == COMMAND_READ_MOTOR_VALUE) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_READ_MOTOR_VALUE);
        signed int left = dualHBridgeMotorPwm->dualHBridgeMotorReadValue(dualHBridgeMotorPwm, HBRIDGE_1);
        signed int right = dualHBridgeMotorPwm->dualHBridgeMotorReadValue(dualHBridgeMotorPwm, HBRIDGE_2);
        appendHex2(outputStream, left / 2);
        appendHex2(outputStream, right / 2);
    } else if (commandHeader == COMMAND_STOP_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_STOP_MOTOR);

        stopMotors(dualHBridgeMotorPwm);
    } else if (commandHeader == COMMAND_SMALL_TEST_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_SMALL_TEST_MOTOR);
        appendStringLN(getInfoOutputStreamLogger(), "Both Forward");
        // Left forward
        dualHBridgeMotorPwm->dualHBridgeMotorWriteValue(dualHBridgeMotorPwm, 50, 50);
        delayMilliSecs(2000);
        stopMotors(dualHBridgeMotorPwm);
    } else if (commandHeader == COMMAND_NORMAL_TEST_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_NORMAL_TEST_MOTOR);

        OutputStream* logStream = getInfoOutputStreamLogger();
        appendStringLN(logStream, "Left Forward");
        // Left forward
        setMotorSpeeds(dualHBridgeMotorPwm, 50, 0);
        delayMilliSecs(2000);

        appendStringLN(logStream, "Right Forward");
        // Right forward
        setMotorSpeeds(dualHBridgeMotorPwm, 0, 50);
        delayMilliSecs(2000);

        appendStringLN(logStream, "Left Backward");
        // Left backward
        setMotorSpeeds(dualHBridgeMotorPwm, -50, 0);
        delayMilliSecs(2000);

        appendStringLN(logStream, "Right Forward");
        // Right backward
        setMotorSpeeds(dualHBridgeMotorPwm, 0, -50);
        delayMilliSecs(2000);

        appendStringLN(logStream, "Both Forward");
        // Both forward
        setMotorSpeeds(dualHBridgeMotorPwm, 50, 50);
        delayMilliSecs(2000);

        appendStringLN(logStream, "Both Backward");
        // Both backward
        setMotorSpeeds(dualHBridgeMotorPwm, -50, -50);
        delayMilliSecs(2000);

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
