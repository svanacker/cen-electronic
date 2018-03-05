#ifndef PID_DEBUG_DEVICE_INTERFACE_H
#define PID_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/** Show in a table the different value of Speed / Acceleration for each kind of move. */
#define COMMAND_MOTION_PARAMETERS_DEBUG            'M'

/**
* Write into a table all PID Parameters
*/
#define COMMAND_DEBUG_PID_PARAMETERS                'P'

/**
 * Show all values for the end Motion data.
 * @return 
 */
#define COMMAND_END_MOTION_DEBUG                   'e'

/**
 * Show the table with all instructions. 
 */
#define COMMAND_PID_MOTION_INSTRUCTION_TABLE       'L'

/**
* Debug all values for the PID as Table
*/
#define COMMAND_DEBUG_DATA_PID_CONSOLE             'G'

/**
 * Show the table with the trajectory for the current instruction
 * @return 
 */
#define COMMAND_PID_TRAJECTORY_TABLE               'T'
 
/**
* Get the PID device interface.
*/
DeviceInterface* getPidDebugDeviceInterface();

#endif
