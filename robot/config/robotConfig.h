#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/** Mask for the strategy */
#define CONFIG_STRATEGY_MASK           0b00000111

/** The robot does not end (useful for test). */
#define CONFIG_DO_NOT_END              0b00001000

/** Send instruction to the robot to use test */
#define CONFIG_ROLLING_TEST_MASK         0b00010000

/** Use Sonar during the match. */
#define CONFIG_USE_SONAR_MASK          0b00100000

#define CONFIG_USE_BALISE_MASK         0b01000000

/** Indicates we have the color blue if set. */
#define CONFIG_COLOR_BLUE_MASK         0b10000000

/** Speed to low. */
#define CONFIG_SPEED_LOW_MASK            0b100000000

/** Speed to very Low. */
#define CONFIG_SPEED_VERY_LOW_MASK   0b1000000000

/** Speed to ultra very Low. */
#define CONFIG_SPEED_ULTRA_LOW_MASK 0b10000000000

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
typedef void robotConfigReadIntFunction(RobotConfig* robotConfig );

/**
 * Defines the contract for an eeprom.
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
