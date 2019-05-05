#ifndef ELECTRON_LAUNCHER_DEVICE_INTERFACE_2019_H
#define ELECTRON_LAUNCHER_DEVICE_INTERFACE_2019_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

#include "../../common/pwm/servo/servoList.h"

// Electron Launcher Debug
#define COMMAND_ELECTRON_LAUNCHER_2019_DEBUG               'd'

// Electron Launcher Launch
#define COMMAND_ELECTRON_LAUNCHER_2019_LAUNCH              'L'

// Electron Launcher Show Experience !
#define COMMAND_ELECTRON_LAUNCHER_2019_SHOW                'S'

// Electron Launcher Init
#define COMMAND_ELECTRON_LAUNCHER_2019_INIT                'I'


/**
 * Get the device interface for Electron Launcher 2019.
 */
DeviceInterface* getElectronLauncher2019DeviceInterface(void);

#endif
