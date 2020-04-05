#ifndef SERIAL_DEBUG_DEVICE_INTERFACE_H
#define SERIAL_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to see the content of Serial Buffers. */
#define COMMAND_SERIAL_DEBUG              'd'

/** Command to clear the content input & output Buffer after the write Index */
#define COMMAND_SERIAL_CLEAR_AFTER_WRITE_INDEX 'c'

/** Command to clear the Serial Input & Output Buffers. */
#define COMMAND_SERIAL_CLEAR_ALL              'C'

/** Command to list all registered Serial. */
#define COMMAND_SERIAL_LIST              'L'

/** Ask to output a char into a specific serial port. */
#define COMMAND_SERIAL_CHAR_OUTPUT            'o'

/** Ask to output 4 chars into a specific serial port. */
#define COMMAND_SERIAL_CHAR_ARRAY_OUTPUT      'O'

/** Ask to simulate an input of a char to a specific serial port. */
#define COMMAND_SERIAL_CHAR_INPUT             'i'

/** Ask to simulate an input of 4 chars to a specific serial port. */
#define COMMAND_SERIAL_CHAR_ARRAY_INPUT       'I'

/**
 * Get the serial debug device interface.
 */
DeviceInterface* getSerialDebugDeviceInterface(void);

#endif
