#ifndef ROBOT_CONSTANTS_H
#define ROBOT_CONSTANTS_H


// CONSTANT ON ROBOT

/** Length of the left wheels when there is one pulse on coders. */
// #define WHEEL_LENGTH_LEFT 0.1145f // value 13/05/2010
// #define WHEEL_LENGTH_LEFT 0.1169f avant correction
// #define WHEEL_LENGTH_LEFT 0.1168f

/** Average wheel length in mm for 1 impulsion. */
#define WHEEL_AVERAGE_LENGTH		0.011685f

#define WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED		7.0f
#define WHEEL_PULSE_BY_ROTATION						20000.0f
// Parenthesis are very important to avoid problems when this define is used by other define
#define WHEEL_PULSE_BY_SECONDS_AT_FULL_SPEED		(WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED * WHEEL_PULSE_BY_ROTATION)

// To compensate difference between WHEELS
#define WHEEL_DELTA_LENGTH			0.0f			


/** Length of the right wheels when there is one pulse on coders. */
// #define WHEEL_LENGTH_RIGHT 0.1145f // value 13/05/2010
// #define WHEEL_LENGTH_RIGHT 0.1169f // avant correction
// Codeurs 500 impulsions : #define WHEEL_LENGTH_RIGHT 0.1168f
#define WHEEL_LENGTH_LEFT 			WHEEL_AVERAGE_LENGTH + WHEEL_DELTA_LENGTH
#define WHEEL_LENGTH_RIGHT 			WHEEL_AVERAGE_LENGTH - WHEEL_DELTA_LENGTH

/** Default wheels distance. */
#define WHEELS_DISTANCE 226.70f

/** Distance between the center of the robot and a wheel. */
#define WHEELS_DISTANCE_FROM_CENTER WHEELS_DISTANCE / 2

#endif
