#include <stdlib.h>
#include <stdbool.h>

#include "pid.h"

// Commons

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "alphaTheta.h"
#include "pidMotion.h"
#include "pidTypeOptimizer.h"
#include "computer/pidComputer.h"
#include "parameters/pidParameter.h"
#include "parameters/pidParameterPersistence.h"
#include "pidDebug.h"
#include "pidTimer.h"
#include "detectedMotionType.h"
#include "endDetection/blocked/motionBlockedDetection.h"
#include "endDetection/shocked/motionShockedDetection.h"
#include "endDetection/reached/motionReachedDetection.h"
#include "endDetection/motionEndDetectionStatusUpdater.h"

#include "../../device/motor/pwmMotor.h"

#include "../position/coders.h"
#include "../position/coderErrorComputer.h"

#include "../../robot/kinematics/robotKinematics.h"

unsigned int getPidIndex(enum PidType pidType) {
    return (unsigned int) pidType;
}

void setEnabledPid(PidMotion* pidMotion, unsigned int pidIndex, bool enabled) {
    PidParameter * localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
    localPidParameter->enabled = enabled;
}

void setPidParameter(PidMotion* pidMotion, unsigned int pidIndex, float p, float i, float d, float maxIntegral) {
    PidParameter* localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
    localPidParameter->p = p;
    localPidParameter->i = i;
    localPidParameter->d = d;
    localPidParameter->maxIntegral = maxIntegral;
}

PidParameter* getPidParameterByIndex(PidMotion* pidMotion, unsigned int pidIndex) {
    // To avoid to return NULL
    if (!checkPidTypeIndexInRange(pidIndex)) {
        writeError(PID_TYPE_UNKNOWN_ENUM);
        return &(pidMotion->globalParameters.pidParameters[(unsigned int) PID_TYPE_NONE]);
    }
    PidParameter* result = &(pidMotion->globalParameters.pidParameters[pidIndex]);
    return result;
}

PidParameter* getPidParameterByPidType(PidMotion* pidMotion, enum PidType pidType) {
    unsigned int pidIndex = getPidIndex(pidType);
    PidParameter* result = &(pidMotion->globalParameters.pidParameters[pidIndex]);
    return result;
}

void updateMotorsAndDetectedMotionType(PidMotion* pidMotion) {
    PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    if (motionDefinition == NULL) {
        setDetectedMotionType(&(pidMotion->computationValues), DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH);
        return;
    }
    if (motionDefinition->state != PID_MOTION_DEFINITION_STATE_ACTIVE) {
        setDetectedMotionType(&(pidMotion->computationValues), DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH);
        return;
    }
    if (!mustPidBeRecomputed()) {
        setDetectedMotionType(&(pidMotion->computationValues), DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS);
        return;
    }
    // Here, we must recompute pid
    pidMotion->computationValues.lastPidTimeInSecond = pidMotion->computationValues.pidTimeInSecond;
    pidMotion->computationValues.pidTimeInSecond = getPidTimeInSecond();

    #ifdef _MSC_VER
        #include "pc/pidPc.h"
        simulateCurrentPositionReachIfNeeded(pidMotion, motionDefinition);
    #endif

    // Compute the current Position
    computeCurrentPositionUsingCoders(pidMotion);

    // Adapt PID Type for Final Approach (when stabilized ...)
    changePidTypeIfFinalApproach(pidMotion, motionDefinition);

    // Computes the PID
    motionDefinition->computeU(pidMotion, motionDefinition);

    // Apply Correction

    // 2 dependant Wheels Alpha/Theta (direction +/- angle) => Left/Right correction
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaValues = &(computationValues->values[ALPHA]);
    float leftMotorSpeed = computeLeft(thetaValues->u, alphaValues->u);
    float rightMotorSpeed = computeRight(thetaValues->u, alphaValues->u);
    setMotorSpeeds((int)leftMotorSpeed, (int) rightMotorSpeed);

    // If we maintain the position, we consider that we must do not check the end of motion (next paragraph)
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    if (thetaInst->motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN);
        return;
    }
    
    updateEndDetectionStatusRegister(pidMotion, motionDefinition);

    // Detection if the robot is blocked or not, and update the DetectedMotionType
    if (detectIfRobotIsShocked(pidMotion, motionDefinition)) {
        setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_SHOCK_WHEELS);
        return;
    }
    // Detection if this is the end of the move because we are blocked by something
    if (isMotionBlocked(pidMotion, motionDefinition)) {
        setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS);
        return;
    }

    // Detection if this is the end of the move because we have reached the target
    if (isMotionReached(pidMotion, motionDefinition)) {
        setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_REACHED);
        return;
    }
}
