#ifndef PID_DEVICE_INTERFACE_H
#define PID_DEVICE_INTERFACE_H

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

// PARAMETERS

/** Defines the COMMAND used to get speed / acceleration parameters for different motion type. */
#define COMMAND_GET_MOTION_PARAMETERS                'm'

/** Defines the COMMAND used to set speed / acceleration parameters for different motion type. */
#define COMMAND_SET_MOTION_PARAMETERS                'M'

/**
 * Read some parameters for a specific PID
 */
#define COMMAND_GET_PID_PARAMETERS                   'p'

/**
 * Set the some parameters for a specific PID.
 */
#define COMMAND_SET_PID_PARAMETERS                   'P'

// PERSISTENCE

/**
 * Load default Values
 */
#define COMMAND_LOAD_PID_PARAMETERS_DEFAULT_VALUES  'D'

/**
 * Save Values
 */
#define COMMAND_SAVE_PID_PARAMETERS                 'S'

/**
 * Send values to have information about profile at the begin of
 * trajectory compute.
 */
#define COMMAND_GET_MOTION_DEFINITION_TRAJECTORY    't'

/**
 * Send values to have statistical debug informations.
 */
#define COMMAND_GET_COMPUTATION_VALUES_DATA_PID     'g'

/**
 * Clear the history of computation Values.
 */
#define COMMAND_CLEAR_COMPUTATION_VALUES_DATA_PID   'H'

/**
 * This is interesting to be able to replay a set of data and check behaviour or new behaviour with new parameters.
 */
#define COMMAND_SET_COMPUTATION_VALUES_DATA_PID     'G'

// END DETECTION PARAMETER

#define COMMAND_GET_END_DETECTION_PARAMETER_DETAIL  'u'

#define COMMAND_SET_END_DETECTION_PARAMETER_DETAIL  'U'

/**
 * Get the Detection Motion Parameter.
 */
#define COMMAND_GET_END_DETECTION_PARAMETER_AGGREGATION         'e'

/**
 * Change end Detection Motion Parameter.
 */
#define COMMAND_SET_END_DETECTION_PARAMETER_AGGREGATION         'E'

/**
 * Get the PID device interface.
 */
DeviceInterface* getPidDeviceInterface();

#endif
