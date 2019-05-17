#include "forkDevice2019.h"

#include "../arm/arm2019.h"
#include "fork2019.h"
#include "forkAccelerator2019.h"
#include "forkGoldenium2019.h"
#include "forkScan2019.h"

#include "forkDeviceInterface2019.h"

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

void deviceFork2019Init(void) {

}

void deviceFork2019ShutDown(void) {

}

bool deviceFork2019IsOk(void) {
    return true;
}

void deviceFork2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    bool wait = true;
    // Fork Back/Retracted
    if (commandHeader == COMMAND_2019_FORK_BACK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_BACK);
        unsigned int side = readHex(inputStream);
        moveForkBack(servoList, side, wait);
    }
    // Fork Single Puck
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SIMPLE_PUCK);
        unsigned int side = readHex(inputStream);
        moveForkSimplePuck(servoList, side, wait);
    }
    // Fork Double Puck
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_DOUBLE_PUCK);
        unsigned int side = readHex(inputStream);
        moveForkDoublePuck(servoList, side, wait);
        
    }
    // Fork Push Off
    else if (commandHeader == COMMAND_2019_FORK_PUSH_OFF) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_OFF);
        unsigned int side = readHex(inputStream);
        moveForkPushOff(servoList, side, wait);
    }
    // Fork Push On
    else if (commandHeader == COMMAND_2019_FORK_PUSH_ON) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_ON);
        unsigned int side = readHex(inputStream);
        moveForkPushOn(servoList, side, wait);
    }
    // Init
    else if (commandHeader == COMMAND_2019_FORK_INIT) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_INIT);
        fork2019Init(servoList);
    }
    // Take
    else if (commandHeader == COMMAND_2019_FORK_TAKE_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_TAKE_SIMPLE_PUCK);
        fork2019TakeSimplePuck(servoList, tofSensorList);
    }
    else if (commandHeader == COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM) {
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
    // Fork Accelerator Drop
    else if (commandHeader == COMMAND_2019_FORK_ACCELERATOR_DROP) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_ACCELERATOR_DROP);
        unsigned int firstSideToRelease = readHex(inputStream);
        if (firstSideToRelease == FORK_2019_LEFT_INDEX) {
            fork2019AcceleratorDrop(servoList, FORK_2019_LEFT_INDEX, FORK_2019_RIGHT_INDEX);
        }
        else {
            fork2019AcceleratorDrop(servoList, FORK_2019_RIGHT_INDEX, FORK_2019_LEFT_INDEX);
        }
    }
    // Scan
    else if (commandHeader == COMMAND_2019_FORK_SCAN) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SCAN);
        unsigned int side = readHex(inputStream);
        bool scanOk = forkScan(servoList, tofSensorList, side);
        appendBool(outputStream, scanOk);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceFork2019Init,
    .deviceShutDown = &deviceFork2019ShutDown,
    .deviceIsOk = &deviceFork2019IsOk,
    .deviceHandleRawData = &deviceFork2019HandleRawData,
};


DeviceDescriptor* getFork2019DeviceDescriptor(ServoList* servoListParam, TofSensorList* tofSensorListParam) {
    servoList = servoListParam;
    tofSensorList = tofSensorListParam;
    return &descriptor;
}
