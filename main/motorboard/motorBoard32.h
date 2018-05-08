#ifndef MOTOR_BOARD_H
#define MOTOR_BOARD_H

#include "../../common/io/buffer.h"
#include "../../common/i2c/i2cConstants.h"

#define MOTOR_BOARD_PIC_NAME "MOTOR BOARD 32"

// LOGS

#define MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH                1

// I2C

#define MOTOR_BOARD_I2C_BUS_LIST_LENGTH                    2
#define MOTOR_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH         10

#define MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH      200
#define MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH     200

// SERIAL

// How serial many ports are available on MOTOR_BOARD
#define MOTOR_BOARD_SERIAL_LINK_LIST_LENGTH 3

// The port used to send instruction if we connect MainBoard and MotorBoard via RS232
#define MOTOR_BOARD_SERIAL_PORT_STANDARD    SERIAL_PORT_1

// The port for which we debug (we can send instruction too)
#define MOTOR_BOARD_SERIAL_PORT_DEBUG       SERIAL_PORT_2

// The port to send notification (too avoid conflicts)
#define MOTOR_BOARD_SERIAL_PORT_NOTIFICATION SERIAL_PORT_5

// EEPROM
#define MOTOR_BOARD_MEMORY_EEPROM_LENGTH    0x0500

/** Maximal length for In Buffer length. */
#define MOTOR_BOARD_IN_BUFFER_LENGTH     200

/** Maximal length for Out Buffer length. */
#define MOTOR_BOARD_OUT_BUFFER_LENGTH    200

// DEVICES
#define MOTOR_BOARD_DEVICE_LIST_LENGTH   25

// TIMERS
#define MOTOR_BOARD_TIMER_LENGTH         3

// PID MOTION INSTRUCTION COUNT
#define MOTOR_BOARD_PID_MOTION_INSTRUCTION_COUNT    20

/**
 * Get the I2C Slave Output Buffer.
 */
Buffer* getI2CSlaveOutputBuffer();

#endif
