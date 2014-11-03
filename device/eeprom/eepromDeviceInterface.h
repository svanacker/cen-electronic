#ifndef EEPROM_DEVICE_INTERFACE_H
#define	EEPROM_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"


// The EEPROM DEVICE HEADER

#define EEPROM_DEVICE_HEADER     'E'


// List of EEPROM COMMAND HEADER

/**
* Defines the header to read one byte from the Eeprom
*/

#define COMMAND_READ_DATA_EEPROM         'r'

/**
* Defines the header to write one byte on the Eeprom.
*/
#define COMMAND_WRITE_DATA_EEPROM         'w'

/**
* Defines the header to read the buffer from the Eeprom
*/
#define COMMAND_READ_BLOC_EEPROM         'R'

/**
* Defines the header to write the buffer on the Eeprom
*/
#define COMMAND_WRITE_BLOC_EEPROM         'W'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getEepromDeviceInterface();

#endif