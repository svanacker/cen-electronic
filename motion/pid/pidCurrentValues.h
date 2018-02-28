#ifndef PID_CURRENT_VALUES_H
#define PID_CURRENT_VALUES_H

/**
 * Defines a struct which stores current and old Values of position, and voltage supplied to the motor.
 */
typedef struct PidCurrentValues {
    /** Normal position. */
    float normalPosition;
    /** current position values. */
    float position;
    /** Old Position values. */
    float oldPosition;
    /** Speed. */
    float currentSpeed;
    /** U (voltage) values. */
    float u;
} PidCurrentValues;

/**
 * Clear all values of the current structure.
 * @param pidCurrentValues
 */
void clearPidCurrentValues(PidCurrentValues* pidCurrentValues);

#endif
