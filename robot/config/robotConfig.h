#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

/**
 * Define a type of color which was detected.
 */
enum RobotType {
    // The big robot authorized for Eurobot
    ROBOT_TYPE_BIG,
    // The Small robot authorized for Eurobot
    ROBOT_TYPE_SMALL
};

// --- 8 LOW CONFIG BITS ---

/** Mask for the strategy : 0b 0000 0111 */
#define CONFIG_STRATEGY_MASK           0x0007

/** The robot does wait for the start (useful for test & to keep the hook on the robot) : 0b 0000 1000 */
#define CONFIG_DONT_WAIT_FOR_START     0x0008

/** The robot does not end (useful for test) : 0b 0000 1000 */
#define CONFIG_DO_NOT_END              0x0010

/** Use Sonar with very long detection distance during the match : 0b00100000 */
#define CONFIG_SONAR_FAR_MASK          0x0020

/** Use sonar with near detection distance : 0b0100 0000*/
#define CONFIG_SONAR_NEAR_MASK         0x0040

/** Indicates we have the color yellow if set. */
// 0b 1000 0000
#define CONFIG_COLOR_YELLOW_MASK       0x0080

// --- 8 HIGH CONFIG BITS ---

/** Speed to low. */
// 0b 0000 0001 0000 0000
#define CONFIG_SPEED_LOW_MASK          0x0100

/** Speed to very Low. */
// 0b 0000 0010 0000 0000
#define CONFIG_SPEED_VERY_LOW_MASK     0x0200

/** Speed to ultra very Low. */
// 0b 0000 0100 0000 0000
#define CONFIG_SPEED_ULTRA_LOW_MASK    0x0400

/** Config Undefined 1. */
// 0b 0000 1000 0000 0000
#define CONFIG_UNDEFINED_1_MASK        0x0800

/** Config Used to activate more Debug . */
// 0b 0001 0000 0000 0000
#define CONFIG_DEBUG                   0x1000

// LCD - BACKLIGHT

/** Config LCD. */
// 0b 0010 0000 0000 0000
#define CONFIG_LCD_MASK                0x2000

// IMPORTANT : There is only 14 bits and not 16 bits, so 0x4000 and 0x8000 does not exist !!

/** The count of bits managed handled by the device. */
#define CONFIG_BIT_COUNT 14

// forward declaration
struct RobotConfig;
typedef struct RobotConfig RobotConfig;

/**
 * Read a value from the switch configuration.
 * @return value the value to store
 */
typedef unsigned int robotConfigReadIntFunction(RobotConfig* robotConfig);

/**
 * Write a fake value to replace the switch configuration.
 */
typedef void robotConfigWriteIntFunction(RobotConfig* robotConfig, unsigned int robotConfigValue);

/**
 * Defines the contract for switch robot configuration.
 */
struct RobotConfig {
    // The type of the robot
    enum RobotType robotType;
    /** The function which must be used to read the robot configuration */
    robotConfigReadIntFunction* robotConfigReadInt;
    /** The function which can be used if we change the config. */
    robotConfigWriteIntFunction* robotConfigWriteInt;
};

// GLOBAL FUNCTIONS - NON SPECIFIC

/**
 * Init an robotConfig object with all basic Functions.
 * @param robotConfigReadIntFunction the pointer on the real function which read an int.
 */
void initRobotConfig(RobotConfig* robotConfig,
                     enum RobotType robotType, 
                     robotConfigReadIntFunction* robotConfigReadInt,
                     robotConfigWriteIntFunction* robotConfigWriteInt);

/**
* Reads the raw config Value.
* You must call refreshConfig for the first time
*/
unsigned int getConfigValue(RobotConfig* robotConfig);

/**
* Returns if the specified configMask is set or not
*/
bool isConfigSet(RobotConfig* robotConfig, unsigned int configMask);

bool isSonarActivated(RobotConfig* robotConfig);

#endif
