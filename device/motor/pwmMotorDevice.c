#include <i2c.h>

#include "pwmMotor.h"
#include "pwmMotorDevice.h"
#include "pwmMotorDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/pwm/motorPwm.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"


// DEVICE INTERFACE

void initPwmMotor(void) {
    initPwmForMotor();
}

bool isPwmMotorDeviceOk(void) {
    return true;
}

void devicePwmMotorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_MOVE_MOTOR) {
        signed int left = readSignedHex2(inputStream);
        signed int right = readSignedHex2(inputStream);
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_MOVE_MOTOR);

        setMotorSpeeds(left * 2, right * 2);
    } else if (header == COMMAND_STOP_MOTOR) {
        ackCommand(outputStream, MOTOR_DEVICE_HEADER, COMMAND_STOP_MOTOR);

        stopMotors();
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initPwmMotor,
    .deviceShutDown = &stopMotors,
    .deviceIsOk = &isPwmMotorDeviceOk,
    .deviceHandleRawData = &devicePwmMotorHandleRawData,
};

DeviceDescriptor* getMotorDeviceDescriptor() {
    return &descriptor;
}
