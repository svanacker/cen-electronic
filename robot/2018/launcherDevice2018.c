#include "launcherDevice2018.h"

#include "launcherDeviceInterface2018.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/relay/relay.h"

#include "../../main/meca1/mechanicalMainBoard1Common.h"
#include "../../drivers/ioExpander/ioExpander.h"

static Launcher2018* launcher2018;

// LIGHT

void lightOn2018(int launcherIndex) {
    unsigned int servoIndex = LAUNCHER_LIGHT_LEFT_SERVO_INDEX;
    unsigned int servoOffPosition = LAUNCHER_LIGHT_LEFT_SERVO_OFF_POSITION;
    unsigned int servoOnPosition = LAUNCHER_LIGHT_LEFT_SERVO_ON_POSITION;
    unsigned int speed = PWM_SERVO_SPEED_MAX;
    unsigned int delay = LAUNCHER_LIGHT_LEFT_SERVO_DELAY;
    
    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        servoIndex = LAUNCHER_LIGHT_RIGHT_SERVO_INDEX;
        servoOffPosition = LAUNCHER_LIGHT_RIGHT_SERVO_OFF_POSITION;
        servoOnPosition = LAUNCHER_LIGHT_RIGHT_SERVO_ON_POSITION;
        delay = LAUNCHER_LIGHT_RIGHT_SERVO_DELAY;
    }
    
    // TODO : Check this !
    // ServoList* servoList = _getServoList();
    /// servoList->useTimer = false;
    
    // pwmServo(servoIndex, speed, servoOnPosition);
    // TODO : Check it because it's really longer than 50 ms
    // delaymSec(delay);
    // pwmServo(servoIndex, speed, servoOffPosition);
}

// LAUNCH

void launch2018(int launcherIndex, bool prepare) {
    Relay* relay = launcher2018->relay;
    IOExpander* ioExpander = launcher2018->ioExpander;
    
    unsigned int relayIndex = LAUNCHER_LEFT_RELAY_INDEX;
    unsigned int ioExpanderIndex = LAUNCHER_LEFT_IO_EXPANDER_INDEX;
    int maxIteration = 100;
    
    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        relayIndex = LAUNCHER_RIGHT_RELAY_INDEX;
        ioExpanderIndex = LAUNCHER_RIGHT_IO_EXPANDER_INDEX;
    }

    if (prepare) {
        // Activate the relay
        relay->relayWriteValue(relay, relayIndex, true);
        // We wait that the contact is done -> ioExpander goes to ground (0)
        while (ioExpander->ioExpanderReadSingleValue(ioExpander, ioExpanderIndex)) {
            maxIteration--;
            if (maxIteration <= 0) {
                break;
            }
            delaymSec(5);
        }
        // Change the motor state
        relay->relayWriteValue(relay, relayIndex, false);        
    }
    else {
        // Activate or not the relay
        relay->relayWriteValue(relay, relayIndex, true);
        // We wait that the contact is left -> ioExpander goes to +5V
        while (!ioExpander->ioExpanderReadSingleValue(ioExpander, ioExpanderIndex)) {
            maxIteration--;
            if (maxIteration <= 0) {
                break;
            }
            delaymSec(5);
        }
        // Change the motor state
        relay->relayWriteValue(relay, relayIndex, false);    
    }
}

// DISTRIBUTOR

unsigned int distributor2018CleanNext(int launcherIndex) {
    signed int motorSpeed = -LAUNCHER_2018_DEFAULT_SPEED;
    signed int motorLowSpeed = -LAUNCHER_2018_LOW_SPEED;
    signed int motorVeryLowSpeed = -LAUNCHER_2018_VERY_LOW_SPEED;

    unsigned int threshold = DISTRIBUTOR_TOF_DISTANCE_THRESHOLD;
    unsigned int lowThreshold = DISTRIBUTOR_TOF_DISTANCE_LOW_THRESHOLD;
    unsigned int veryLowThreshold = DISTRIBUTOR_TOF_DISTANCE_LOW_THRESHOLD;

     signed int currentSpeed;

    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        motorSpeed *= -1;
        motorLowSpeed *= -1;
        motorVeryLowSpeed *= -1;
    }

    TofSensorList* tofSensorList = launcher2018->tofSensorList;
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, 0);
    
    currentSpeed = motorSpeed;
    setMotorSpeeds(launcher2018->dualHBridgeMotor, currentSpeed, 0);
    
    // Avoid to stay blocked if we are already on a target
    unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
    while (true) {
        distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance >= threshold) {
            break;
        }
    }
    delaymSec(50);
    // Check if we must stop
    while (true) {
        distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance != 0) {
            // Reached !
            if (distance <= threshold) {
                break;
            }
            // Low mode
            else if (currentSpeed != motorLowSpeed && distance <= lowThreshold) {
                currentSpeed = motorLowSpeed;
                setMotorSpeeds(launcher2018->dualHBridgeMotor, currentSpeed, 0);
            }
            // Very Low mode
            else if (currentSpeed != motorLowSpeed && currentSpeed != motorVeryLowSpeed && distance <= veryLowThreshold) {
                currentSpeed = motorVeryLowSpeed;
                setMotorSpeeds(launcher2018->dualHBridgeMotor, currentSpeed, 0);
            }
        }
    }
    setMotorSpeeds(launcher2018->dualHBridgeMotor, 0, 0);
    
    return distance;
}

