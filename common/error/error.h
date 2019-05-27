#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

/**
 * Main Method to write Error.
 * Avoid using long strings which takes program memory.
 * @param errorCode the error Code
 */
void writeError(int errorCode);

/**
 * Returns the last error.
 * @returns the last error code, 0x0000 if there is no error
 */
int getLastError();

/**
 * Returns if there is an error.
 * @return true if there is an error (lastError > 0), false else.
 */
bool isThereAnyError();

/**
 * Clears the last error, to avoid that we take into consideration an old error.
 */
void clearLastError();

// List of error Code

#define ERROR_NONE                                                        0x0000

#define ILLEGAL_ARGUMENT_EXCEPTION                                        0x0001
#define LIMIT_ARGUMENT_MUST_BE_POSITIVE                                   0x0010

// IO

#define IO_BUFFER_EMPTY                                                   0x0100
#define IO_BUFFER_FULL                                                    0x0101
#define IO_BUFFER_NULL                                                    0x0102
#define IO_BUFFER_NOT_ENOUGH_DATA                                         0x0103
#define IO_BUFFER_ILLEGAL_INDEX_ACCESS                                    0x0104

#define PRINT_WRITER_NOT_HEX_VALUE                                        0x0109

#define IO_PIN_INDEX_ERROR                                                0x0110

#define IO_READER_READ_FILTERED_CHAR                                      0x0120
#define IO_READER_CHECK_CHAR_PROBLEM                                      0x0130
#define IO_READER_NOT_BOOL_VALUE                                          0x0131

#define COMPOSITE_OUTPUT_STREAM_NOT_INITIALIZED                           0x0170
#define COMPOSITE_OUTPUT_STREAM_ILLEGAL_INDEX                             0x0171
#define COMPOSITE_OUTPUT_STREAM_FULL                                      0x0172

// LOG
#define LOG_LIST_NOT_INITIALIZED                                          0x0180
#define LOG_LIST_TOO_MUCH_LOG_HANDLERS                                    0x0181
#define LOG_LIST_OUT_OF_BOUNDS                                            0x0182

// SERIAL
#define SERIAL_LINK_LIST_NOT_INITIALIZED                                  0x0190
#define SERIAL_LINK_LIST_TOO_MUCH_LINKS                                   0x0191
#define SERIAL_LINK_LIST_OUT_OF_BOUNDS                                    0x0192

// SERVO
#define SERVO_LIST_NOT_INITIALIZED                                        0x01A0
#define SERVO_LIST_TOO_MUCH_SERVOS                                        0x01A1
#define SERVO_LIST_OUT_OF_BOUNDS                                          0x01A2
#define SERVO_LIST_SERVO_NULL                                             0x01A3
#define SERVO_LIST_SERVO_NOT_INITIALIZED                                  0x01A4
#define SERVO_NULL                                                        0x01A5
#define SERVO_LIST_NULL                                                   0x01A6
#define SERVO_MAX_SPEED_UNDER_LOAD_UNDEFINED                              0x01A7

// TIMER
#define TIMERS_LIST_NOT_INITIALIZED                                       0x0200
#define TOO_MUCH_TIMERS                                                   0x0201
#define TIMERS_LIST_ILLEGAL_INDEX                                         0x0202
#define TIMER_NULL					                                      0x0203
#define TIMERS_LIST_NULL                                                  0x0204
#define TIMER_DELAY_ALREADY_INITIALIZED                                   0x0205
#define TIMER_DELAY_NOT_FOUND                                             0x0206
#define TIMER_DELAY_DISABLED                                              0x0207
#define TIMER_MARK_WHEREAS_DISABLED                                       0x0209
#define TIMER_OBJECT_NULL                                                 0x0210

