#ifndef SILEC_DEVICE_INTERFACE_H
#define SILEC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** wrtie a texte on the SILEC */
#define WRITE_FREQUENCY_SILEC                    'w'

/**
* Interface for the Device
* @return the Interface for the SILEC device.
*/
DeviceInterface* getSilecDeviceInterface();

#endif