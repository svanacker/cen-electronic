#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

/**
 * Main Method to write Error.
 * Avoid using long strings which takes program memory.
 * @param errorCode the error Code
 */
void writeError(int errorCode);

/**
 * Returns the last error.
 * @returns the last error code, 0x0000 if there is no error
 */
int getLastError();

/**
 * Returns if there is an error.
 * @return true if there is an error (lastError > 0), false else.
 */
bool isThereAnyError();

/**
 * Clears the last error, to avoid that we take into consideration an old error.
 */
void clearLastError();

// List of error Code

#define ILLEGAL_ARGUMENT_EXCEPTION         0x001

// IO

#define IO_BUFFER_EMPTY                  0x0100
#define IO_BUFFER_FULL                   0x0101
#define IO_BUFFER_NULL                    0x0102
#define IO_BUFFER_NOT_ENOUGH_DATA         0x0103

#define PRINT_WRITER_NOT_HEX_VALUE		0x0104

#define IO_PIN_INDEX_ERROR                0x0110


#define IO_READER_READ_FILTERED_CHAR    0x0120
#define IO_READER_CHECK_CHAR_PROBLEM    0x0130


// TIMER
#define TIMERS_LIST_NOT_INITIALIZED		0x0200
#define TOO_MUCH_TIMERS                 0x0201

// EEPROM
#define EEPROM_NULL						0x280
#define EEPROM_NOT_INITIALIZED			0x281
#define EEPROM_OUT_OF_BOUNDS			0x282

// BIT LIST
#define BIT_LIST_ARRAY_OUT_OF_BOUNDS    0x0300

// PWM
#define PWM_NOT_AVAILABLE                0x0400
#define PWM_VALUE_MUST_BE_POSITIVE        0x0401

// OTHERS COMMON ERRORS
#define UNIMPLETEMENTED_EXCEPTION        0x500

// I2C 

#define I2C_MASTER_ALREADY_INITIALIZED    0x1000
#define I2C_SLAVE_ALREADY_INITIALIZED     0x1001


// DEVICE

#define TOO_MUCH_DEVICES                0x2000
#define NO_DEVICE_DESC_FOUND_FOR        0x2001
#define DEVICES_LIST_NOT_INITIALIZED    0x2002

#define DEVICE_TEST_INTENSIVE_CHECK_PROBLEM 0x2010

// -> Dispatcher
#define NO_DISPATCHER_FOUND                0x2100
#define NO_DISPATCHER_INPUT_STREAM        0x2101
#define NO_DISPATCHER_INPUT_BUFFER        0x2102
#define DEVICE_NOT_FOUND                0x2103

#define DISPATCHER_NO_CALLBACK_FOR_NOTIFICATION 0x2110
#define TOO_MUCH_DRIVER_DATA_DISPATCHER    0x2111
#define DISPATCHERS_LIST_NOT_INITIALIZED   0x2120

// DRIVER

#define DRIVER_STREAM_LISTENER_INPUT_BUFFER_NULL    0x2200
#define DRIVER_STREAM_LISTENER_OUTPUT_BUFFER_NULL    0x2201
#define DRIVER_INPUT_STREAM_NULL                    0x2210

#define TOO_MUCH_DRIVERS                0x2300


// PID

#define PID_INDEX_INCORRECT                0x3000

// Zigbee
#define TOO_MUCH_JENNIC_EVENT            0x4000


// Specific
#define TOO_MUCH_GAME_BOARD_ELEMENTS    0x5000
#define TOO_MUCH_STRATEGIES                0x5010
#define TOO_MUCH_STRATEGY_ITEMS            0x5020
#define TOO_MUCH_TARGETS                0x5030
#define TOO_MUCH_LOCATIONS                0x5040
#define TOO_MUCH_PATHS                    0x5050
#define TOO_MUCH_ACTION                    0x5060
#define TOO_MUCH_TARGET_ACTION            0x5070
#define TOO_MUCH_TARGET_ACTION_ITEM        0x5080

#endif