// EEPROM
#define EEPROM_NULL                                                       0x0280
#define EEPROM_NOT_INITIALIZED                                            0x0281
#define EEPROM_OUT_OF_BOUNDS                                              0x0282
#define EEPROM_FILE_ILLEGAL_CALL                                          0x0283
#define EEPROM_NEGATIVE_FLOAT_NOT_ALLOWED                                 0x0284

// CLOCK
#define CLOCK_NULL                                                        0x0290
#define CLOCK_NOT_INITIALIZED                                             0x0291

// BATTERY
#define BATTERY_NULL                                                      0x02A0
#define BATTERY_NOT_INITIALIZED                                           0x02A1

// TEMPERATURE
#define TEMPERATURE_NULL                                                  0x02B0

// CURRENT
#define CURRENT_NULL                                                      0x02C0

// BIT LIST
#define BIT_LIST_ARRAY_OUT_OF_BOUNDS                                      0x0300

// PWM
#define PWM_NOT_AVAILABLE                                                 0x0400
#define PWM_VALUE_MUST_BE_POSITIVE                                        0x0401

// RELAY
#define RELAY_NULL                                                        0x0480

// COLOR
#define COLOR_SENSOR_NULL                                                 0x04A0

// ACCELEROMETER
#define ACCELEROMETER_SENSOR_SETUP_PROBLEM                                0x04B0

// OTHERS COMMON ERRORS
#define UNIMPLETEMENTED_EXCEPTION                                         0x0500

// ADC
#define ADC_BAD_INDEX                                                     0x0600

// I2C 

#define I2C_MASTER_ALREADY_INITIALIZED                                    0x1000
#define I2C_SLAVE_ALREADY_INITIALIZED                                     0x1001
#define I2C_BUS_PORT_NOT_DEFINED                                          0x1002
// -> I2C  : Bus
#define I2C_BUS_NULL                                                      0x1003
#define I2C_BUS_TYPE_NOT_DEFINED                                          0x1004
#define I2C_BUS_CONNECTION_NULL                                           0x1005
#define I2C_BUS_CONNECTION_OBJECT_NULL                                    0x1006
#define I2C_BUS_CONNECTION_MASTER_TO_SLAVE_PIPE_NULL                      0x1007
#define I2C_BUS_CONNECTION_SLAVE_TO_MASTER_PIPE_NULL                      0x1008

// -> I2C : BusList
#define I2C_BUS_LIST_NOT_INITIALIZED	                                  0x1010
#define TOO_MUCH_I2C_BUS				                                  0x1011
#define I2C_BUS_LIST_ILLEGAL_INDEX                                        0x1012
// -> I2C : BusConnectionList
#define I2C_BUS_CONNECTION_LIST_NOT_INITIALIZED	                          0x1020
#define TOO_MUCH_I2C_BUS_CONNECTION				                          0x1021
#define I2C_BUS_CONNECTION_LIST_ILLEGAL_INDEX                             0x1022

#define I2C_START_I2C_ERROR                                               0x1040

#define I2C_TOO_MUCH_LOOP_MASTER_WAIT_SEND_I2C_ERROR                      0x1050
#define I2C_TOO_MUCH_LOOP_MASTER_READ_I2C_ERROR                           0x1051
#define I2C_TOO_MUCH_LOOP_WAIT_I2C_ERROR                                  0x1052

// DEVICE

#define TOO_MUCH_DEVICES                                                  0x2000
#define NO_DEVICE_DESC_FOUND_FOR                                          0x2001
#define DEVICES_LIST_NOT_INITIALIZED                                      0x2002
#define DEVICE_ILLEGAL_INDEX                                              0x2003
#define DEVICE_INTERFACE_PROBLEM                                          0x2004

#define DEVICE_TEST_INTENSIVE_CHECK_PROBLEM                               0x2010

// -> Dispatcher
#define NO_DISPATCHER_FOUND                                               0x2100
#define NO_DISPATCHER_INPUT_STREAM                                        0x2101
#define NO_DISPATCHER_INPUT_BUFFER                                        0x2102
#define DEVICE_NOT_FOUND                                                  0x2103


