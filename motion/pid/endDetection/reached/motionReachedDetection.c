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

#define REACHED_WINDOW_COUNT                           5

#define REACHED_DETECTION_DERIVATIVE_ERROR_THRESHOLD   0.05f

/**
 * @private
 */
bool isMotionInstructionReached(PidMotion* pidMotion, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    // We don't consider that we reach the real position before the expected motion
    if (pidMotion->computationValues.pidTimeInSecond <= motionInstruction->t3) {
        return false;
    }
    unsigned windowElementCount = REACHED_WINDOW_COUNT;
    unsigned int startIndex = 0;
    startIndex = currentValues->historyWriteIndex - windowElementCount;
    if (startIndex < 0) {
        startIndex = 0;
    }
    unsigned int index = 0;
    float absDerivativeErrorIntegral = 0.0f;
    for (index = startIndex; index < currentValues->historyWriteIndex - 1; index++) {

        // We check that the derivative error is verly low (stabilization)
        float absDerivativeError = fabsf(currentValues->derivativeErrorHistory[index]);
        absDerivativeErrorIntegral += absDerivativeError;
    }
    return (absDerivativeErrorIntegral < REACHED_DETECTION_DERIVATIVE_ERROR_THRESHOLD);
}

bool isMotionReached(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool thetaReached = isMotionInstructionReached(pidMotion, thetaMotionInstruction, thetaCurrentValues);
    bool alphaReached = isMotionInstructionReached(pidMotion, alphaMotionInstruction, alphaCurrentValues);

    return (thetaReached && alphaReached);

}
