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


/**
* Sets the PID at the specified index.
* @param pidIndex the index of the PID to set (between 0 and PID_COUNT)
* @param p the P parameter
* @param i the I parameter
* @param d the D parameter
* @param maxIntegral the bounds of the I term
*/
void setPidParameter(int pidIndex, float p, float i, float d, float maxIntegral);

#endif