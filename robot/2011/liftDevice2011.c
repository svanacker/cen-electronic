#include "liftDevice2011.h"

#include "liftDeviceInterface2011.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/servoPwm.h"

#include "../../main/meca2/mechanicalBoard2.h"

void deviceLift2011Init() {

}

void deviceLift2011ShutDown() {
}

bool deviceLift2011IsOk() {
    return true;
}

#define LIFT_PWM_UP         1800

#define LIFT_PWM_MIDDLE        1500

#define LIFT_PWM_BOTTOM     1200

void deviceLift2011HandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (commandHeader == COMMAND_LIFT_2011_BOTTOM) {
        appendAck(outputStream);
        append(outputStream, COMMAND_LIFT_2011_BOTTOM);

        int counter = 0;
        while (!PIN_SWITCH_LIFT_BOTTOM) {
            counter++;
            pwmServoAll(20000, LIFT_PWM_BOTTOM);
            delaymSec(50);
            if (counter > 20) {
                break;
            }
        }
        pwmServoAll(20000, LIFT_PWM_MIDDLE);
        delaymSec(50);
        pwmServoAll(20000, LIFT_PWM_MIDDLE);
    } else if (commandHeader == COMMAND_LIFT_2011_UP) {
        appendAck(outputStream);
        append(outputStream, COMMAND_LIFT_2011_UP);

        pwmServoAll(20000, LIFT_PWM_MIDDLE);
        delaymSec(80);

        int counter;
        for (counter = 0; counter < 2; counter++) {
            pwmServoAll(20000, LIFT_PWM_UP);
            delaymSec(100);
        }
        pwmServoAll(20000, LIFT_PWM_MIDDLE);
        delaymSec(100);
        pwmServoAll(20000, LIFT_PWM_MIDDLE);
    } else if (commandHeader == COMMAND_LIFT_2011_DOWN) {
        appendAck(outputStream);
        append(outputStream, COMMAND_LIFT_2011_DOWN);

    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLift2011Init,
    .deviceShutDown = &deviceLift2011ShutDown,
    .deviceIsOk = &deviceLift2011IsOk,
    .deviceHandleRawData = &deviceLift2011HandleRawData,
};

DeviceDescriptor* getLift2011DeviceDescriptor() {
    return &descriptor;
}
