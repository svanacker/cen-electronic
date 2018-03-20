#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionReachedDetection.h"

#include "../../../../common/commons.h"
#include "../../../../common/math/cenMath.h"

#include "../../../../common/io/buffer.h"
#include "../../../../common/io/outputStream.h"
#include "../../../../common/io/printWriter.h"
#include "../../../../common/io/reader.h"

#include "../../../../common/log/logger.h"
#include "../../../../common/log/logLevel.h"

#include "../../../parameters/motionParameter.h"
#include "../../detectedMotionType.h"
#include "../../pidComputationValues.h"
#include "../../computer/pidComputer.h"
#include "../../pidConstants.h"
#include "../../pid.h"

/**
 * @private
 */
bool isMotionInstructionReached(PidMotion* pidMotion, MotionInstruction* motionInstruction) {
    // FIRST NAIVE IMPLEMENTATION
    if (pidMotion->computationValues.pidTimeInSecond > motionInstruction->t3 * 2.0f) {
        return true;
    }
    return false;
}

bool isMotionReached(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);
    
    bool isThetaReached = isMotionInstructionReached(pidMotion, thetaMotionInstruction);
    bool isAlphaReached = isMotionInstructionReached(pidMotion, alphaMotionInstruction);
    
    return (isAlphaReached && isThetaReached);
}
