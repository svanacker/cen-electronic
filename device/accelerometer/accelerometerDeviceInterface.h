#ifndef ACCELEROMETER_DEVICE_INTERFACE_H
#define ACCELEROMETER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Debug all register. */
#define COMMAND_ACCELEROMETER_DEBUG_CONFIG                      'D'

/** Show the value of accelerometers. */
#define COMMAND_ACCELEROMETER_DEBUG_VALUES                      'd'

/** Get the number of sample. */
#define COMMAND_ACCELEROMETER_GET_SAMPLE_COUNT                  's'

/** Get the value of accelerometer in milliG . */
#define COMMAND_ACCELEROMETER_GET_SAMPLE_DATA_MILLIG_G          'r'

/** Get the raw value of accelerometer. */
#define COMMAND_ACCELEROMETER_GET_SAMPLE_RAW_DATA               'R'

/** Set the threshold in milliG */
#define COMMAND_ACCELEROMETER_SET_THRESHOLD                     'T'

/** Get the threshold in milliG */
#define COMMAND_ACCELEROMETER_GET_THRESHOLD                     't'

/**
* Interface for the Device.
* @return the Interface for the Accelerometer device.
*/
DeviceInterface* getAccelerometerDeviceInterface(void);

#endif
