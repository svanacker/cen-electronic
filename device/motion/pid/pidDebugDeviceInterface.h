#ifndef PID_DEBUG_DEVICE_INTERFACE_H
#define PID_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/**
* Write into a table all PID Parameters
*/
#define COMMAND_DEBUG_PID_PARAMETERS                'R'

/**
 * Show all values for the end Motion data.
 * @return 
 */
#define COMMAND_END_MOTION_DEBUG                   'e'

/**
 * Debug all pid values. 
 */
#define COMMAND_PID_MOTION_PARAMETER_DEBUG         'D'

/**
* Debug all values for the PID as Table
*/
#define COMMAND_DEBUG_DATA_PID_CONSOLE              'G'

 
/**
* Get the PID device interface.
*/
DeviceInterface* getPidDebugDeviceInterface();

#endif
