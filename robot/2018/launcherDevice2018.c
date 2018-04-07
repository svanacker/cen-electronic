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
#include "ioExpander/ioExpander.h"

static Launcher2018* launcher2018;

void launch2018(int launcherIndex, bool prepare) {
    Relay* relay = launcher2018->relay;
    IOExpander* ioExpander = launcher2018->ioExpander;
    
    unsigned int relayIndex = LAUNCHER_LEFT_RELAY_INDEX;
    unsigned int ioExpanderIndex = LAUNCHER_LEFT_IO_EXPANDER_INDEX;
    
    if (launcherIndex == LAUNCHER_RIGHT_INDEX) {
        relayIndex = LAUNCHER_RIGHT_RELAY_INDEX;
        ioExpanderIndex = LAUNCHER_RIGHT_IO_EXPANDER_INDEX;
    }

    if (prepare) {
        // Activate the relay
        relay->relayWriteValue(relay, relayIndex, true);
        // We wait that the contact is done -> ioExpander goes to ground (0)
        while (ioExpander->ioExpanderReadSingleValue(ioExpander, ioExpanderIndex)) {
            delaymSec(50);
        }
        // Change the motor state
        relay->relayWriteValue(relay, relayIndex, false);        
    }
    else {
        // Activate or not the relay
        relay->relayWriteValue(relay, relayIndex, true);
        // We wait that the contact is left -> ioExpander goes to +5V
        while (!ioExpander->ioExpanderReadSingleValue(ioExpander, ioExpanderIndex)) {
            delaymSec(50);
        }
        // Change the motor state
        relay->relayWriteValue(relay, relayIndex, false);    
    }
}

void deviceLauncher2018Init(void) {

}

void deviceLauncher2018ShutDown(void) {

}

bool deviceLauncher2018IsOk(void) {
    return true;
}

void deviceLauncher2018HandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
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
                      Relay* relay) {
    launcher2018->ioExpander = ioExpander;
    launcher2018->relay = relay;
}
