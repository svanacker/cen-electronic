#ifndef PID_DEVICE_INTERFACE_H
#define PID_DEVICE_INTERFACE_H

#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/**
* Set the value of PID.
*/
#define COMMAND_WRITE_PID                      'w'

/**
* Read the value of PID.
*/
#define COMMAND_READ_PID                       'r'

/**
 * Load and save default Values
 */
#define COMMAND_LOAD_DEFAULT_VALUES            'd'

/**
* Send values to have information about profile at the begin of
* trajectory compute.
*/
#define COMMAND_SEND_MOTION_PARAMETER          'm'

/**
* Send values to have statistical debug informations.
*/
#define COMMAND_SEND_DEBUG_DATA_PID            'd'

/**
* Change end Detection Motion Parameter.
*/
#define COMMAND_SET_END_DETECTION_PARAMETER    'p'

/**
* Get the Detection Motion Parameter.
*/
#define COMMAND_GET_END_DETECTION_PARAMETER    'P'

/**
* Get the PID device interface.
*/
DeviceInterface* getPIDDeviceInterface();

#endif
