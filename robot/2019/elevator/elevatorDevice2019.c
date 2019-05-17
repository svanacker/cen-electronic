#include "elevatorDevice2019.h"

#include "elevator2019.h"
#include "elevatorDeviceInterface2019.h"

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

void deviceElevator2019Init(void) {

}

void deviceElevator2019ShutDown(void) {

}

bool deviceElevator2019IsOk(void) {
    return true;
}

void deviceElevator2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    bool wait = true;
    // ELEVATOR
    // -> Up/Down
    if (commandHeader == COMMAND_2019_ELEVATOR_VALUE) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_VALUE);
        unsigned int servoValue = readHex4(inputStream);
        moveElevatorAtValue(servoList, servoValue, wait);
    }
    // -> Bottom
    else if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_BOTTOM);
        moveElevatorBottom(servoList, wait);
    }
    else if (commandHeader == COMMAND_2019_ELEVATOR_DISTRIBUTOR_SCAN) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_DISTRIBUTOR_SCAN);
        moveElevatorDistributorScan(servoList, wait);
    }
    // -> Position to take the Goldenium
    else if (commandHeader == COMMAND_2019_ELEVATOR_GOLDENIUM_POSITION) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_GOLDENIUM_POSITION);
        moveElevatorToTakeGoldenium(servoList, wait);
    }
    // -> Init Position
    else if (commandHeader == COMMAND_2019_ELEVATOR_INIT_POSITION) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_INIT_POSITION);
        moveElevatorInitPosition(servoList, wait);
    }
    // -> Accelerator Second Release
    else if (commandHeader == COMMAND_2019_ELEVATOR_ACCELERATOR_SECOND_DROP) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_ACCELERATOR_SECOND_DROP);
        moveElevatorAcceleratorSecondDrop(servoList, wait);
    }
    // -> Up
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_UP);
        moveElevatorUp(servoList, wait);
    }
    // -> Left
    else if (commandHeader == COMMAND_2019_ELEVATOR_LEFT) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_LEFT);
        moveElevatorLeft(servoList, wait);
    }
    // -> Middle
    else if (commandHeader == COMMAND_2019_ELEVATOR_MIDDLE) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_MIDDLE);
        moveElevatorMiddle(servoList, wait);
    }
    // -> Right
    else if (commandHeader == COMMAND_2019_ELEVATOR_RIGHT) {
        ackCommand(outputStream, ELEVATOR_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_RIGHT);
        moveElevatorRight(servoList, wait);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceElevator2019Init,
    .deviceShutDown = &deviceElevator2019ShutDown,
    .deviceIsOk = &deviceElevator2019IsOk,
    .deviceHandleRawData = &deviceElevator2019HandleRawData,
};


DeviceDescriptor* getElevator2019DeviceDescriptor(ServoList* servoListParam) {
    servoList = servoListParam;
    return &descriptor;
}
