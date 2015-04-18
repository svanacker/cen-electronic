#ifndef SYSTEM_DEVICE_INTERFACE_H
#define SYSTEM_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to show devices list. */
#define COMMAND_DEVICE_LIST        'd'

/** Command to show the content of a device by his .*/
#define COMMAND_USAGE_SPECIFIC_DEVICE 's'

/** Command to show usage for all devices. */
#define COMMAND_USAGE              'u'

/** Command to show notification for all devices. */
#define COMMAND_NOTIFICATION       'n'

/** Command to wait a certain amount of time (in milliseconds). */
#define COMMAND_WAIT               'W'

/** Command to show the name of the PIC. */
#define COMMAND_PIC_NAME           'N'

/** Command to know if the remote board is present. */
#define COMMAND_PING               'P'

/**
* Get the system device interface.
* @return a pointer on the system device Interface.
*/
DeviceInterface* getSystemDeviceInterface(void);

/**
* Defines the name of the PIC.
* @apicName the name of the PIC (Ex : MAIN BOARD 32 ...)
*/
void setPicName(char* apicName);

/**
* Returns the name of the PIC.
* @return the name of the PIC (Ex : MAIN BOARD 32 ...)
*/
char* getPicName(void);

#endif
