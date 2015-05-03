#ifndef LCD_DEVICE_INTERFACE_H
#define LCD_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command to write on the LCD
*/
#define COMMAND_LCD                  'w'

/**
 * Command to clear the LCD
 */
#define COMMAND_CLEAR_LCD            'c'

/**
* Define the number of fixed count of char used
* for each message.
*/
#define LCD_CHAR_COUNT_BY_MESSAGE     4

/**
* Interface for Device.
*/
DeviceInterface* getLCDDeviceInterface();

#endif

