#include "distributorDevice2019.h"

#include "distributorDeviceInterface2019.h"
#include "distributor2019.h"

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

#include "../../../robot/2019/fork/fork2019.h"
#include "../../../robot/2019/fork/forkAccelerator2019.h"


static ServoList* servoList;
static TofSensorList* tofSensorList;

void deviceDistributor2019Init(void) {

}

void deviceDistributor2019ShutDown(void) {

}

bool deviceDistributor2019IsOk(void) {
    return true;
}

void deviceDistributor2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // DISTRIBUTOR
    // PrepareTake
    if (commandHeader == COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_PREPARE_TAKE);
        distributor2019PrepareTake(servoList);
    }
    // Take
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_TAKE) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_TAKE);
        distributor2019Take(servoList, tofSensorList);
    }
    // DROP
    // Fake Accelerator Drop
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_INIT) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_INIT);
        accelerator2019FakeInit(servoList);
    }
    // Prepare Fork Accelerator Drop
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_PREPARE_DROP) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_ACCELERATOR_PREPARE_DROP);
        accelerator2019PrepareDrop(servoList);
    }
    // Fake Move Forward
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_MOVE_FORWARD) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_ACCELERATOR_FAKE_MOVE_FORWARD);
        accelerator2019FakeMoveForward();
    }
    // Fork Accelerator Drop
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_ACCELERATOR_DROP);
        unsigned int firstSideToRelease = readHex(inputStream);
        if (firstSideToRelease == FORK_2019_LEFT_INDEX) {
            accelerator2019Drop(servoList, FORK_2019_LEFT_INDEX, FORK_2019_RIGHT_INDEX);
        }
        else {
            accelerator2019Drop(servoList, FORK_2019_RIGHT_INDEX, FORK_2019_LEFT_INDEX);
        }
    }
    // Complete Sequence
    else if (commandHeader == COMMAND_2019_DISTRIBUTOR_ACCELERATOR_COMPLETE_SEQUENCE) {
        ackCommand(outputStream, DISTRIBUTOR_2019_DEVICE_HEADER, COMMAND_2019_DISTRIBUTOR_ACCELERATOR_COMPLETE_SEQUENCE);
        unsigned int firstSideToRelease = readHex(inputStream);
        if (firstSideToRelease == FORK_2019_LEFT_INDEX) {
            accelerator2019CompleteSequence(servoList, FORK_2019_LEFT_INDEX, FORK_2019_RIGHT_INDEX);
        }
        else {
            accelerator2019CompleteSequence(servoList, FORK_2019_RIGHT_INDEX, FORK_2019_LEFT_INDEX);
        }
    }

}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceDistributor2019Init,
    .deviceShutDown = &deviceDistributor2019ShutDown,
    .deviceIsOk = &deviceDistributor2019IsOk,
    .deviceHandleRawData = &deviceDistributor2019HandleRawData,
};


DeviceDescriptor* getDistributor2019DeviceDescriptor(ServoList* servoListParam, TofSensorList* tofSensorListParam) {
    servoList = servoListParam;
    tofSensorList = tofSensorListParam;
    return &descriptor;
}
