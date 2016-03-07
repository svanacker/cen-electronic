#ifndef MOTOR_BOARD_H
#define MOTOR_BOARD_H

#include "../../common/io/buffer.h"

#define MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH                1

/** Define the I2C address used by motorBoard. */
#define MOTOR_BOARD_I2C_ADDRESS     0x54

#define MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH    200
#define MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH    200

/**
 * Get the I2C Slave Output Buffer.
 */
Buffer* getI2CSlaveOutputBuffer();

/** Maximal length for In Buffer length. */
#define MOTOR_BOARD_IN_BUFFER_LENGTH     200

/** Maximal length for Out Buffer length. */
#define MOTOR_BOARD_OUT_BUFFER_LENGTH    200

// DEVICES
#define MOTOR_BOARD_DEVICE_LIST_LENGTH   20

// TIMERS
#define MOTOR_BOARD_TIMER_LENGTH         2

#endif
