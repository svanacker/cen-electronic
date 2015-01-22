#ifndef MOTOR_BOARD_PC_H
#define MOTOR_BOARD_PC_H

#define MOTOR_BOARD_PC_NAME    "motorBoardPc"

#define MOTOR_BOARD_PC_LOG_HANDLER_LIST_LENGTH					 2

#define MOTOR_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS    1


/**
 * Start Point to emulate the motor Board PC.
 */
void runMotorBoardPC(void);

/** Define the I2C address used by motorBoardPc. */
#define MOTOR_BOARD_PC_I2C_ADDRESS     0x50

#define MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH 2

#define MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH 100
#define MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH  100

// CONSOLE

#define MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH    40
#define MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH    40

/** Maximal length for In Buffer length. */
#define MOTOR_BOARD_PC_IN_BUFFER_LENGTH    50

/** Maximal length for Out Buffer length. */
#define MOTOR_BOARD_PC_OUT_BUFFER_LENGTH    50

// DEVICES
#define MOTOR_BOARD_PC_DEVICE_LIST_LENGTH        10

// TIMERS
#define MOTOR_BOARD_PC_TIMER_LENGTH         2

#endif
