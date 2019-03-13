#ifndef MAIN_BOARD_COMMON_H
#define MAIN_BOARD_COMMON_H

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/serial/serial.h"

#include "../../common/i2c/i2cBusList.h"

#include "../../robot/config/robotConfig.h"

#include "../../common/pwm/servo/servoList.h"

// DEVICE

#define MAIN_BOARD_DEVICE_LENGTH                                       40
#define MAIN_BOARD_TIMER_LIST_LENGTH                                    5

// SERVO 
#define MAIN_BOARD_SERVO_LIST_LENGTH                                   21

// IO EXPANDER
#define MAIN_BOARD_IO_EXPANDER_LIST_LENGTH                              1

// TOFS
#define MAIN_BOARD_TOF_SENSOR_LIST_LENGTH                               1

// UART
#define MAIN_BOARD_SERIAL_LINK_LIST_LENGTH                              4
#define MAIN_BOARD_SERIAL_PORT_DEBUG                        SERIAL_PORT_2
#define MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY                 SERIAL_PORT_5

#define MAIN_BOARD_SERIAL_PORT_MOTOR                        SERIAL_PORT_1
#define MAIN_BOARD_SERIAL_PORT_MECA_1                       SERIAL_PORT_6

// I2C

#define MAIN_BOARD_I2C_BUS_LIST_LENGTH                                  2
#define MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH                      20

// LOGS
#define MAIN_BOARD_LOG_HANDLER_LIST_LENGTH                              2

// DEBUG UART

#define MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH                         2000
#define MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH                        2000

// MOTOR UART

#define MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH                         8000
#define MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH                        8000

// NOTIFY UART

#define MAIN_BOARD_MOTOR_NOTIFY_INPUT_BUFFER_LENGTH                  8000
#define MAIN_BOARD_MOTOR_NOTIFY_OUTPUT_BUFFER_LENGTH                 8000

// DISPATCHER DATA

#define MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH                   7
#define MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH     200
#define MAIN_BOARD_UART_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH   2000

// I2C DEBUG

#define MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH                 200
#define MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH                  200

// DRIVER

#define MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH                      2000
#define MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH                     2000

// SERVO LIST
ServoList* mainBoardCommonGetServoList(void);

// LOG LIST

/**
 * Init the array of logs.
 */
void mainBoardCommonInitLogs(void);

// BUS LIST

/**
 * Init the 2 I2C Bus of the Main Board.
 */
void mainBoardCommonInitBusList(void);

/**
 * Returns the main I2C Bus used on 
 */
I2cBus* mainBoardCommonGetMainI2cBus(void);

// SERIAL LIST

/**
 * Init the list of Serial Port of the Main Board.
 */
void mainBoardCommonInitSerialList(void);

/**
 * Init the default Debug Open Serial Link.
 */
void mainBoardCommonDebugOpenSerialLink(void);

// TIMER LIST

/**
 * Init the list of timer for the Main Board.
 */
void mainBoardCommonInitTimerList(void);

// DEVICES

/**
 * Inits the array of device list and the local device.
 */
void mainBoardCommonInitDeviceListArray(void);

/**
 * Add the common devices for the Main Board (only the devices linked to the hardware).
 */
void mainBoardCommonAddDevices(RobotConfig* robotConfig);

// DRIVERS

/**
 * Inits the array of driver data dispatcher list and the local one.
 */
void mainBoardCommonInitDriverDataDispatcherList(void);

/**
 * Init the Drivers (only the local hardware supported by the Main Board).
 */
void mainBoardCommonInitDrivers(void);

// STREAM INSTRUCTION

/**
 * In the loop to handle the instruction, manages the common's part.
 */
void mainBoardCommonHandleStreamInstruction(void);

// TODO : Move it to Accelerometer Common
void mainBoardCommonHandleAccelerometer(void);

// INIT - DRIVERS

void mainBoardCommonInitCommonDrivers(void);

// INIT

void mainBoardCommonMainInit(RobotConfig* robotConfig);


#endif
