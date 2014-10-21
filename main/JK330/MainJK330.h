#ifndef MAINJK330_H
#define MAINJK330_H

#include "../../common/io/outputStream.h"
#include "../../common/serial/serial.h"

#include "../../main/motorboard/motorBoard.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/beaconReceiver/beaconReceiverBoard.h"
#include "../../main/strategy/strategyMain.h"


// DEBUG UART

#define MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH    28
#define MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH    28

// PC UART

#define MAIN_BOARD_PC_INPUT_BUFFER_LENGTH        MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH + 2
#define MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH        MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH + 2

// DISPATCHER DATA

/** The Input length must be equivalent to the output length of the linked board. */
#define MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH            MOTOR_BOARD_OUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_1_BUFFER_LENGTH            MECA_BOARD_1_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH            MECA_BOARD_2_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH            BEACON_RECEIVER_BOARD_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_STRATEGY_BOARD_BUFFER_LENGTH          STRATEGY_BOARD_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_AIR_CONDITIONING_BOARD_BUFFER_LENGTH  AIR_CONDITIONING_BOARD_OUTPUT_BUFFER_LENGTH

// I2C DEBUG

#define MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH           30
#define MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH            30


// DRIVER

#define MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH                    30
#define MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH                30

// DEVICE

#define MAIN_BOARD_DEVICE_LENGTH            20
#define MAIN_BOARD_TIMER_LENGTH             5

#endif