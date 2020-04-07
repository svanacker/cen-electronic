#include "armDevice2020.h"

#include "arm2020.h"

#include "armDeviceInterface2020.h"

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

void deviceArm2020Init(void) {

}

void deviceArm2020ShutDown(void) {

}

bool deviceArm2020IsOk(void) {
    return true;
}

void deviceArm2020HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ARM
    if (commandHeader == COMMAND_2020_ARM_CENTER) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_ARM_CENTER);
        lateralArm2020(servoList, 0x00);
    } else if (commandHeader == COMMAND_2020_ARM_LEFT) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_ARM_LEFT);
        lateralArm2020(servoList, 0x01);
    } else if (commandHeader == COMMAND_2020_ARM_RIGHT) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_ARM_RIGHT);
        lateralArm2020(servoList, 0x02);
    }// FLAG
    else if (commandHeader == COMMAND_2020_FLAG_DOWN) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_FLAG_DOWN);
        arm2020FlagDown(servoList);
    } else if (commandHeader == COMMAND_2020_FLAG_UP) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_FLAG_UP);
        arm2020FlagUp(servoList);
    }// HOOK - SIMPLE - SINGLE
    else if (commandHeader == COMMAND_2020_HOOK_DOWN) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_DOWN);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookDown(servoList, servoIndex);
    } else if (commandHeader == COMMAND_2020_HOOK_UP) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_UP);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookUp(servoList, servoIndex, false);
    } else if (commandHeader == COMMAND_2020_HOOK_TAKE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_TAKE);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookTake(servoList, servoIndex);
    } else if (commandHeader == COMMAND_2020_HOOK_RELEASE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_RELEASE);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookRelease(servoList, servoIndex, false);
    } else if (commandHeader == COMMAND_2020_HOOK_PREPARE_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_PREPARE_FLOOR);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookPrepareFloor(servoList, servoIndex);
    } else if (commandHeader == COMMAND_2020_HOOK_LOCK_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_LOCK_FLOOR);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookLockFloor(servoList, servoIndex);
    }
    // HOOK - SIMPLE - ALL
    else if (commandHeader == COMMAND_2020_HOOK_ALL_DOWN) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_DOWN);
        arm2020HookDownAll(servoList);
    }
    else if (commandHeader == COMMAND_2020_HOOK_ALL_UP) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_UP);
        arm2020HookUpAll(servoList, true);
    }
    else if (commandHeader == COMMAND_2020_HOOK_ALL_TAKE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_TAKE);
        arm2020HookTakeAll(servoList);
    }
    else if (commandHeader == COMMAND_2020_HOOK_ALL_RELEASE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_RELEASE);
        arm2020HookReleaseAll(servoList, true);
     } else if (commandHeader == COMMAND_2020_HOOK_PREPARE_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_PREPARE_FLOOR);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookPrepareFloor(servoList, servoIndex);
    }
    else if (commandHeader == COMMAND_2020_HOOK_ALL_PREPARE_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_PREPARE_FLOOR);
        arm2020HookPrepareFloorAll(servoList);
    }
    else if (commandHeader == COMMAND_2020_HOOK_LOCK_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_LOCK_FLOOR);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookLockFloor(servoList, servoIndex);
    }
    else if (commandHeader == COMMAND_2020_HOOK_ALL_LOCK_FLOOR) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_LOCK_FLOOR);
        arm2020HookLockFloorAll(servoList);
    }
    // HOOK - COMPLEX - SINGLE
    else if (commandHeader == COMMAND_2020_HOOK_PREPARE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_PREPARE);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020HookPrepare(servoList, servoIndex);
    } else if (commandHeader == COMMAND_2020_HOOK_TAKE_AND_UP) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_TAKE_AND_UP);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020TakeAndUp(servoList, servoIndex);
    } else if (commandHeader == COMMAND_2020_HOOK_DOWN_AND_RELEASE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_DOWN_AND_RELEASE);
        unsigned char servoIndex = readHex2(inputStream);
        arm2020DownAndRelease(servoList, servoIndex);
    }
    // HOOK - COMPLEX - ALL
    else if (commandHeader == COMMAND_2020_HOOK_ALL_PREPARE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_PREPARE);
        arm2020HookPrepareAll(servoList);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_TAKE_AND_UP) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_TAKE_AND_UP);
        arm2020TakeAndUpAll(servoList);
    } else if (commandHeader == COMMAND_2020_HOOK_ALL_DOWN_AND_RELEASE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_DOWN_AND_RELEASE);
        arm2020DownAndReleaseAll(servoList);
    }
    // HOOK - SEQUENCE
    else if (commandHeader == COMMAND_2020_HOOK_ALL_SEQUENCE) {
        ackCommand(outputStream, ARM_2020_DEVICE_HEADER, COMMAND_2020_HOOK_ALL_SEQUENCE);
        arm2020HookSequenceAll(servoList);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceArm2020Init,
    .deviceShutDown = &deviceArm2020ShutDown,
    .deviceIsOk = &deviceArm2020IsOk,
    .deviceHandleRawData = &deviceArm2020HandleRawData,
};

DeviceDescriptor* getArm2020DeviceDescriptor(ServoList* servoListParam) {
    servoList = servoListParam;
    return &descriptor;
}
