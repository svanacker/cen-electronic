#include "armDevice2019.h"

#include "arm2019.h"
#include "../fork/fork2019.h"

#include "armDeviceInterface2019.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/deviceConstants.h"

static ServoList* servoList;

void deviceArm2019Init(void) {

}

void deviceArm2019ShutDown(void) {

}

bool deviceArm2019IsOk(void) {
    return true;
}

void deviceArm2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ARM ON & OFF
    if (commandHeader == COMMAND_2019_ARM_ON) {
        ackCommand(outputStream, ARM_2019_DEVICE_HEADER, COMMAND_2019_ARM_ON);
        unsigned int side = readHex(inputStream);
        arm2019On(servoList, side);
    }
    else if (commandHeader == COMMAND_2019_ARM_OFF) {
        ackCommand(outputStream, ARM_2019_DEVICE_HEADER, COMMAND_2019_ARM_OFF);
        unsigned int side = readHex(inputStream);
        arm2019Off(servoList, side);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceArm2019Init,
    .deviceShutDown = &deviceArm2019ShutDown,
    .deviceIsOk = &deviceArm2019IsOk,
    .deviceHandleRawData = &deviceArm2019HandleRawData,
};


DeviceDescriptor* getArm2019DeviceDescriptor(ServoList* servoListParam) {
    servoList = servoListParam;
    return &descriptor;
}
