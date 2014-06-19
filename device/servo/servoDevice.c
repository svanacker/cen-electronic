#include "servoDevice.h"
#include "servoDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servoPwm.h"

#include "../../device/device.h"

#define MAX_SERVO_SPEED         20000

void deviceServoInit() {
    initPwmForServo(PWM_SERVO_MIDDLE_POSITION);
}

void deviceServoShutDown() {
}

bool deviceServoIsOk() {
    return true;
}

void deviceServoHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {

    // WRITE COMMANDS
    if (header == SERVO_COMMAND_WRITE) {
        int servoIndex = readHex2(inputStream);
        int servoSpeed = readHex2(inputStream);

        // 0xFF is for test to determine the index of each 
        // servo (test)
        if (servoIndex == 0xFF) {
            testAllPwmServos();
        }
        else {
            //if (servoSpeed == 0xFF) {
            servoSpeed = MAX_SERVO_SPEED;
            //}
    
            int servoValue = readHex4(inputStream);
            if (servoIndex > 0 && servoIndex <= PWM_COUNT) {
                pwmServo(servoIndex, servoSpeed, servoValue);
            } else {
                pwmServoAll(servoSpeed, servoValue);
            }
        }
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE);
    }
    else if (header == SERVO_COMMAND_WRITE_COMPACT) {
        int servoValue = readHex4(inputStream);
        pwmServoAll(MAX_SERVO_SPEED, servoValue);
        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_WRITE_COMPACT);
    }
    // READ COMMANDS
    else if (header == SERVO_COMMAND_READ_SPEED) {
        int servoIndex = readHex2(inputStream);
        int speed = pwmServoReadSpeed(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_SPEED);
        appendHex2(outputStream, speed);
    }
    else if (header == SERVO_COMMAND_READ_SPEED) {
        int servoIndex = readHex2(inputStream);
        int currentPosition = pwmServoReadCurrentPosition(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_CURRENT_POSITION);
        appendHex4(outputStream, currentPosition);
    }
    else if (header == SERVO_COMMAND_READ_TARGET_POSITION) {
        int servoIndex = readHex2(inputStream);
        int targetPosition = pwmServoReadTargetPosition(servoIndex);

        ackCommand(outputStream, SERVO_DEVICE_HEADER, SERVO_COMMAND_READ_TARGET_POSITION);
        appendHex4(outputStream, targetPosition);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceServoInit,
    .deviceShutDown = &deviceServoShutDown,
    .deviceIsOk = &deviceServoIsOk,
    .deviceHandleRawData = &deviceServoHandleRawData,
};

DeviceDescriptor* getServoDeviceDescriptor() {
    return &descriptor;
}
