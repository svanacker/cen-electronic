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
    return TRUE;
}

void devicePwmMotorHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_MOVE_MOTOR) {
        signed int left = readSignedHex2(inputStream);
        signed int right = readSignedHex2(inputStream);
        appendAck(outputStream);

        setMotorSpeeds(left * 2, right * 2);
        append(outputStream, COMMAND_MOVE_MOTOR);
    } else if (header == COMMAND_STOP_MOTOR) {
        appendAck(outputStream);

        stopMotors();
        append(outputStream, COMMAND_STOP_MOTOR);
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
