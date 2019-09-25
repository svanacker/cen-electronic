#include "pid.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"

bool pidEquals(Pid* pid1, Pid* pid2) {
    bool result;
    result &= floatEquals(pid1->p, pid2->p);
    result &= floatEquals(pid1->i, pid2->i);
    result &= floatEquals(pid1->d, pid2->d);
    result &= floatEquals(pid1->maxIntegral, pid2->maxIntegral);
    return result;
}

bool motionErrorEquals(MotionError* motionError1, MotionError* motionError2) {
    bool result;
    result &= floatEquals(motionError1->previousError, motionError2->previousError);
    result &= floatEquals(motionError1->error, motionError2->error);
    result &= floatEquals(motionError1->derivativeError, motionError2->derivativeError);
    result &= floatEquals(motionError1->integralError, motionError2->integralError);
    return result;
}

/*
bool motionEndInfoEquals(MotionEndInfo* motionEndInfo1, MotionEndInfo* motionEndInfo2) {
    bool result;
    result &= floatEquals(motionEndInfo1->maxTime, motionEndInfo2->maxTime);
    result &= floatEquals(motionEndInfo1->absDeltaPositionIntegral, motionEndInfo2->absDeltaPositionIntegral);
    result &= floatEquals(motionEndInfo1->uIntegral, motionEndInfo2->uIntegral);
    return result;
}
*/

bool motionEquals(Motion* motion1, Motion* motion2) {
    bool result;
    result &= floatEquals(motion1->position, motion2->position);
    result &= floatEquals(motion1->oldPosition, motion2->oldPosition);
    result &= floatEquals(motion1->u, motion2->u);
    return result;
}

bool motionInstructionEquals(MotionInstruction* motionInstruction1, MotionInstruction* motionInstruction2) {
    bool result;
    result &= floatEquals(motionInstruction1->nextPosition, motionInstruction2->nextPosition);
    return result;
}