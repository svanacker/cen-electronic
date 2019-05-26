#include "goldeniumDevice2019.h"
#include "goldenium2019.h"

#include "../fork/fork2019.h"
#include "../fork/forkScan2019.h"

#include "goldeniumDeviceInterface2019.h"

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

#include "../../../drivers/tof/tofList.h"

static ServoList* servoList;
static TofSensorList* tofSensorList;

void deviceGoldenium2019Init(void) {

}

void deviceGoldenium2019ShutDown(void) {

}

bool deviceGoldenium2019IsOk(void) {
    return true;
}

void deviceGoldenium2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM);
        fork2019PrepareTakeGoldenium(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    }
    else if (commandHeader == COMMAND_2019_FORK_TAKE_GOLDENIUM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_TAKE_GOLDENIUM);
        unsigned int side = readHex(inputStream);
        bool scanOk = fork2019TakeGoldenium(servoList, tofSensorList, side);
        appendBool(outputStream, scanOk);
    }
    else if (commandHeader == COMMAND_2019_FORK_DROP_GOLDENIUM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_DROP_GOLDENIUM);
        unsigned int side = readHex(inputStream);
        fork2019DropGoldenium(servoList, side);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceGoldenium2019Init,
    .deviceShutDown = &deviceGoldenium2019ShutDown,
    .deviceIsOk = &deviceGoldenium2019IsOk,
    .deviceHandleRawData = &deviceGoldenium2019HandleRawData,
};


DeviceDescriptor* getGoldenium2019DeviceDescriptor(ServoList* servoListParam, TofSensorList* tofSensorListParam) {
    servoList = servoListParam;
    tofSensorList = tofSensorListParam;
    return &descriptor;
}
