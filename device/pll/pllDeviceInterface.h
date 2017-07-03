#ifndef PLL_DEVICE_INTERFACE_H
#define PLL_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** read all values acceleration from PLL. */
#define WRITE_FREQUENCY_PLL                    'w'

/**
* Interface for the Device
* @return the Interface for the PLL device.
*/
DeviceInterface* getPllDeviceInterface();

#endif