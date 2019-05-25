
#ifndef MAIN_BOARD_PC_H
#define MAIN_BOARD_PC_H

#include <stdbool.h>

#define MAIN_BOARD_PC_NAME    "mainBoardPc"
#define MAIN_BOARD_PC_ROBOT_MANAGER   "robotManager"

// LOGS

#define MAIN_BOARD_PC_LOG_HANDLER_LIST_LENGTH                    2

// Serial Emulation from PC_MAIN_BOARD
#define MAIN_BOARD_PC_SERIAL_LINK_LIST_LENGTH                    3
#define ROBOT_MANAGER_INPUT_BUFFER_LENGTH                      100
#define ROBOT_MANAGER_OUTPUT_BUFFER_LENGTH                     100 

#define MAIN_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS        1

// DISPATCHER

#define MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH                3
#define MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH 100
#define MAIN_BOARD_PC_DATA_MECA1_BOARD_DISPATCHER_BUFFER_LENGTH 100

// I2C

#define MAIN_BOARD_TO_MOTOR_BOARD_PC_PIPE_I2C_MASTER_NAME    L"\\\\.\\pipe\\mainToMotorMasterPipe"
#define MAIN_BOARD_TO_MECA1_BOARD_PC_PIPE_I2C_MASTER_NAME    L"\\\\.\\pipe\\mainToMeca1MasterPipe"

#define MAIN_BOARD_I2C_BUS_LIST_LENGTH							2
#define MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH				3

#define MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH        200
#define MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH         200

// Drivers
#define MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH              200
#define MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH             200

// Console
#define MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH               200
#define MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH              200

// Devices
#define MAIN_BOARD_PC_DEVICE_LIST_LENGTH                        30

#define MAIN_BOARD_PC_TOF_SENSOR_LIST_LENGTH                    14
#define MAIN_BOARD_PC_IO_EXPANDER_LIST_LENGTH                   2
#define MAIN_BOARD_PC_MULTIPLEXER_LIST_LENGTH                   2

// Servos
#define MAIN_BOARD_PC_SERVO_LIST_LENGTH                         21

// Timers
#define MAIN_BOARD_PC_TIMER_LIST_LENGTH                         10



/**
 * Start Point to emulate the main Board PC.
 * @param connectToRobotManagerMode if true, wait for a Pipe given by the RobotManager Program.
 */
void runMainBoardPC(bool connectToRobotManagerMode, bool singleMode);

#endif
