#ifndef CLOCK_DEVICE_INTERFACE_H
#define	CLOCK_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"


// The CLOCK DEVICE HEADER

#define CLOCK_DEVICE_HEADER     'C'


// List of CLOCK COMMAND HEADER

/**
* Defines the header to read the clock
*/

#define COMMAND_READ_CLOCK         'r'

/**
* Defines the header to write the Houre on the clock.
*/
#define COMMAND_WRITE_HOUR         'h'

/**
* Defines the header to write the Houre on the clock.
*/
#define COMMAND_WRITE_DATE         'd'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getClockDeviceInterface();

#endif