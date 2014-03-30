#ifndef PID_TEST_H
#define PID_TEST_H

#include "pid.h"

#include "../../common/commons.h"

// Equals Function for all PID structures

/**
* Returns TRUE if the two "Pid" structures have the same value for each field, FALSE else.
*/
bool pidEquals(Pid* pid1, Pid* pid2);

/**
* Returns TRUE if the two "MotionError" structures have the same value for each field, FALSE else.
*/
bool motionErrorEquals(MotionError* motionError1, MotionError* motionError2);

/**
* Returns TRUE if the two "MotionEndInfo" structures have the same value for each field.
*/
bool motionEndInfoEquals(MotionEndInfo* motionEndInfo1, MotionEndInfo* motionEndInfo2);

/**
* Returns TRUE if the two "Motion" structures have the same value for each field.
*/
bool motionEquals(Motion* motion1, Motion* motion2);

/**
* Returns TRUE if the two "MotionInstruction" structures have the same value for each field.
*/
bool motionInstructionEquals(MotionInstruction* motionInstruction1, MotionInstruction* motionInstruction2);

#endif
