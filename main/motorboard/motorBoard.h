#ifndef MOTOR_BOARD_H
#define MOTOR_BOARD_H

#include "../../common/io/buffer.h"

/** Define the I2C address used by motorBoard. */
#define MOTOR_BOARD_I2C_ADDRESS     0x54

#define MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH    50
#define MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH    50

/**
 * Get the I2C Slave Output Buffer.
 */
Buffer* getI2CSlaveOutputBuffer();

/** Maximal length for In Buffer length. */
#define MOTOR_BOARD_IN_BUFFER_LENGTH     50

/** Maximal length for Out Buffer length. */
#define MOTOR_BOARD_OUT_BUFFER_LENGTH    50

// DEVICES
#define MOTOR_BOARD_DEVICE_LENGTH        10

// TIMERS
#define MOTOR_BOARD_TIMER_LENGTH         2

#endif
