#ifndef SYSTEM_DEVICE_INTERFACE_H
#define SYSTEM_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to show log configuration. */
#define COMMAND_LOG '$'

/** Command to show usage for all devices. */
#define COMMAND_USAGE 'u'

/** Command to wait a certain amount of time (in milliseconds). */
#define COMMAND_WAIT 'M'

/** Command to show the name of the PIC. */
#define COMMAND_PIC_NAME 'N'


/** Command to know if the remote board is present. */
#define COMMAND_PING 'P'

/** Command to debug the I2C. */
#define COMMAND_DEBUG_I2C '"'

/**
* Get the system device interface.
*/
DeviceInterface* getSystemDeviceInterface();

/**
* Defines the name of the PIC.
*/
void setPicName(char* apicName);

/**
* Returns the name of the PIC.
*/
char* getPicName();

#endif
