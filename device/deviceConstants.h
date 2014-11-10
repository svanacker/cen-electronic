#ifndef DEVICE_CONSTANTS_H
#define DEVICE_CONSTANTS_H

// TODO : Change !!!
#define CLOCK_DEVICE_HEADER     				'C'


/** Device header .*/
#define ROBOT_CONFIG_DEVICE_HEADER      		'c'

#define ADC_DEVICE_HEADER            			'd'

#define END_MATCH_DETECTOR_DEVICE_HEADER        'e'

// The EEPROM DEVICE HEADER

#define EEPROM_DEVICE_HEADER     				'E'

#define AIR_CONDITIONING_DEVICE_HEADER         	'g'

/** Command to debug the I2C Master. */
#define I2C_MASTER_DEBUG_DEVICE_HEADER        	'I'

#define ROBOT_INFRARED_DETECTOR_DEVICE_HEADER    'I'

/** Command to debug the I2C Slave. */
#define I2C_SLAVE_DEBUG_DEVICE_HEADER       	'i'

/** Laser Beacon Device Header. */
#define LASER_BEACON_DEVICE_HEADER            	'l'

/**
 * Command header for LCD Device.
 */
#define LCD_DEVICE_HEADER    					'L'

/**
 * Defines the header char used to identify the motion Device (high level).
 */
#define MOTION_DEVICE_HEADER        			'M'

/**
 * Defines the header char used to identify the motor Device (low level).
 */
#define MOTOR_DEVICE_HEADER     				'm'


/**
 * Header char of Trajectory device : 'n' for 'navigation.
 */
#define TRAJECTORY_DEVICE_HEADER        		'n'

#define PID_DEVICE_HEADER 						'p'

#define PIN_DEVICE_HEADER						'P'

#define BEACON_RECEIVER_DEVICE_HEADER           'r'

#define RELAY_DEVICE_HEADER						'R'

/** Header for the servo device .*/
#define SERVO_DEVICE_HEADER                     's'

/** Header for System Device. */
#define SYSTEM_DEVICE_HEADER    				'S'

// The TEMPERATURE SENSOR DEVICE HEADER

/** Header for Temperature Device. */
#define TEMPERATURE_SENSOR_DEVICE_HEADER     	'T'

/** Header for Test Device. */
#define DEVICE_TEST_HEADER 						't'

/** Common Beacon device header. */
#define COMMON_BEACON_DEVICE_HEADER            	'U'

#define CODERS_DEVICE_HEADER                    'w'

#define STRATEGY_DEVICE_HEADER                  'Y'

#define START_MATCH_DETECTOR_DEVICE_HEADER      '!'

#define SONAR_DEVICE_HEADER                		'<'

#define SYSTEM_DEBUG_DEVICE_HEADER        		'*'

#define ROBOT_SONAR_DETECTOR_DEVICE_HEADER  	'#'

#define	PLIERS_DEVICE_2011_HEADER				'_'

#define ARM_DEVICE_2012_HEADER					'|'

#endif
