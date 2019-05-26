#ifndef DEVICE_CONSTANTS_H
#define DEVICE_CONSTANTS_H

/** Device header .*/
#define BATTERY_DEVICE_HEADER                      'b'

#define ACCELEROMETER_DEVICE_HEADER                'B'

#define ROBOT_CONFIG_DEVICE_HEADER                 'c'

#define CURRENT_SENSOR_DEVICE_HEADER               'C'

#define ADC_DEVICE_HEADER                          'd'

#define END_MATCH_DETECTOR_DEVICE_HEADER           'e'

// The EEPROM DEVICE HEADER

#define EEPROM_DEVICE_HEADER                       'E'

#define FILE_DEVICE_HEADER                         'F'

#define IO_DEVICE_HEADER                           'g'

#define MULTIPLEXER_HEADER                         'G'

// 'h' for Help
#define SYSTEM_DEBUG_DEVICE_HEADER                 'h'

// 'H' for HBridge
#define MD22_DEVICE_HEADER                         'H'

/** Command to debug the I2C Master. */
#define I2C_MASTER_DEBUG_DEVICE_HEADER             'I'

/** Command to debug the I2C Slave. */
#define I2C_SLAVE_DEBUG_DEVICE_HEADER              'i'

/** Command to debug the dispatchers. */
#define DATA_DISPATCHER_DEVICE_HEADER              'j'

/** Command to manipulate the clock. */
#define CLOCK_DEVICE_HEADER                        'k'

/** Command to handle the Kinematics. */
#define KINEMATICS_HEADER                          'K'

/**
 * Command header for LCD Device.
 */
#define LCD_DEVICE_HEADER                          'L'

#define LOG_DEVICE_HEADER                          'l'

/**
 * Defines the header char used to identify the motion Device (high level).
 */
#define MOTION_DEVICE_HEADER                       'M'

/**
 * Defines the header char used to identify the motor Device (low level).
 */
#define MOTOR_DEVICE_HEADER                        'm'

/**
 * Header char of Trajectory device : 'n' for 'navigation.
 */
#define TRAJECTORY_DEVICE_HEADER                   'n'

/**
 * Header char of Navigation device
 */
#define NAVIGATION_DEVICE_HEADER                   'N'

/** To set PID values */
#define PID_DEVICE_HEADER                          'p'

/** To debug PID values */
#define PID_DEBUG_DEVICE_HEADER                    'P'

/** Command to ping */
#define COMMAND_PING_DISPATCHER_INDEX              'Q'

/** Command to debug the I2C (Master or Slave). */
// TODO : Conflict !!
#define I2C_COMMON_DEBUG_DEVICE_HEADER             'Q'

/** To access to each pin of the PIC */
#define PIN_DEVICE_HEADER                          'q'

// TODO : To REMOVE
#define BEACON_RECEIVER_DEVICE_HEADER              'r'

#define RELAY_DEVICE_HEADER                        'R'

/** Header for the servo device .*/
#define SERVO_DEVICE_HEADER                        's'

/** Header for System Device. */
#define SYSTEM_DEVICE_HEADER                       'S'

// The TEMPERATURE SENSOR DEVICE HEADER

/** Header for Temperature Device. */
#define TEMPERATURE_SENSOR_DEVICE_HEADER           'T'

/** Header for Test Device. */
#define TEST_DEVICE_HEADER                         't'

/** Serial debug (U for "Uart"). */
#define SERIAL_DEBUG_DEVICE_HEADER                 'U'

/** Header for Test2 Device. */
#define TEST2_DEVICE_HEADER                        'v'

#define TIMER_DEVICE_HEADER                        'V'

#define CODERS_DEVICE_HEADER                       'w'

#define PC_DEVICE_HEADER                           'W'

#define EXTENDED_MOTION_DEVICE_HEADER			   'X'

/** To access to the game board */
#define GAME_BOARD_DEVICE_HEADER                   'y'

/** To access to the strategy (list of points, targets...) */
#define STRATEGY_DEVICE_HEADER                      'Y'

/** Reserved to clear buffer. */
#define NOT_TOO_USE_1                               'z'

/** Reserved to clear deeply the buffer. */
#define NOT_TOO_USE_2                               'Z'

/** To send the signal of start Match */
#define START_MATCH_DEVICE_HEADER                   '!'

/** Time of flight device. */
#define TOF_DEVICE_HEADER                          '['

#define COLOR_SENSOR_DEVICE_HEADER                 '*'

/** TODO */
#define ROBOT_SONAR_DETECTOR_DEVICE_HEADER         '#'

#define MOTION_SIMULATION_DEVICE_HEADER            '/' 

// 2019

#define ELEVATOR_2019_DEVICE_HEADER                '|'

#define FORK_2019_DEVICE_HEADER                    '_'

#define DISTRIBUTOR_2019_DEVICE_HEADER             'D'

#define ARM_2019_DEVICE_HEADER                     'A'

#define GOLDENIUM_2019_DEVICE_HEADER               'o'

#define ELECTRON_LAUNCHER_2019_DEVICE_HEADER       '.'

#endif
