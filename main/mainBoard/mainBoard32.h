#ifndef MAIN_BOARD_32_H
#define MAIN_BOARD_32_H

#include "../../common/io/outputStream.h"

#include "../../main/motorBoard/motorBoard32.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/beaconReceiver/beaconReceiverBoard.h"
#include "../../main/strategy/strategyMain.h"

#include "../../robot/match/startMatch.h"

// UART
#define SERIAL_PORT_DEBUG         SERIAL_PORT_2 
#define SERIAL_PORT_PC            SERIAL_PORT_6
#define SERIAL_PORT_MOTOR         SERIAL_PORT_5
#define SERIAL_PORT_MECA2         SERIAL_PORT_1

// LOGS
#define MAIN_BOARD_LOG_HANDLER_LIST_LENGTH   2

// DEBUG UART

#define MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH    100
#define MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH    100

// MOTOR UART

#define MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH    100
#define MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH   100

// PC UART

#define MAIN_BOARD_PC_INPUT_BUFFER_LENGTH        100
#define MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH       100

// MECHANICAL BOARD 2
#define MAIN_BOARD_MECA2_INPUT_BUFFER_LENGTH        100
#define MAIN_BOARD_MECA2_OUTPUT_BUFFER_LENGTH       100

// DISPATCHER DATA

#define MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH   5
#define MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH       100
#define MAIN_BOARD_UART_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH      100

/** The Input length must be equivalent to the output length of the linked board. */
#define MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH            MOTOR_BOARD_OUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_1_BUFFER_LENGTH            MECA_BOARD_1_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH            MECA_BOARD_2_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH            BEACON_RECEIVER_BOARD_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_STRATEGY_BOARD_BUFFER_LENGTH          STRATEGY_BOARD_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_AIR_CONDITIONING_BOARD_BUFFER_LENGTH  AIR_CONDITIONING_BOARD_OUTPUT_BUFFER_LENGTH



// I2C DEBUG

#define MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH           50
#define MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH            50

// DRIVER

#define MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH                 50
#define MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH                50

// DEVICE

#define MAIN_BOARD_DEVICE_LENGTH            25
#define MAIN_BOARD_TIMER_LENGTH             5

bool mainBoardWaitForInstruction(StartMatch* startMatch);

#endif