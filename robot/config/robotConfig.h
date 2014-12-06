#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/** Mask for the strategy : 0b00000111 */
#define CONFIG_STRATEGY_MASK           0x0007

/** The robot does not end (useful for test) : 0b00001000 */
#define CONFIG_DO_NOT_END              0x0008

/** Send instruction to the robot to use test : 0b00010000 */
#define CONFIG_ROLLING_TEST_MASK       0x0010

/** Use Sonar during the match : 0b00100000 */
#define CONFIG_USE_SONAR_MASK          0x0020

// 0b01000000
#define CONFIG_USE_BALISE_MASK         0x0040

/** Indicates we have the color blue if set. */
// 0b10000000
#define CONFIG_COLOR_BLUE_MASK         0x0080

/** Speed to low. */
// 0b100000000
#define CONFIG_SPEED_LOW_MASK          0x0100

/** Speed to very Low. */
// 0b1000000000
#define CONFIG_SPEED_VERY_LOW_MASK     0x0200

/** Speed to ultra very Low. */
// 0b10000000000
#define CONFIG_SPEED_ULTRA_LOW_MASK    0x0400

/** Address of the first PCF8574 for the configuration. */
#define PCF8574_LOW_BYTE_CONFIG_ADDRESS 1

/** Address of the second PCF8574 for the configuration. */
#define PCF8574_HIGH_BYTE_CONFIG_ADDRESS 0

/** The count of bits managed handled by the device. */
#define CONFIG_BIT_COUNT 14

#endif
