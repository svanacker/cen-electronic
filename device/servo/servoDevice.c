#include <stdbool.h>

#include "servoDevice.h"
#include "servoDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoPwmDebug.h"

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

void deviceServoInit(void) {
    initPwmForServo(PWM_SERVO_MIDDLE_POSITION);
}

void deviceServoShutDown(void) {
}

bool deviceServoIsOk(void) {
    return true;
}

void deviceServoHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // WRITE COMMANDS
    if (commandHeader == SERVO_COMMAND_WRITE) {
        int servoIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        int servoSpeed = readHex2(inputStream);
        checkIsSeparator(inputStream);
        int servoValue = readHex4(inputStream);
        if (servoIndex > 0 && servoIndex <= PWM_COUNT) {
            pwmServo(servoIndex, servoSpeed, servoValue);
        } else {
            pwmServoAll(servoSpeed, servoValue);
        }
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE);
    }
    else if (commandHeader == SERVO_COMMAND_WRITE_COMPACT) {
        int servoValue = readHex4(inputStream);
        pwmServoAll(PWM_SERVO_SPEED_MAX, servoValue);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE_COMPACT);
    }
    // READ COMMANDS
    else if (commandHeader == SERVO_COMMAND_READ) {
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ);
        int servoIndex = readHex2(inputStream);
        int speed = pwmServoReadSpeed(servoIndex);
        int currentPosition = pwmServoReadCurrentPosition(servoIndex);
        int targetPosition = pwmServoReadTargetPosition(servoIndex);

        appendHex2(outputStream, servoIndex);
        appendSeparator(outputStream);
        appendHex2(outputStream, speed);
        appendSeparator(outputStream);
        appendHex4(outputStream, currentPosition);
        appendSeparator(outputStream);
        appendHex4(outputStream, targetPosition);
    }
    else if (commandHeader == SERVO_COMMAND_READ_SPEED) {
        int servoIndex = readHex2(inputStream);
        int speed = pwmServoReadSpeed(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_SPEED);
        appendHex2(outputStream, speed);
    }
    else if (commandHeader == SERVO_COMMAND_READ_CURRENT_POSITION) {
        int servoIndex = readHex2(inputStream);
        int currentPosition = pwmServoReadCurrentPosition(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_CURRENT_POSITION);
        appendHex4(outputStream, currentPosition);
    }
    else if (commandHeader == SERVO_COMMAND_READ_TARGET_POSITION) {
        int servoIndex = readHex2(inputStream);
        int targetPosition = pwmServoReadTargetPosition(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_TARGET_POSITION);
        appendHex4(outputStream, targetPosition);
    }
    // DEBUG COMMANDS
    else if (commandHeader == SERVO_COMMAND_TEST) {
        testAllPwmServos();
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_TEST);
    }
    else if (commandHeader == SERVO_COMMAND_DEBUG) {
        printServoList(getDebugOutputStreamLogger());
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_DEBUG);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceServoInit,
    .deviceShutDown = &deviceServoShutDown,
    .deviceIsOk = &deviceServoIsOk,
    .deviceHandleRawData = &deviceServoHandleRawData,
};

DeviceDescriptor* getServoDeviceDescriptor(void) {
    return &descriptor;
}
