#ifndef SERVO_DEVICE_INTERFACE_H
#define SERVO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_SERVO 's'

/**
* Interface for Servo Device
*/
DeviceInterface* getServoDeviceInterface();

#endif

