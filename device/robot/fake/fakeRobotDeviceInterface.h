#ifndef FAKE_ROBOT_DEVICE_INTERFACE_H
#define FAKE_ROBOT_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/** Command to get the position of the fake robot. */
#define COMMAND_FAKE_ROBOT_GET_POSITION           'r'  

/** Command to set the position of the fake robot. */
#define COMMAND_FAKE_ROBOT_SET_POSITION           'w'

/**
 * Get the Fake Robot device interface.
 * @return a pointer on the system device Interface.
 */
DeviceInterface* getFakeRobotDeviceInterface(void);

#endif
