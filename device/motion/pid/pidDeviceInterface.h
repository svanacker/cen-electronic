#ifndef PID_DEVICE_INTERFACE_H
#define PID_DEVICE_INTERFACE_H

#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/**
* Set the some parameters for a specific PID.
*/
#define COMMAND_WRITE_PID_PARAMETERS                'w'

/**
* Read some parameters for a specific PID
*/
#define COMMAND_READ_PID_PARAMETERS                'r'

/**
* Write into a table all PID Parameters
*/
#define COMMAND_DEBUG_PID_PARAMETERS                'R'

/**
 * Load default Values
 */
#define COMMAND_LOAD_PID_DEFAULT_VALUES            'd'

/**
 * Save Values
 */
#define COMMAND_SAVE_PID                           's'

/**
 * Debug all pid values. 
 */
#define COMMAND_PID_MOTION_PARAMETER_DEBUG         'D'

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
* Debug all values for the PID
*/
#define COMMAND_DEBUG_DATA_PID_CONSOLE              'G'

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
