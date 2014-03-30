#ifndef MOTION_PERSISTENCE_H
#define MOTION_PERSISTENCE_H

// First 2 octets are reserved
#define EEPROM_MOTION_START_INDEX	100


// Forward / Backward
#define DEFAULT_FORWARD_ACCELERATION 			0x20
#define DEFAULT_FORWARD_SPEED 					0x60

// Default Rotation
#define DEFAULT_ROTATION_ACCELERATION 			0x20
#define DEFAULT_ROTATION_SPEED 					0x60

// One Wheel
#define DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION 0x08
#define DEFAULT_ROTATION_ONE_WHEEL_SPEED 		0x10

// Maintain Position
#define DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION 0x04
#define DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED 		0x02

/**
 * Load the motion parameters from the EEPROM :
 * (for default speed / acceleration)
 */
void loadMotionParameters();

/**
 * Load the motion parameters from the EEPROM :
 * (for default speed / acceleration)
 */
void saveMotionParameters();

#endif


