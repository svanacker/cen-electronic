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

#define SHOCKED_DETECTION_ACCELERATION_WINDOW_COUNT 5
#define SHOCKED_DETECTION_ACCELERATION_MAX_FOR_ONE_VALUE_THRESHOLD    10000.0f
#define SHOCKED_DETECTION_ACCELERATION_THRESHOLD                      20000.0f

/**
 * Detects a shock by analyzing a window of time and check if there is a high acceleration (shock on a short time are often responsible of a high acceleration / deceleration)
 */
bool detectShockByAcceleration(MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    unsigned windowElementCount = SHOCKED_DETECTION_ACCELERATION_WINDOW_COUNT;
    unsigned int startIndex = 0;
    startIndex = currentValues->historyWriteIndex - windowElementCount;
    if (startIndex < 0) {
        startIndex = 0;
    }
    unsigned int index = 0;
    float absAccelerationHistoryIntegral = 0.0f;
    for (index = startIndex; index < currentValues->historyWriteIndex - 1; index++) {
        float absAccelerationHistory = fabsf(currentValues->accelerationHistory[index]);
        // Avoid that a single value could be more than the global threshold
        if (absAccelerationHistory > SHOCKED_DETECTION_ACCELERATION_MAX_FOR_ONE_VALUE_THRESHOLD) {
            absAccelerationHistoryIntegral += SHOCKED_DETECTION_ACCELERATION_MAX_FOR_ONE_VALUE_THRESHOLD;
        }
        else {
            absAccelerationHistoryIntegral += absAccelerationHistory;
        }
    }
    if (absAccelerationHistoryIntegral >= SHOCKED_DETECTION_ACCELERATION_THRESHOLD) {
        return true;
    }
    return false;
}

bool detectIfRobotIsShocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool thetaShocked = detectShockByAcceleration(thetaMotionInstruction, thetaCurrentValues);
    bool alphaShocked = detectShockByAcceleration(alphaMotionInstruction, alphaCurrentValues);

    return (thetaShocked || alphaShocked);
}

