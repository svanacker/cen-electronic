#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionBlockedDetection.h"

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
bool isMotionInstructionBlocked(PidMotion* pidMotion, MotionInstruction* motionInstruction) {
	return false;
}

bool isMotionBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);
    
    bool isThetaBlocked = isMotionInstructionBlocked(pidMotion, thetaMotionInstruction);
    bool isAlphaBlocked = isMotionInstructionBlocked(pidMotion, alphaMotionInstruction);
    
    return (isAlphaBlocked || isThetaBlocked);
}
