#ifndef MOTOR_BOARD_PC_H
#define MOTOR_BOARD_PC_H

#include <stdbool.h>

#define MOTOR_BOARD_PC_NAME         "motorBoardPc"
#define MOTOR_BOARD_PC_RUN_SINGLE   "single"
#define MOTOR_BOARD_PC_RUN_STANDARD "standard"

#define MOTOR_BOARD_PC_LOG_HANDLER_LIST_LENGTH                     2

#define MOTOR_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS    1


/**
 * Start Point to emulate the motor Board PC.
 */
void runMotorBoardPC(bool singleMode);

/** Define the I2C address used by motorBoardPc. */
#define MOTOR_BOARD_PC_I2C_ADDRESS     0x50

// Dispatchers

#define MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH       2

// SERIAL
#define MOTOR_BOARD_PC_SERIAL_LINK_LIST_LENGTH           2

// I2cBus
#define MOTOR_BOARD_PC_PIPE_I2C_SLAVE_NAME    L"\\\\.\\pipe\\motorBoardPipe"

#define MOTOR_BOARD_PC_I2C_BUS_LIST_LENGTH                  1
#define MOTOR_BOARD_PC_I2C_BUS_CONNECTION_LIST_LENGTH       2

#define MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH 150
#define MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH  150

// CONSOLE

#define MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH     150
#define MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH    150

/** Maximal length for In Buffer length. */
#define MOTOR_BOARD_PC_IN_BUFFER_LENGTH                150

/** Maximal length for Out Buffer length. */
#define MOTOR_BOARD_PC_OUT_BUFFER_LENGTH               150

// DEVICES
#define MOTOR_BOARD_PC_DEVICE_LIST_LENGTH              20

// TIMERS
#define MOTOR_BOARD_PC_TIMER_LENGTH                    3

// PID MOTION INSTRUCTION COUNT
#define MOTOR_BOARD_PC_PID_MOTION_INSTRUCTION_COUNT    10

#endif