void distributor2018EjectDirty(void) {
    /*
    // TODO : Check this !
    ServoList* servoList = _getServoList();
    servoList->useTimer = false;

    pwmServo(LAUNCHER_DIRTY_EJECTOR_SERVO_INDEX, 0xFF, LAUNCHER_DIRTY_EJECTOR_SERVO_ON_POSITION);
    // TODO : Check it because it's really longer than 50 ms
    delaymSec(LAUNCHER_DIRTY_EJECTOR_SERVO_DELAY);
    pwmServo(LAUNCHER_DIRTY_EJECTOR_SERVO_INDEX, 0xFF, LAUNCHER_DIRTY_EJECTOR_SERVO_OFF_POSITION);
    */
}

void deviceLauncher2018Init(void) {

}

void deviceLauncher2018ShutDown(void) {

}

bool deviceLauncher2018IsOk(void) {
    return true;
}

void deviceLauncher2018HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // Launcher
    if (commandHeader == LAUNCHER_PREPARE_BALL_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        launch2018(launcherIndex, true);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_PREPARE_BALL_COMMAND);
    }
    else if (commandHeader == LAUNCHER_SEND_BALL_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        launch2018(launcherIndex, false);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_SEND_BALL_COMMAND);
    }
    // Light / Bee
    else if (commandHeader == LAUNCHER_LIGHT_ON_SERVO_MOVE_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        lightOn2018(launcherIndex);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_LIGHT_ON_SERVO_MOVE_COMMAND);
    }
    // Distributor
    else if (commandHeader == DISTRIBUTOR_LOAD_NEXT_BALL_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        unsigned int distance = distributor2018CleanNext(launcherIndex);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, DISTRIBUTOR_LOAD_NEXT_BALL_COMMAND);
        appendHex2(outputStream, distance);
    }
    else if (commandHeader == DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND) {
        distributor2018EjectDirty();
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, DISTRIBUTOR_EJECT_DIRTY_BALL_COMMAND);
    }
    // Just one right color ball
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_BALL_COMMAND) {
        int launcherIndex = readHex2(inputStream);
        launch2018(launcherIndex, true);
        unsigned int distance = distributor2018CleanNext(launcherIndex);
        launch2018(launcherIndex, false);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_LOAD_AND_SEND_BALL_COMMAND);
        appendHex2(outputStream, distance);
    }
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_UNICOLOR_BALL_LIST) {
        int launcherIndex = readHex2(inputStream);
        unsigned int i;
        for (i = 0; i < 8; i++) {
            launch2018(launcherIndex, true);
            distributor2018CleanNext(launcherIndex);
            launch2018(launcherIndex, false);
        }
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_LOAD_AND_SEND_UNICOLOR_BALL_LIST);
    }
    else if (commandHeader == LAUNCHER_LOAD_AND_SEND_MIXED_BALL_LIST) {
        int launcherIndex = readHex2(inputStream);
        unsigned int i;
        // Invert the sens because we load in the other sense
        if (launcherIndex == 0) {
            launcherIndex = 1;
        }
        else {
            launcherIndex = 0;
        } 
            
        for (i = 0; i < 8; i++) {
            distributor2018CleanNext(launcherIndex);
        }
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_LOAD_AND_SEND_MIXED_BALL_LIST);
    }

}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLauncher2018Init,
    .deviceShutDown = &deviceLauncher2018ShutDown,
    .deviceIsOk = &deviceLauncher2018IsOk,
    .deviceHandleRawData = &deviceLauncher2018HandleRawData,
};


DeviceDescriptor* getLauncher2018DeviceDescriptor(Launcher2018* launcher2018Param) {
    launcher2018 = launcher2018Param;
    return &descriptor;
}

void initLauncher2018(Launcher2018* launcher2018,
                      IOExpander* ioExpander,
                      Relay* relay,
                      DualHBridgeMotor* dualHBridgeMotor,
                      TofSensorList* tofSensorList) {
    launcher2018->ioExpander = ioExpander;
    launcher2018->relay = relay;
    launcher2018->dualHBridgeMotor = dualHBridgeMotor;
    launcher2018->tofSensorList = tofSensorList;
}
