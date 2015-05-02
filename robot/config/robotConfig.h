#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/** Mask for the strategy : 0b 0000 0111 */
#define CONFIG_STRATEGY_MASK           0x0007

/** The robot does not end (useful for test) : 0b 0000 1000 */
#define CONFIG_DONT_WAIT_FOR_START     0x0008

/** The robot does not end (useful for test) : 0b 0000 1000 */
#define CONFIG_DO_NOT_END              0x0010

/** Use Sonar during the match : 0b00100000 */
// #define CONFIG_USE_SONAR_MASK          0x0020

/** Send instruction to the robot to use test : 0b 0001 0000 */
#define CONFIG_ROLLING_TEST_MASK       0x0020

// 0b 0100 0000
#define CONFIG_DONT_USE_BEACON_MASK    0x0040

/** Indicates we have the color green if set. */
// 0b1000 0000
#define CONFIG_COLOR_GREEN_MASK         0x0080

/** Speed to low. */
// 0b 0001 0000 0000
#define CONFIG_SPEED_LOW_MASK          0x0100

/** Speed to very Low. */
// 0b 0010 0000 0000
#define CONFIG_SPEED_VERY_LOW_MASK     0x0200

/** Speed to ultra very Low. */
// 0b 0100 0000 0000
#define CONFIG_SPEED_ULTRA_LOW_MASK    0x0400

/** Address of the first PCF8574 for the configuration. */
#define PCF8574_LOW_BYTE_CONFIG_ADDRESS 1

/** Address of the second PCF8574 for the configuration. */
#define PCF8574_HIGH_BYTE_CONFIG_ADDRESS 0

/** The count of bits managed handled by the device. */
#define CONFIG_BIT_COUNT 14



// forward declaration
struct RobotConfig;
typedef struct RobotConfig RobotConfig;

/**
 * Read a value from the switch configuration.
 * @return value the value to store
 */
typedef signed int robotConfigReadIntFunction(RobotConfig* robotConfig );

/**
 * Defines the contract for switch robot configuration.
 */
struct RobotConfig {
    /** The function which must be used to read the robot configuration */
    robotConfigReadIntFunction* robotConfigReadInt;
};

// GLOBAL FUNCTIONS - NON SPECIFIC

/**
 * Init an robotconfig object with all basic Functions.
 * @param robotConfigReadIntFunction the pointer on the real function which read an int.
 */
void initRobotConfig(RobotConfig* robotConfig,
                robotConfigReadIntFunction* robotConfigReadInt);


#endif
