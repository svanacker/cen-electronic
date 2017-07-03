#ifndef LED_DEVICE_INTERFACE_H
#define LED_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Get the value of an ADC. */
#define COMMAND_WRITE_LED                   'w'

#define COMMAND_TEST_LED                    't'

/**
* Interface for the Device
* @return the Interface for the LED device.
*/
DeviceInterface* getLedDeviceInterface();

#endif
