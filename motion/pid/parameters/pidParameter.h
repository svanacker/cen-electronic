#ifndef PID_PARAMETER_H
#define PID_PARAMETER_H

#include <stdbool.h>

/**
 * Defines the structure which is used to store PID parameters.
 */
typedef struct PidParameter {
    /** The proportional term */
    float p;
    /** The integral term */
    float i;
    /** The derivative term */
    float d;
    /** The maximal term of integral */
    float maxIntegral;
    /** Enable or not the pid. */
    bool enabled;
} PidParameter;

#endif