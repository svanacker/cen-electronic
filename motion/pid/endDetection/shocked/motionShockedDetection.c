#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionShockedDetection.h"

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
 * Detects a shock by analyzing a window of time and check if there is a high acceleration (shock on a short time are often responsible of a high acceleration / deceleration)
 */
bool detectShockByAcceleration(MotionEndDetectionParameter* endDetectionParameters, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    unsigned int windowElementCount = (int) endDetectionParameters->shockedAccelerationWindowAnalysisCount;
    unsigned int startIndex = 0;
    startIndex = currentValues->historyWriteIndex - windowElementCount;
    if (startIndex < 0) {
        startIndex = 0;
    }
    unsigned int index = 0;
    unsigned int matchCount = 0;
    for (index = startIndex; index < currentValues->historyWriteIndex - 1; index++) {
        float absAccelerationHistory = fabsf(currentValues->accelerationHistory[index]);
        // Avoid that a single value could be more than the global threshold
        if (absAccelerationHistory > endDetectionParameters->shockedAccelerationMaxForOneValueThreshold) {
            matchCount++;
        }
    }
    if (matchCount >= endDetectionParameters->shockedAccelerationWindowsMatchCount) {
        return true;
    }
    return false;
}

bool detectIfRobotIsShocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionEndDetectionParameter* endDetectionParameters = &(pidMotion->globalParameters.motionEndDetectionParameter);
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool thetaShocked = detectShockByAcceleration(endDetectionParameters, thetaMotionInstruction, thetaCurrentValues);
    bool alphaShocked = detectShockByAcceleration(endDetectionParameters, alphaMotionInstruction, alphaCurrentValues);

    return (thetaShocked || alphaShocked);
}

