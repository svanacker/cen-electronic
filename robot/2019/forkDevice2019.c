#include "forkDevice2019.h"

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

void moveServo(
               unsigned int leftRight,
               unsigned int leftServoIndex,
               unsigned int rightServoIndex,
               unsigned int leftSpeed,
               unsigned int rightSpeed,
               unsigned int leftPosition,
               unsigned rightPosition) {
    if (leftRight == FORK_2019_LEFT_AND_RIGHT_INDEX || leftRight == FORK_2019_LEFT_INDEX) {
        Servo* servo = getServo(servoList, leftServoIndex);
        pwmServo(servo, leftSpeed, leftPosition);
    }
    if (leftRight == FORK_2019_LEFT_AND_RIGHT_INDEX || leftRight == FORK_2019_RIGHT_INDEX) {
        Servo* servo = getServo(servoList, rightServoIndex);
        pwmServo(servo, rightSpeed, rightPosition);
    }    
}

void moveElevatorBottom(void) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE);
}

void moveElevatorUp(void) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_UP_SERVO_VALUE);
}

void moveElevatorDoublePuck(void) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_DOUBLE_PUCK_SERVO_VALUE);
}


void moveForkBack(unsigned int leftRight) {
    moveServo(leftRight, 
            FORK_2019_LEFT_SERVO_INDEX, FORK_2019_RIGHT_SERVO_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE, FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE);
}

void moveForkSimplePuck(unsigned int leftRight) {
    moveServo(leftRight, 
            FORK_2019_LEFT_SERVO_INDEX, FORK_2019_RIGHT_SERVO_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE);
}

void moveForkDoublePuck(unsigned int leftRight) {
    moveServo(leftRight, 
            FORK_2019_LEFT_SERVO_INDEX, FORK_2019_RIGHT_SERVO_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE);
}

void moveForkPushOff(unsigned int leftRight) {
    moveServo(leftRight, 
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_OFF_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_OFF_SERVO_VALUE);
}

void moveForkPushOn(unsigned int leftRight) {
    moveServo(leftRight, 
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_ON_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_ON_SERVO_VALUE);
}

void forkScan() {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_RIGHT_SERVO_VALUE);
    delaymSec(500);
    unsigned int i;
    for (i = FORK_2019_SCAN_RIGHT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i+= 10) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, 0);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance > 0 && distance < 16) {
            appendStringAndDecLN(getDebugOutputStreamLogger(), "distance=", distance);
            break;
        }
        delaymSec(10);
    }
}

void deviceFork2019HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // ELEVATOR
    // -> Bottom
    if (commandHeader == COMMAND_2019_ELEVATOR_BOTTOM) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_BOTTOM);
        moveElevatorBottom();
    }
    // -> Middle for Double Puck Position
    else if (commandHeader == COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_DOUBLE_PUCK_POSITION);
        moveElevatorDoublePuck();
    }
    // -> Up
    else if (commandHeader == COMMAND_2019_ELEVATOR_UP) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_ELEVATOR_UP);
        moveElevatorUp();
    }
    // Fork Back/Retracted
    else if (commandHeader == COMMAND_2019_FORK_BACK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_BACK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkBack(servoIndex); 
    }
    // Fork Single Puck
    else if (commandHeader == COMMAND_2019_FORK_SIMPLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SIMPLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkSimplePuck(servoIndex);

    }
    // Fork Double Puck
    else if (commandHeader == COMMAND_2019_FORK_DOUBLE_PUCK) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_DOUBLE_PUCK);
        unsigned int servoIndex = readHex(inputStream);
        moveForkDoublePuck(servoIndex);
        
    }
    // Fork Push Off
    else if (commandHeader == COMMAND_2019_FORK_PUSH_OFF) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_OFF);
        unsigned int servoIndex = readHex(inputStream);
        moveForkPushOff(servoIndex);
    }
    // Fork Push On
    else if (commandHeader == COMMAND_2019_FORK_PUSH_ON) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_PUSH_ON);
        unsigned int servoIndex = readHex(inputStream);
        moveForkPushOn(servoIndex);
    }
    // Init
    else if (commandHeader == COMMAND_2019_FORK_INIT) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_INIT);
        // Left/Right Elevator
        // TODO
        
        // Elevator
        moveElevatorBottom();
        
        // Fork Push Off
        moveForkPushOff(FORK_2019_LEFT_AND_RIGHT_INDEX);
        
        // Fork Retracted
        moveForkBack(FORK_2019_LEFT_AND_RIGHT_INDEX);
    }
    else if (commandHeader == COMMAND_2019_FORK_TAKE) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_TAKE);
     
        // Elevator
        moveElevatorBottom();
        delaymSec(1000);
        
        // Fork Push Off
        moveForkPushOff(FORK_2019_LEFT_AND_RIGHT_INDEX);
        delaymSec(500);
        
        // Fork Single Puck
        moveForkSimplePuck(FORK_2019_LEFT_AND_RIGHT_INDEX);
        delaymSec(1000);
        
        // Elevator
        moveElevatorUp();
        delaymSec(1000);
    }
    else if (commandHeader == COMMAND_2019_FORK_RELEASE) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_RELEASE);
     
        // Elevator
        moveElevatorUp();
        delaymSec(1000);
        
        // Fork Push On
        moveForkPushOn(FORK_2019_LEFT_AND_RIGHT_INDEX);
        delaymSec(500);
        
        // Fork 
        moveForkBack(FORK_2019_LEFT_AND_RIGHT_INDEX);
        delaymSec(1000);
        
        // Fork Push Off
        moveForkPushOff(FORK_2019_LEFT_AND_RIGHT_INDEX);
        delaymSec(500);
    }
    else if (commandHeader == COMMAND_2019_FORK_SCAN) {
        ackCommand(outputStream, FORK_2019_DEVICE_HEADER, COMMAND_2019_FORK_SCAN);
        forkScan();
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
