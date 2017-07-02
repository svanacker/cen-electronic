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
#define COMMAND_WRITE_PID_PARAMETERS                'w'

/**
* Read the value of PID.
*/
#define COMMAND_READ_PID_PARAMETERS                'r'

/**
 * Load and save default Values
 */
#define COMMAND_LOAD_PID_DEFAULT_VALUES            'd'

/**
* Send values to have information about profile at the begin of
* trajectory compute.
*/
#define COMMAND_GET_MOTION_PARAMETER                'm'

/**
* Send values to have statistical debug informations.
*/
#define COMMAND_GET_DEBUG_DATA_PID                  'g'

/**
* Change end Detection Motion Parameter.
*/
#define COMMAND_SET_END_DETECTION_PARAMETER         'p'

/**
* Get the Detection Motion Parameter.
*/
#define COMMAND_GET_END_DETECTION_PARAMETER         'P'

/**
 * Returns if the simulation mode is activated.
 */
#define COMMAND_GET_SIMULATION_MODE                 's'

/**
 * Set the simulation mode on or off.
 */
#define COMMAND_SET_SIMULATION_MODE                 'S'
 
/**
* Get the PID device interface.
*/
DeviceInterface* getPIDDeviceInterface();

#endif
