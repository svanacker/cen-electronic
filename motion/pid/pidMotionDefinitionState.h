#ifndef PID_MOTION_DEFINITION_STATE_H
#define PID_MOTION_DEFINITION_STATE_H

#include "../../common/io/outputStream.h"

/**
 * Store the state of the motion
 */
enum PidMotionDefinitionState {
    /**
     * The type at the initial state
     */
    PID_MOTION_DEFINITION_STATE_UNDEFINED,
    /**
     * The main information have been set (like ProfileType, main information...)
     * but we need to compute later current values (end Motion Detection ...)
     */
    PID_MOTION_DEFINITION_STATE_SET,
    /**
     * The motion definition is active and is the current motion
     */
    PID_MOTION_DEFINITION_STATE_ACTIVE,
    /**
     * The motion definition is ended => We must go to the next definition
     */
    PID_MOTION_DEFINITION_STATE_ENDED
};

/**
 * Append in the stream a string representation of the enum PidMotionDefinitionState.
 * @return how many chars were written
 */
unsigned int appendMotionDefinitionStateString(OutputStream* outputStream, enum PidMotionDefinitionState state);

/**
 * Append a column value with the string representation of the enum PidMotionDefinitionState.
 */
unsigned int addPidMotionDefinitionStateTableData(OutputStream* outputStream, enum PidMotionDefinitionState state, int columnSize);

#endif