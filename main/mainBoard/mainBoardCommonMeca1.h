#ifndef MAIN_BOARD_COMMON_MECA1_H
#define MAIN_BOARD_COMMON_MECA1_H

#include "mainBoardCommon.h"

// MECHANICAL BOARD 1
#define MAIN_BOARD_MECA_1_INPUT_BUFFER_LENGTH        2000
#define MAIN_BOARD_MECA_1_OUTPUT_BUFFER_LENGTH       2000

/** The Input length must be equivalent to the output length of the linked board. */
#define MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH            MOTOR_BOARD_OUT_BUFFER_LENGTH
#define MAIN_BOARD_LINK_TO_MECA_BOARD_1_BUFFER_LENGTH            MECA_BOARD_32_1_OUTPUT_BUFFER_LENGTH

/**
 * Add the devices to connect the MainBoard and the meca1
 */
void mainBoardCommonMeca1AddDevices(void);

/**
 * Add the Dispatcher for the Mecanical Board 1.
 */
void mainBoardCommonMeca1AddDispatcher(void);

#endif
