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
#include "computer/pidComputer.h"
#include "parameters/pidParameter.h"
#include "parameters/pidPersistence.h"
#include "pidDebug.h"
#include "endDetection/motionEndDetection.h"
#include "pidTimer.h"
#include "detectedMotionType.h"

#include "../../device/motor/pwmMotor.h"

#include "../position/coders.h"
#include "../position/coderErrorComputer.h"

#include "../../robot/kinematics/robotKinematics.h"

unsigned char getIndexOfPid(enum InstructionType instructionType, enum PidType pidType) {
    return pidType * INSTRUCTION_TYPE_COUNT + instructionType;
}

bool getRollingTestMode(PidMotion* pidMotion) {
    return pidMotion->rollingTestMode;
}

// Must Reach Position

bool getMustReachPosition(PidMotion* pidMotion) {
    return pidMotion->mustReachPosition;
}

void setMustReachPosition(PidMotion* pidMotion, bool value) {
	pidMotion->mustReachPosition = value;
}

void setEnabledPid(PidMotion* pidMotion, int pidIndex, unsigned char enabled) {
    PidParameter * localPidParameter = getPidParameter(pidMotion, pidIndex, pidMotion->rollingTestMode);
    localPidParameter->enabled = enabled;
}

void stopPID(PidMotion* pidMotion) {
	setMustReachPosition(pidMotion, false);
}

float getWheelPulseByPidTimeAtFullSpeed(void) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float result = getWheelPulseBySecondsAtFullSpeed(robotKinematics) / PID_UPDATE_MOTORS_FREQUENCY;
    return result;
}

float getUFactorAtFullSpeed(void) {
    // TODO : Why This Constant (must depend on the voltage) !!!
    float result = 128.0f / getWheelPulseByPidTimeAtFullSpeed();
    return result;
}

/**
 * Returns the tension which must be applied to the motor to reach normalSpeed, with no load on motor.
 */
float getNormalU(float pulseAtSpeed) {
    // at full Speed (value = 127), 7 rotations / seconds * 20000 impulsions
    // at Frequency of 200 Hz => 730 pulses by pidTime at full Speed
    
    // NormalU = (pulseAtSpeed / pulseAtFullSpeed) * MAX_U
    float result = pulseAtSpeed * getUFactorAtFullSpeed();
    // float result = 0.0f;
    return result;
}

void setPidParameter(PidMotion* pidMotion, int pidIndex, float p, float i, float d, float maxIntegral) {
    PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, pidMotion->rollingTestMode);
    localPidParameter->p = p;
    localPidParameter->i = i;
    localPidParameter->d = d;
    localPidParameter->maxIntegral = maxIntegral;
}

PidParameter* getPidParameter(PidMotion* pidMotion, int index, unsigned int pidMode) {
    PidParameter* result = &(pidMotion->globalParameters.pidParameters[index]);
    return result;
}

/**
* @private
*/
void changePidTypeIfFinalApproach(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    float pidTime = pidMotion->computationValues.pidTime;

    computeErrorsWithNextPositionUsingCoders(pidMotion, motionDefinition);
    PidComputationValues* computationValues = &(pidMotion->computationValues);

    // Theta and Alpha Error are only used compared to the next position as
    // we only use it to change the PID Type for final Approach
    float thetaError = computationValues->thetaError;
    float alphaError = computationValues->alphaError;
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

    // Change PID type for final Approach
    if ((thetaError < ERROR_FOR_STRONG_PID) && (pidTime > thetaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)
        && (alphaError < ERROR_FOR_STRONG_PID) && (pidTime > alphaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)) {
        thetaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
        alphaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
    }
}

enum DetectedMotionType updateMotors(PidMotion* pidMotion) {
    if (!getMustReachPosition(pidMotion)) {
        return DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
    }
    if (mustPidBeRecomputed()) {
        float pidTime = (float) getPidTime();
		pidMotion->computationValues.pidTime = pidTime;
		PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);

        #ifdef _MSC_VER
			#include "pc/pidPc.h"
			simulateCurrentPositionReachIfNeeded(pidMotion, motionDefinition);
        #endif

        // Compute the current Position
        computeCurrentPositionUsingCoders(pidMotion, motionDefinition);

        // Adapt PID Type for Final Approach (when stabilized ...)
        changePidTypeIfFinalApproach(pidMotion, motionDefinition);

        // Computes the PID
        motionDefinition->computeU(pidMotion, motionDefinition);

        // Apply Correction

        // 2 dependant Wheels Alpha/Theta (direction +/- angle) => Left/Right correction
        PidComputationValues* computationValues = &(pidMotion->computationValues);
        PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
        PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);
        float leftMotorSpeed = computeLeft(thetaCurrentValues->u, alphaCurrentValues->u);
        float rightMotorSpeed = computeRight(thetaCurrentValues->u, alphaCurrentValues->u);
        setMotorSpeeds((int)leftMotorSpeed, (int) rightMotorSpeed);

        // If we maintain the position, we consider that we must maintain indefinitely the position
        MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
        if (thetaInst->motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
            return DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN;
        }

        // DETECTS END OF MOTION => TODO : Extract it in a method
        MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        MotionEndInfo* thetaEndMotion = &(computationValues->motionEnd[THETA]);
        MotionEndInfo* alphaEndMotion = &(computationValues->motionEnd[ALPHA]);
    
        thetaCurrentValues->currentSpeed = thetaCurrentValues->position - thetaCurrentValues->oldPosition;
        alphaCurrentValues->currentSpeed = alphaCurrentValues->position - alphaCurrentValues->oldPosition;

        updateEndMotionData(computationValues, THETA, thetaEndMotion, endDetectionParameter, (int) pidTime);
        updateEndMotionData(computationValues, ALPHA, alphaEndMotion, endDetectionParameter, (int) pidTime);

        bool isThetaEnd = isEndOfMotion(THETA, thetaEndMotion, endDetectionParameter);
        bool isAlphaEnd = isEndOfMotion(ALPHA, alphaEndMotion, endDetectionParameter);

        bool isThetaBlocked = isRobotBlocked(motionDefinition, THETA, thetaEndMotion, endDetectionParameter);
        bool isAlphaBlocked = isRobotBlocked(motionDefinition, ALPHA, alphaEndMotion, endDetectionParameter);

        if (isThetaEnd && isAlphaEnd) {
            if (isThetaBlocked || isAlphaBlocked) {
                return DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS;
            } else {
                return DETECTED_MOTION_TYPE_POSITION_REACHED;
            }
        }
    }
    return DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS;
}
