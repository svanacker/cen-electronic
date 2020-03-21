#ifndef MECHANICAL_BOARD_1_PC_H
#define MECHANICAL_BOARD_1_PC_H

#include <stdbool.h>

#include "mechanicalMainBoard1Common.h"

#define MECHANICAL_BOARD_1_PC_NAME           "mechanicalBoard1Pc"
#define MECHANICAL_BOARD_1_PC_RUN_SINGLE     "single"
#define MECHANICAL_BOARD_1_PC_RUN_STANDARD   "standard"

#define MECHANICAL_BOARD_1_PC_LOG_HANDLER_LIST_LENGTH                     2

#define MECHANICAL_BOARD_1_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS    1

/**
 * Start Point to emulate the mechanical Board 1 PC.
 */
void runMechanicalBoard1PC(bool singleMode);

// Dispatchers

#define MECHANICAL_BOARD_1_PC_DATA_DISPATCHER_LIST_LENGTH       2

// SERIAL
#define MECHANICAL_BOARD_1_PC_SERIAL_LINK_LIST_LENGTH           2

// I2cBus
#define MECHANICAL_BOARD_1_PC_PIPE_I2C_SLAVE_NAME    L"\\\\.\\pipe\\mecanicalBoard1Pc"

#define MECHANICAL_BOARD_1_PC_I2C_BUS_LIST_LENGTH                  1
#define MECHANICAL_BOARD_1_PC_I2C_BUS_CONNECTION_LIST_LENGTH       2

#define MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH 150
#define MECHANICAL_BOARD_1_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH  150

#define MECHANICAL_BOARD_1_PC_IO_EXPANDER_LIST_LENGTH         1
#define MECHANICAL_BOARD_1_PC_IO_EXPANDER_LAUNCHER_INDEX      0

// CONSOLE

#define MECHANICAL_BOARD_1_PC_CONSOLE_INPUT_BUFFER_LENGTH     150
#define MECHANICAL_BOARD_1_PC_CONSOLE_OUTPUT_BUFFER_LENGTH    150

/** Maximal length for In Buffer length. */
#define MECHANICAL_BOARD_1_PC_IN_BUFFER_LENGTH                150

/** Maximal length for Out Buffer length. */
#define MECHANICAL_BOARD_1_PC_OUT_BUFFER_LENGTH               150

// DEVICES
#define MECHANICAL_BOARD_1_PC_DEVICE_LIST_LENGTH              20

// TIMERS
#define MECHANICAL_BOARD_1_PC_TIMER_LENGTH                     2

#endif
