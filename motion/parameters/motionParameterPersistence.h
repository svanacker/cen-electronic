#ifndef MOTION_PARAMETER_PERSISTENCE_H
#define MOTION_PARAMETER_PERSISTENCE_H

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"

// Forward / Backward
// 768 mm / s^2
#define DEFAULT_FORWARD_ACCELERATION             896.0f
// 1024 mm / s
#define DEFAULT_FORWARD_SPEED                    1024.0f

// Default Rotation
#define DEFAULT_ROTATION_ACCELERATION            768.0f
#define DEFAULT_ROTATION_SPEED                   768.0f

// One Wheel
#define DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION  512.0f
#define DEFAULT_ROTATION_ONE_WHEEL_SPEED         512.0f

// Maintain Position
#define DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION  16.0f
#define DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED         16.0f

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


