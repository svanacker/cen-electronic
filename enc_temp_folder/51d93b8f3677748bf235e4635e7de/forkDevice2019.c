#include "forkDevice2019.h"

#include "forkDeviceInterface2019.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoList.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/deviceConstants.h"

static ServoList* servoList;

void deviceFork2019Init(void) {

}

void deviceFork2019ShutDown(void) {

}

bool deviceFork2019IsOk(void) {
    return true;
}

void deviceFork2019HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ELEVATOR
    // -> Bottom
    if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_BOTTOM);
        Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
        pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE);
    }
    // -> Middle for Double Puck Position
    else if (commandHeader == COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_UP);
        Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
        pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_UP_SERVO_VALUE);
    }
    // -> Up
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_UP);
        Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
        pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_UP_SERVO_VALUE);
    }
    // Fork Back/Retracted
    else if (commandHeader == COMMAND_2019_FORK_BACK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_BACK);
        unsigned int servoIndex = readHex(inputStream);
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_LEFT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_LEFT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE);
        }
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_RIGHT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_RIGHT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_RIGHT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE);
        }
    }
    // Fork Single Puck
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SIMPLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_LEFT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_LEFT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE);
        }
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_RIGHT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_RIGHT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_RIGHT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE);
        }
    }
    // Fork Double Puck
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_DOUBLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_LEFT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_LEFT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE);
        }
        if (servoIndex == FORK_2019_LEFT_AND_RIGHT_INDEX || servoIndex == FORK_2019_RIGHT_INDEX) {
            Servo* servo = getServo(servoList, FORK_2019_RIGHT_SERVO_INDEX);
            pwmServo(servo, FORK_2019_SERVO_RIGHT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE);
        }
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceFork2019Init,
    .deviceShutDown = &deviceFork2019ShutDown,
    .deviceIsOk = &deviceFork2019IsOk,
    .deviceHandleRawData = &deviceFork2019HandleRawData,
};


DeviceDescriptor* getFork2019DeviceDescriptor(ServoList* servoListParam) {
    servoList = servoListParam;
    return &descriptor;
}
