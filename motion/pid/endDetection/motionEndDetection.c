#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionEndDetection.h"

#include "../../../common/commons.h"
#include "../../../common/math/cenMath.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../parameters/motionParameter.h"
#include "../detectedMotionType.h"
#include "../pidComputationValues.h"
#include "../computer/pidComputer.h"
#include "../pidConstants.h"
#include "../pid.h"


/**
 * Detects a shock by analyzing a window of time and check if there is a high acceleration (shock on a short time are often responsible of a high acceleration / deceleration)
 */
bool detectShockByAcceleration(MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    enum MotionParameterType motionParameterType = motionInstruction->motionParameterType;
    float baseAcceleration = motionInstruction->a;
    float accelerationThreshold = fabsf(baseAcceleration * 5.0f);

    RobotKinematics* robotKinematics = getRobotKinematics();
    // Avoid to detect too low acceleration
    float maxAcceleration = getRobotAccelerationMaxMillimeterBySecondSquare(robotKinematics);
    if (fabsf(baseAcceleration * 10) < maxAcceleration) {
        return false;
    }

    unsigned windowElementCount = 5;
    unsigned int startIndex = 0;
    startIndex = currentValues->historyWriteIndex - windowElementCount;
    if (startIndex < 0) {
        startIndex = 0;
    }
    unsigned int index = 0;
    unsigned int aboveThresholdCount = 0;
    for (index = startIndex; index < currentValues->historyWriteIndex - 1; index++) {
        if (fabsf(currentValues->accelerationHistory[index]) > accelerationThreshold) {
            aboveThresholdCount++;
        }
    }
    if (2 * aboveThresholdCount > windowElementCount) {
        return true;
    }
    return false;
}

void detectIfRobotIsBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    bool thetaShocked = detectShockByAcceleration(thetaMotionInstruction, thetaCurrentValues);
    bool alphaShocked = detectShockByAcceleration(alphaMotionInstruction, alphaCurrentValues);

    if (thetaShocked || alphaShocked) {
        setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS);
        return;
    }
    /*
    MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        

    thetaCurrentValues->accelerationHistory[i]
    MotionEndInfo* thetaEndMotion = &(computationValues->values[THETA].motionEnd);
    MotionEndInfo* alphaEndMotion = &(computationValues->values[ALPHA].motionEnd);
    thetaCurrentValues->currentSpeed = thetaCurrentValues->currentPosition - thetaCurrentValues->oldPosition;
    alphaCurrentValues->currentSpeed = alphaCurrentValues->currentPosition - alphaCurrentValues->oldPosition;

    updateEndMotionData(computationValues, THETA, thetaEndMotion, endDetectionParameter, (int) computationValues->pidTime);
    updateEndMotionData(computationValues, ALPHA, alphaEndMotion, endDetectionParameter, (int) computationValues->pidTime);

    bool isThetaEnd = isEndOfMotion(THETA, thetaEndMotion, endDetectionParameter);
    bool isAlphaEnd = isEndOfMotion(ALPHA, alphaEndMotion, endDetectionParameter);

    bool isThetaBlocked = isMotionInstructionIsBlocked(motionDefinition, THETA, thetaEndMotion, endDetectionParameter);
    bool isAlphaBlocked = isMotionInstructionIsBlocked(motionDefinition, ALPHA, alphaEndMotion, endDetectionParameter);

    if (isThetaEnd && isAlphaEnd) {
        if (isThetaBlocked || isAlphaBlocked) {
            setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS);
            return;
        } else {
            setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_REACHED);
            return;
        }
    }
    // If not blocked or not reached -> In Progress
    setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS);
    */
}