#ifndef FILE_DEVICE_H
#define FILE_DEVICE_H

#include "../../device/deviceDescriptor.h"

/**
* Returns a descriptor on the File device.
* @return a pointer on the deviceDescriptor (which does the job with the hardware)
*/
DeviceDescriptor* getFileDeviceDescriptor(void);

#endif