#ifndef ERROR_H
#define ERROR_H

/**
 * Main Method to write Error.
 * Avoid using long strings which takes program memory.
 */
void writeError(int errorCode);


// List of error Code

#define ILLEGAL_ARGUMENT_EXCEPTION 		0x001


// IO

#define IO_BUFFER_EMPTY 			 	0x0100
#define IO_BUFFER_FULL	 			 	0x0101

#define IO_PIN_INDEX_ERROR				0x0110


#define IO_READER_READ_FILTERED_CHAR	0x0120



// I2C 

#define I2C_MASTER_ALREADY_INITIALIZED 	0x1000


// DEVICE

#define TOO_MUCH_DEVICES				0x2000
#define NO_DEVICE_DESC_FOUND_FOR		0x2001

#define NO_DISPATCHER_FOUND				0x2100
#define NO_DISPATCHER_INPUT_STREAM		0x2101
#define NO_DISPATCHER_INPUT_BUFFER		0x2102
#define DEVICE_NOT_FOUND				0x2103

#define DISPATCHER_NO_CALLBACK_FOR		0x2110
#define TOO_MUCH_DRIVER_DATA_DISPATCHER	0x2111

// PID

#define PID_INDEX_INCORRECT				0x3000

#define PID_ERROR_METHOD				0x3100


#define TOO_MUCH_JENNIC_EVENT			0x4000

#endif
