#ifndef MPU_DEVICE_INTERFACE_H    
#define MPU_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** read all values acceleration from MPU. */
#define GET_ACCELERATION_MPU                  'a'

/** read all values gyroscope from MPU. */
#define GET_GYROSCOPE_MPU                     'g'

/** read temperature values from MPU. */
#define GET_TEMPERATURE_MPU                     't'

/**
* Interface for the Device
* @return the Interface for the MPU device.
*/
DeviceInterface* getMpuDeviceInterface();

#endif 