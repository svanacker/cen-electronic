#include "forkDevice2019.h"

#include "fork2019.h"
#include "forkDeviceInterface2019.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoList.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/deviceConstants.h"

#include "../../drivers/tof/tofList.h"

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
    // ELEVATOR
    // -> Up/Down
    if (commandHeader == COMMAND_2019_ELEVATOR_VALUE) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_VALUE);
        unsigned int servoValue = readHex4(inputStream);
        moveElevatorAtValue(servoList, servoValue);
    }
    // -> Bottom
    else if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_BOTTOM);
        moveElevatorBottom(servoList);
    }
    // -> Middle for Double Puck Position
    else if (commandHeader == COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION);
        moveElevatorDoublePuck(servoList);
    }
    // -> Init Position
    else if (commandHeader == COMMAND_2019_ELEVATOR_INIT_POSITION) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_INIT_POSITION);
        moveElevatorDoublePuck(servoList);
    }
    // -> Up
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_UP);
        moveElevatorUp(servoList);
    }
    // -> Left
    else if (commandHeader == COMMAND_2019_ELEVATOR_LEFT) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_LEFT);
        moveElevatorLeft(servoList);
    }
    // -> Left
    else if (commandHeader == COMMAND_2019_ELEVATOR_RIGHT) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_RIGHT);
        moveElevatorRight(servoList);
    }
    // Fork Back/Retracted
    else if (commandHeader == COMMAND_2019_FORK_BACK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_BACK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkBack(servoList, servoIndex); 
    }
    // Fork Single Puck
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SIMPLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkSimplePuck(servoList, servoIndex);
    }
    // Fork Double Puck
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_DOUBLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkDoublePuck(servoList, servoIndex);
        
    }
    // Fork Push Off
    else if (commandHeader == COMMAND_2019_FORK_PUSH_OFF) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_OFF);
        unsigned int servoIndex = readHex(inputStream);
        moveForkPushOff(servoList, servoIndex);
    }
    // Fork Push On
    else if (commandHeader == COMMAND_2019_FORK_PUSH_ON) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_ON);
        unsigned int servoIndex = readHex(inputStream);
        moveForkPushOn(servoList, servoIndex);
    }
    // Init
    else if (commandHeader == COMMAND_2019_FORK_INIT) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_INIT);
        fork2019Init(servoList);
    }
    // Take
    else if (commandHeader == COMMAND_2019_FORK_TAKE_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_TAKE_SIMPLE_PUCK);
        fork2019TakeSimplePuck(servoList);
    }
    else if (commandHeader == COMMAND_2019_FORK_TAKE_GOLDENIUM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_TAKE_GOLDENIUM);
        fork2019TakeGoldenium(servoList);
    }
    // Release
    else if (commandHeader == COMMAND_2019_FORK_RELEASE) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_RELEASE);
        fork2019Release(servoList);
    }
    // Scan
    else if (commandHeader == COMMAND_2019_FORK_SCAN) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SCAN);
        forkScanFromLeftToRight(servoList, tofSensorList);
    }
    // ARM ON & OFF
    else if (commandHeader == COMMAND_2019_ARM_ON) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ARM_ON);
        unsigned int servoIndex = readHex(inputStream);
        arm2019On(servoList, servoIndex);
    }
    else if (commandHeader == COMMAND_2019_ARM_OFF) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ARM_OFF);
        unsigned int servoIndex = readHex(inputStream);
        arm2019Off(servoList, servoIndex);
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
