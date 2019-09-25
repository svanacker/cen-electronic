#include "electronLauncherDevice2019.h"

#include "electronLauncher2019.h"
#include "electronLauncher2019Debug.h"
#include "electronLauncherDeviceInterface2019.h"

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

static ElectronLauncher2019* launcher;

void deviceElectronLauncher2019Init(void) {

}

void deviceElectronLauncher2019ShutDown(void) {

}

bool deviceElectronLauncher2019IsOk(void) {
    return true;
}

void deviceElectronLauncher2019HandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // DEBUG
    if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_DEBUG) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_DEBUG);
        electronLauncher2019Debug(launcher, getDebugOutputStreamLogger());
    }
    // LAUNCH
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_LAUNCH) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_LAUNCH);
        electronLauncher2019Launch(launcher);
    }
    // SHOW
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SHOW) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_SHOW);
        electronLauncher2019Show(launcher);
    }
    // INIT
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_INIT) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_INIT);
        electronLauncher2019Reset(launcher);
    }
    // SIMULATE ROBOT PLACED
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED);
        electronLauncher2019SimulateRobotPlaced(launcher);
    }
    // SIMULATE ROBOT MOVED
    else if (commandHeader == COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED_AND_MOVED) {
        ackCommand(outputStream, ELECTRON_LAUNCHER_2019_DEVICE_HEADER, COMMAND_ELECTRON_LAUNCHER_2019_SIMULATE_ROBOT_PLACED_AND_MOVED);
        electronLauncher2019SimulateRobotPlacedAndMoved(launcher);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceElectronLauncher2019Init,
    .deviceShutDown = &deviceElectronLauncher2019ShutDown,
    .deviceIsOk = &deviceElectronLauncher2019IsOk,
    .deviceHandleRawData = &deviceElectronLauncher2019HandleRawData,
};


DeviceDescriptor* getElectronLauncher2019DeviceDescriptor(ElectronLauncher2019* launcherParam) {
    launcher = launcherParam;
    return &descriptor;
}
