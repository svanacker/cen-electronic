#include "airConditionningBoardDevice.h"
#include "airConditionningBoardDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/pwm/servoPwm.h"

#include "../../common/delay/delay30F.h"

#define		SERVO_INDEX				1
#define		SERVO_VALUE_TOUCH		1620
#define		SERVO_VALUE_STAND_BY	1400
#define		SERVO_SPEED				0xFF

void deviceAirConditionningBoardInit() {
}

void deviceAirConditionningBoardShutDown() {
}

BOOL deviceAirConditionningBoardIsOk() {
    return TRUE;
}

void deviceAirConditionningBoardHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream) {
    if (header == COMMAND_AIR_CONDITIONNING) {
        int powerState = readHex2(inputStream);

        if (powerState != 0x00) {
            pwmServoAll(SERVO_SPEED, SERVO_VALUE_TOUCH);
            delaymSec(1000);
            pwmServoAll(SERVO_SPEED, SERVO_VALUE_STAND_BY);
        } else {
            pwmServoAll(SERVO_SPEED, SERVO_VALUE_TOUCH);
            delaymSec(1000);
            pwmServoAll(SERVO_SPEED, SERVO_VALUE_STAND_BY);
        }

        appendAck(outputStream);
        append(outputStream, COMMAND_AIR_CONDITIONNING);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceAirConditionningBoardInit,
    .deviceShutDown = &deviceAirConditionningBoardShutDown,
    .deviceIsOk = &deviceAirConditionningBoardIsOk,
    .deviceHandleRawData = &deviceAirConditionningBoardHandleRawData,
};

DeviceDescriptor* getAirConditionningBoardDeviceDescriptor() {
    return &descriptor;
}

