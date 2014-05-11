#ifndef SONAR_DEVICE_INTERFACE_H
#define SONAR_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define SONAR_DEVICE_HEADER				'<'

/** Command header to get the sonar value. */
#define COMMAND_GET_SONAR 				'r'

/** Command header to change the address. */
#define COMMAND_SONAR_CHANGE_ADDRESS	'@'

/**
* Interface for Device "Sonar".
*/
DeviceInterface* getSonarDeviceInterface();

#endif
