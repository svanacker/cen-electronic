#ifndef MAIN_BOARD_CLIENT_H
#define MAIN_BOARD_CLIENT_H

#include "../../common/io/outputStream.h"

#include "../../main/motorBoard/motorBoard.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/beaconReceiver/beaconReceiverBoard.h"

#define MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH	30
#define MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH	30

#define MAIN_BOARD_PC_INPUT_BUFFER_LENGTH		MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH
#define MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH		MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH

/** The Input length must be equivalent to the output length of the linked board. */
#define MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH			MOTOR_BOARD_OUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_1_BUFFER_LENGTH			MECA_BOARD_1_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH			MECA_BOARD_2_OUTPUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH			BEACON_RECEIVER_BOARD_OUTPUT_BUFFER_LENGTH


#endif
