#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

#include <stdbool.h>

#include "../../robot/robotType.h"

#include "../../common/io/outputStream.h"

// --- 8 LOW CONFIG BITS ---

/** Mask for the strategy */
// 0b 0000 0000  0000 0111 
#define CONFIG_STRATEGY_MASK           0x0007

/** Manual Mode to reach step and target */
// 0b 0000 0000  0000 1000
#define CONFIG_STRATEGY_MANUAL_MODE    0x0008

/** The robot does wait for the start (useful for test & to keep the hook on the robot) : */
// 0b 0000 0000  0001 0000 
#define CONFIG_DONT_WAIT_FOR_START     0x0010

/** The robot does not end (useful for test) : */
// 0b 0000 0000 0010 0000
#define CONFIG_DO_NOT_END              0x0020

/** Config Used to activate more Debug . */
// 0b 0000 0000  0100 0000
#define CONFIG_DEBUG                   0x0040

/** Indicates we have the color yellow if set. */
// 0b 0000 0000  1000 0000
#define CONFIG_COLOR_YELLOW_MASK       0x0080

// --- 8 HIGH CONFIG BITS ---

// Mask to configure the speed
// 0b 0000 0111  0000 0000
#define CONFIG_SPEED_MASK              0x0700

#define CONFIG_SPEED_SHIFT_BIT_VALUE         8


// Sonar

/** Sonar distance, 0x00 = disabled */
// 0b 0001 1000  0000 0000
#define CONFIG_SONAR_MASK              0x1800

#define CONFIG_SONAR_SHIFT_BIT_VALUE       11


// LCD - BACKLIGHT

/** Config LCD. */
// 0b 0010 0000 0000 0000
#define CONFIG_LCD_MASK                0x2000

// IMPORTANT : There is only 14 bits and not 16 bits, so 0x4000 and 0x8000 does not exist !!

/** The count of bits managed handled by the device. */
#define CONFIG_BIT_COUNT                  14

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
