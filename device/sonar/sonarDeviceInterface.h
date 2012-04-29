#ifndef SONAR_DEVICE_INTERFACE_H
#define SONAR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command header to get the sonar value. */
#define COMMAND_GET_SONAR 'S'

/**
* Interface for Device "Sonar".
*/
DeviceInterface* getSonarDeviceInterface();

#endif
