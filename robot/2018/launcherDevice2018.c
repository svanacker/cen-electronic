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

#include "../../main/meca1/mechanicalBoard1.h"
#include "../../drivers/ioExpander/ioExpander.h"

static Launcher2018* launcher2018;

void lightOn2018(int launcherIndex) {
    unsigned int servoIndex = LAUNCHER_LIGHT_LEFT_SERVO_INDEX;
    unsigned int servoOffPosition = LAUNCHER_LIGHT_LEFT_SERVO_OFF_POSITION;
    unsigned int servoOnPosition = LAUNCHER_LIGHT_LEFT_SERVO_ON_POSITION;
    unsigned int speed = PWM_SERVO_SPEED_MAX;
    unsigned int delay = 75;
    
    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        servoIndex = LAUNCHER_LIGHT_RIGHT_SERVO_INDEX;
        servoOffPosition = LAUNCHER_LIGHT_RIGHT_SERVO_OFF_POSITION;
        servoOnPosition = LAUNCHER_LIGHT_RIGHT_SERVO_ON_POSITION;
    }
    else if (launcherIndex == LAUNCHER_BEE_INDEX) {
        servoIndex = LAUNCHER_BEE_SERVO_INDEX;
        servoOffPosition = LAUNCHER_BEE_SERVO_OFF_POSITION;
        servoOnPosition = LAUNCHER_BEE_SERVO_ON_POSITION;
        delay = 200;
    }
    
    // TODO : Check this !
    ServoList* servoList = _getServoList();
    servoList->useTimer = false;
    
    pwmServo(servoIndex, speed, servoOnPosition);
    // TODO : Check it because it's really longer than 50 ms
    delaymSec(delay);
    pwmServo(servoIndex, speed, servoOffPosition);
}

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

void distributor2018CleanNext(int launcherIndex) {
    signed int motorSpeed = -20;
    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        motorSpeed *= -1;
    }
    unsigned int threshold = 12;
    TofSensorList* tofSensorList = launcher2018->tofSensorList;
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, 0);
    
    setMotorSpeeds(launcher2018->dualHBridgeMotor, motorSpeed, 0);
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
        if (distance <= threshold) {
            break;
        }
    }
    setMotorSpeeds(launcher2018->dualHBridgeMotor, 0, 0);
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
    else if (commandHeader == LAUNCHER_LIGHT_ON_SERVO_MOVE) {
        int launcherIndex = readHex2(inputStream);
        lightOn2018(launcherIndex);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_LIGHT_ON_SERVO_MOVE);
    }
    // Distributor
    else if (commandHeader == LAUNCHER_DISTRIBUTOR_NEXT_CLEAN_BALL) {
        int launcherIndex = readHex2(inputStream);
        distributor2018CleanNext(launcherIndex);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_DISTRIBUTOR_NEXT_CLEAN_BALL);
    }
    else if (commandHeader == LAUNCHER_SEQUENCE_CLEAN_BALL) {
        int launcherIndex = readHex2(inputStream);
        launch2018(launcherIndex, true);
        distributor2018CleanNext(launcherIndex);
        launch2018(launcherIndex, false);
        ackCommand(outputStream, LAUNCHER_2018_DEVICE_HEADER, LAUNCHER_SEQUENCE_CLEAN_BALL);
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
