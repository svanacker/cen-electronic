#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/** Mask for the strategy */
#define CONFIG_STRATEGY_MASK    	0b00000111

/** The robot does not end (useful for test). */
#define CONFIG_DO_NOT_END       	0b00001000

/** Send instruction to the robot to use test */
#define CONFIG_ROLLING_TEST_MASK  	0b00010000

/** Use Sonar during the match. */
#define CONFIG_USE_SONAR_MASK   	0b00100000

/** Definition if we are in debug mode of the mode to loop after each devices and sending information to the lcd. */
#define CONFIG_DEBUG_MASK       	0b01000000

/** Indicates we have the color blue if set. */
#define CONFIG_COLOR_BLUE_MASK  	0b10000000

/** Speed to low. */
#define CONFIG_SPEED_LOW_MASK  		0b100000000

/** Speed to very Low. */
#define CONFIG_SPEED_VERY_LOW_MASK 0b1000000000

/** Address of the first PCF8574 for the configuration. */
#define PCF8574_LOW_BYTE_CONFIG_ADDRESS 1

/** Address of the second PCF8574 for the configuration. */
#define PCF8574_HIGH_BYTE_CONFIG_ADDRESS 0

/** The count of bits managed handled by the device. */
#define CONFIG_BIT_COUNT 14

#endif
