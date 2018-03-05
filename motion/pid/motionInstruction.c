#include "motionInstruction.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// TODO : Move code into PIDComputer
#include "computer/pidComputer.h"

void clearMotionInstruction(MotionInstruction* motionInstruction) {
    motionInstruction->nextPosition = 0.0f;
    motionInstruction->a = 0.0f;
    motionInstruction->initialSpeed = 0.0f;
    motionInstruction->speed = 0.0f;
    motionInstruction->speedMax = 0.0f;
    motionInstruction->endSpeed = 0.0f;
    motionInstruction->t1 = 0.0f;
    motionInstruction->t2 = 0.0f;
    motionInstruction->t3 = 0.0f;
    motionInstruction->p1 = 0.0f;
    motionInstruction->p2 = 0.0f;
    // TODO : Define a profile "UNKNOWN"
    motionInstruction->profileType = PROFILE_TYPE_UNDEFINED;
    motionInstruction->motionParameterType = MOTION_PARAMETER_TYPE_UNDEFINED;
    motionInstruction->pidType = PID_TYPE_GO_INDEX;
}

