#include <stdbool.h>

#include "airConditioningDevice.h"
#include "airConditioningDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/delay/cenDelay.h"

#define        SERVO_INDEX                   1
#define        SERVO_VALUE_TOUCH          1620
#define        SERVO_VALUE_STAND_BY       1400
#define        SERVO_SPEED                0xFF

void deviceAirConditioningInit() {
}

void deviceAirConditioningShutDown() {
}

bool deviceAirConditioningIsOk() {
    return true;
}

void airConditioningToggleOn() {
    pwmServoAll(SERVO_SPEED, SERVO_VALUE_TOUCH);
    delaymSec(1000);
    pwmServoAll(SERVO_SPEED, SERVO_VALUE_STAND_BY);
}

void airConditioningToggleOff() {
    pwmServoAll(SERVO_SPEED, SERVO_VALUE_TOUCH);
    delaymSec(1000);
    pwmServoAll(SERVO_SPEED, SERVO_VALUE_STAND_BY);
}

void deviceAirConditioningHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == AIR_CONDITIONING_COMMAND_WRITE) {
        int powerState = readHex2(inputStream);

        if (powerState != 0x00) {
            airConditioningToggleOn();
        } else {
            airConditioningToggleOff();
        }
        ackCommand(outputStream, AIR_CONDITIONING_DEVICE_HEADER, AIR_CONDITIONING_COMMAND_WRITE);
    }
    else if (commandHeader == AIR_CONDITIONING_COMMAND_ON) {
        airConditioningToggleOn();
        ackCommand(outputStream, AIR_CONDITIONING_DEVICE_HEADER, AIR_CONDITIONING_COMMAND_ON);
    }
    else if (commandHeader == AIR_CONDITIONING_COMMAND_OFF) {
        airConditioningToggleOff();
        ackCommand(outputStream, AIR_CONDITIONING_DEVICE_HEADER, AIR_CONDITIONING_COMMAND_OFF);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceAirConditioningInit,
    .deviceShutDown = &deviceAirConditioningShutDown,
    .deviceIsOk = &deviceAirConditioningIsOk,
    .deviceHandleRawData = &deviceAirConditioningHandleRawData,
};

DeviceDescriptor* getAirConditioningDeviceDescriptor() {
    return &descriptor;
}

