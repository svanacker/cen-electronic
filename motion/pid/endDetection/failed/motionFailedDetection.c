#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionFailedDetection.h"



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
bool isMotionInstructionFailed(PidMotion* pidMotion, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    MotionEndDetectionParameter* endDetectionParameters = &(pidMotion->globalParameters.motionEndDetectionParameter);

    // We don't consider that we reach the real position before the expected motion
    if (pidMotion->computationValues.pidTimeInSecond > motionInstruction->t3 + endDetectionParameters->failedTimeoutAfterT3InSecond) {
        return true;
    }
    return false;
}

bool isMotionFailed(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool thetaFailed = isMotionInstructionFailed(pidMotion, thetaMotionInstruction, thetaCurrentValues);
    bool alphaFailed = isMotionInstructionFailed(pidMotion, alphaMotionInstruction, alphaCurrentValues);

    // Both must failed, because if we go forward, alpha could be reach at time = 0.0f;
    return (thetaFailed && alphaFailed);

}