#define DISPATCHER_NO_CALLBACK_FOR_NOTIFICATION                           0x2110
#define TOO_MUCH_DRIVER_DATA_DISPATCHER                                   0x2111
#define DISPATCHERS_LIST_NOT_INITIALIZED                                  0x2120
#define DISPATCHERS_LIST_ILLEGAL_INDEX                                    0x2121
#define DISPATCHER_PING_MUST_BE_HANDLE_IN_DRIVER_STREAM_LISTENER          0x2122
#define DISPATCHER_LINK_ERROR                                             0x2123

#define NOTIFICATION_BAD_DEVICE                                           0x2130
#define NOTIFICATION_BAD_DEVICE_COMMAND_HANDLER_NOT_HANDLE                0x2131

// DRIVER

#define DRIVER_STREAM_LISTENER_INPUT_BUFFER_NULL                          0x2200
#define DRIVER_STREAM_LISTENER_OUTPUT_BUFFER_NULL                         0x2201
#define DRIVER_INPUT_STREAM_NULL                                          0x2210

#define TOO_MUCH_DRIVERS                                                  0x2300

#define TOF_SENSOR_LIST_NOT_INITIALIZED                                   0x2400
#define TOF_SENSOR_LIST_ILLEGAL_INDEX                                     0x2401
#define TOO_MUCH_TOF_SENSOR				                                  0x2402
#define TOF_SENSOR_NULL                                                   0x2403
#define TOF_SENSOR_OBJECT_NULL                                            0x2404
#define TOF_SENSOR_LIST_NULL                                              0x2405

#define IO_EXPANDER_LIST_NOT_INITIALIZED                                  0x2500
#define IO_EXPANDER_LIST_ILLEGAL_INDEX                                    0x2501
#define IO_EXPANDER_NULL                                                  0x2502

#define MULTIPLEXER_LIST_NOT_INITIALIZED                                  0x2600
#define MULTIPLEXER_LIST_ILLEGAL_INDEX                                    0x2601
#define MULTIPLEXER_NULL                                                  0x2602

// PID

#define PID_INDEX_INCORRECT                                               0x3000
#define PID_PARAMETERS_PERSISTENCE_NO_EEPROM                              0x3100
#define PID_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED                 0x3101
#define PID_MOTION_NULL                                                   0x3102
#define PID_MOTION_EMPTY                                                  0x3103
#define PID_MOTION_NOT_ENOUGH_DATA                                        0x3104
#define PID_MOTION_FULL                                                   0x3105
#define PID_TYPE_UNKNOWN_ENUM                                             0x3106

// MOTION

#define MOTION_DEFINITION_LIST_FULL			                              0x3700
#define MOTION_DEFINITION_LIST_OUT_OF_BOUNDS                              0x3701
#define MOTION_DEFINITION_NULL                                            0x3702
#define MOTION_DEFINITION_NO_CURRENT_DEFINITION                           0x3703

#define MOTION_BSPLINE_LIST_NULL                                          0x3800
#define MOTION_BSPLINE_LIST_NOT_INITIALIZED                               0x3801
#define MOTION_BSPLINE_LIST_OUT_OF_BOUNDS                                 0x3802
#define MOTION_BSPLINE_LIST_FULL                                          0x3803
#define MOTION_BSPLINE_LIST_EMPTY                                         0x3804

#define MOTION_BSPLINE_DISTANCE_MUST_BE_POSITIVE                          0x3880

#define MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM                           0x3900
#define MOTION_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED              0x3901

#define MOTION_END_DETECTION_PARAMETERS_PERSISTENCE_NO_EEPROM             0x3902
#define MOTION_END_DETECTION_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED 0x3903


// Zigbee
#define TOO_MUCH_JENNIC_EVENT                                             0x4000

#define CODERS_TIMER_NOT_FOUND                                            0x4100

