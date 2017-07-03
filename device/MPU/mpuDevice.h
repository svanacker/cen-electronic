#ifndef MPU_DEVICE_H    
#define MPU_DEVICE_H

#include "../../common/MPU/MPU.h"

#include "../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the device for the MPU.
* @return a descriptor on the device for the MPU
*/
DeviceDescriptor* getMpuDeviceDescriptor();


#endif 