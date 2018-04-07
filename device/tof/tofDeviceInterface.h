#ifndef TOF_DEVICE_INTERFACE_H
#define TOF_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command header to get the sonar value. */
#define COMMAND_TOF_GET_DISTANCE      'r'

/** Command header to debug all Tof */
#define COMMAND_TOF_DEBUG             'd'

/** Command header to launch a tracker system with a notification system */
#define COMMAND_TOF_TRACK             't'


/**
* Interface for Device "Time of Flight".
*/
DeviceInterface* getTofDeviceInterface();

#endif