// Navigation
#define TOO_MUCH_GAME_BOARD_ELEMENTS                                      0x5000
#define TOO_MUCH_STRATEGIES                                               0x5010
#define STRATEGY_NOT_DEFINED                                              0x5011
#define TOO_MUCH_STRATEGY_ITEMS                                           0x5020
#define TOO_MUCH_TARGETS                                                  0x5030
#define TARGET_IS_NULL                                                    0x5031
#define GAME_STRATEGY_CONTEXT_NULL                                        0x5032

#define TOO_MUCH_LOCATIONS                                                0x5040
#define LOCATION_LIST_NULL                                                0x5041
#define LOCATION_LIST_NOT_INITIALIZED                                     0x5042
#define LOCATION_LIST_INDEX_OUT_OF_BOUNDS                                 0x5043
#define LOCATION_SOURCE_TARGET_EQUAL                                      0x5044
#define LOCATION_DOES_NOT_EXIST                                           0x5045
#define LOCATION_NULL                                                     0x5046
#define LOCATION_START_NULL                                               0x5047
#define LOCATION_END_NULL                                                 0x5048

#define TOO_MUCH_PATHS                                                    0x5050
#define PATH_LIST_NULL                                                    0x5051
#define PATH_LIST_NOT_INITIALIZED                                         0x5052
#define PATH_LIST_INDEX_OUT_OF_BOUNDS                                     0x5053
#define PATH_NULL                                                         0x5054
#define PATH_NOT_FOUND                                                    0x5055

#define TOO_MUCH_ACTION                                                   0x5060
#define TOO_MUCH_TARGET_ACTION                                            0x5070
#define TOO_MUCH_TARGET_ACTION_ITEM                                       0x5080
#define TOO_MUCH_TARGET_ACTION_ITEM_FUNCTION_NULL                         0x5081

#define TOO_MUCH_OUTGOING_PATHS                                           0x5090
#define OUTGOING_PATH_LIST_NULL                                           0x5091
#define OUTGOING_PATH_LIST_NOT_INITIALIZED                                0x5092
#define OUTGOING_PATH_LIST_INDEX_OUT_OF_BOUNDS                            0x5093
#define OUTGOING_PATH_NULL                                                0x5094

#define WRONG_COLOR                                                       0x5100

// ROBOT
#define ROBOT_KINEMATICS_NO_EEPROM                                        0x6000
#define ROBOT_KINEMATICS_EEPROM_NOT_INITIALIZED                           0x6001

#define ROBOT_TYPE_UNKNOWN_ERROR                                          0x6010

#define ROBOT_GAMEBOARD_ELEMENT_LIST_NULL                                 0x6100
#define ROBOT_GAMEBOARD_ELEMENT_LIST_NOT_INITIALIZED                      0x6101
#define ROBOT_GAMEBOARD_TOO_MUCH_ELEMENTS                                 0x6102           
#define ROBOT_GAMEBOARD_ELEMENT_LIST_OUT_OF_BOUNDS                        0x6103

#define ROBOT_START_MATCH_DETECTOR_PC_FILE_LENGTH_ERROR                   0x6200
#define ROBOT_START_MATCH_DETECTOR_PC_NULL                                0x6201
#define ROBOT_END_MATCH_NULL                                              0x6202

#define ROBOT_CONFIG_MUST_BE_0_OR_1_CHAR_ERROR                            0x6300
#define ROBOT_CONFIG_MUST_BE_SPACE_CHAR_ERROR                             0x6301
#define ROBOT_CONFIG_FILE_LENGTH_ERROR                                    0x6302
#define ROBOT_CONFIG_ERROR                                                0x6303

#define ROBOT_POSITION_NULL                                               0x6400


// PC
#define PC_FILE_NOT_FOUND                                                 0x7000

// SPECIFIC 2019
#define ELECTRON_LAUNCHER_2019_NULL                                       0x7100


#endif
