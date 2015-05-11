#ifndef EEPROM_DEVICE_INTERFACE_H
#define EEPROM_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

// List of EEPROM COMMAND HEADER

/**
* Dump the content of the Eeprom to an outputStream (can only be used on local device).
*/
#define COMMAND_DUMP_TO_LOG_OUTPUT_STREAM_EEPROM 'o'

/**
 * Clear the Eeprom by filling with 0 values
 */
#define COMMAND_CLEAR_EEPROM               'c'

/**
* Dump the content of the Eeprom into a file (can only be used on local device).
*/
#define COMMAND_DUMP_TO_FILE_EEPROM          'd'

/**
* Defines the header to read one byte from the Eeprom
*/
#define COMMAND_READ_BYTE_EEPROM         'r'

/**
* Defines the header to read an int from the Eeprom
*/
#define COMMAND_READ_INT_EEPROM         'R'

/**
* Defines the header to write one byte on the Eeprom.
*/
#define COMMAND_WRITE_BYTE_EEPROM         'w'

/**
* Defines the header to write one int on the Eeprom.
*/
#define COMMAND_WRITE_INT_EEPROM         'W'

/**
* Defines the header to read the buffer from the Eeprom
*/
#define COMMAND_READ_BLOCK_EEPROM         'b'

/**
 * Do an intensive test with read and write.
 */
#define COMMAND_INTENSIVE_TEST              'T'

/**
* Defines the header to write the buffer on the Eeprom
*/
#define COMMAND_WRITE_BLOCK_EEPROM         'B'

/**
* Defines the header to reload the content of the eeprom (useful only in Windows).
*/
#define COMMAND_RELOAD_EEPROM              'L'

// Function to get the specific Device Interface

/**
* Interface for Device.
*/
DeviceInterface* getEepromDeviceInterface();

#endif
