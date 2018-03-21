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
bool isMotionInstructionBlocked(MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    unsigned windowElementCount = 10;
    unsigned int startIndex = 0;
    startIndex = currentValues->historyWriteIndex - windowElementCount;
    if (startIndex < 0) {
        startIndex = 0;
    }
    unsigned int index = 0;
    unsigned int aboveThresholdCount = 0;
    for (index = startIndex; index < currentValues->historyWriteIndex - 1; index++) {
        if (currentValues->statusHistory[index].absUTooHighThanExpected) {
            aboveThresholdCount++;
        }
    }
    // If more than 50% have the status higher than expected
    if (2 * aboveThresholdCount > windowElementCount) {
        return true;
    }
    return false;
}

bool isMotionBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);
    
    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool isThetaBlocked = isMotionInstructionBlocked(thetaMotionInstruction, thetaCurrentValues);
    bool isAlphaBlocked = isMotionInstructionBlocked(alphaMotionInstruction, alphaCurrentValues);
    
    return (isAlphaBlocked || isThetaBlocked);
}
