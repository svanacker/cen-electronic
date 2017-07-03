#ifndef LCD_DEVICE_INTERFACE_H
#define LCD_DEVICE_INTERFACE_H

#include "../../common/string/cenString.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
* Command to write on the LCD
*/
#define COMMAND_LCD                  'w'

/**
 * Command to write "Hello World quickly !"
 */
#define COMMAND_LCD_TEST             'T'

/**
 * Command to clear the LCD
 */
#define COMMAND_CLEAR_LCD            'c'

/**
 * 
 * @return 
 */
#define COMMAND_RETRO_LCD            'r'

/**
* Define the number of fixed count of char used
* for each message.
*/
#define LCD_CHAR_COUNT_BY_MESSAGE    FIXED_CHAR_ARRAY_LENGTH 

/**
* Interface for Device.
*/
DeviceInterface* getLCDDeviceInterface();

#endif

