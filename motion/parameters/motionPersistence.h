#ifndef MOTION_PERSISTENCE_H
#define MOTION_PERSISTENCE_H

#include <stdbool.h>

#include "../../common/eeprom/eeprom.h"

// Forward / Backward
#define DEFAULT_FORWARD_ACCELERATION             0x10
#define DEFAULT_FORWARD_SPEED                     0x30

// Default Rotation
#define DEFAULT_ROTATION_ACCELERATION             0x08
#define DEFAULT_ROTATION_SPEED                     0x40

// One Wheel
#define DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION 0x08
#define DEFAULT_ROTATION_ONE_WHEEL_SPEED         0x10

// Maintain Position
#define DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION 0x04
#define DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED         0x02

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


