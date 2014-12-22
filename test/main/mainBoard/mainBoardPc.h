#ifndef MAIN_BOARD_PC_H
#define MAIN_BOARD_PC_H

#define MAIN_BOARD_PC_NAME	"mainBoardPc"

#define MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH				2
#define MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH 50

// Drivers
#define MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH				40
#define MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH				40

// Console
#define MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH				40
#define MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH				40

// Devices
#define MAIN_BOARD_PC_DEVICE_LIST_LENGTH						20

/**
 * Start Point to emulate the main Board PC.
 */
void runMainBoardPC(void);

#endif
