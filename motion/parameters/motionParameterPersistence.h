#ifndef MOTION_PARAMETER_PERSISTENCE_H
#define MOTION_PARAMETER_PERSISTENCE_H

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"

// Forward / Backward
// 768 mm / s^2
#define DEFAULT_FORWARD_ACCELERATION             0X0300
// 1024 mm / s
#define DEFAULT_FORWARD_SPEED                    0x0400

// Default Rotation
#define DEFAULT_ROTATION_ACCELERATION            0x0100
#define DEFAULT_ROTATION_SPEED                   0x0100

// One Wheel
#define DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION  0x0200
#define DEFAULT_ROTATION_ONE_WHEEL_SPEED         0x0200

// Maintain Position
#define DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION  0x0010
#define DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED         0x0010

/**
 * Load the motion parameters from the EEPROM :
 * (for default speed / acceleration)
 */
void loadMotionParameters(Eeprom* motionEeprom, bool loadDefaultValues);

/**
 * Load the motion parameters from the EEPROM :
 * (for default speed / acceleration)
 */
void saveMotionParameters(Eeprom* motionEeprom);

#endif


