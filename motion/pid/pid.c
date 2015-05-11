#include <stdlib.h>
#include <stdbool.h>

// Commons

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "pid.h"
#include "pidMotion.h"
#include "computer/pidComputer.h"
#include "parameters/pidParameter.h"
#include "parameters/pidPersistence.h"
#include "pidDebug.h"
#include "endDetection/motionEndDetection.h"
#include "pidTimer.h"
#include "pidMotionDefinition.h"
#include "detectedMotionType.h"

#include "../../device/motor/pwmMotor.h"

#include "../position/coders.h"
#include "../position/coderErrorComputer.h"

#include "../../robot/kinematics/robotKinematics.h"

static bool mustReachPosition;
static bool simulatedMove;

/** Indicates if we use the testing Board (we take lower values for PID). */
static bool rollingTestMode = ROLLING_BOARD_TEST_MODE_OFF;

unsigned char getIndexOfPid(enum InstructionType instructionType, enum PidType pidType) {
    return pidType * INSTRUCTION_COUNT + instructionType;
}

bool getRollingTestMode() {
    return rollingTestMode;
}

// Must Reach Position

bool getMustReachPosition(void) {
    return mustReachPosition;
}

void setMustReachPosition(bool value) {
    mustReachPosition = value;
}

void setEnabledPid(int pidIndex, unsigned char enabled) {
    PidParameter * localPidParameter = getPidParameter(pidIndex, rollingTestMode);
    localPidParameter->enabled = enabled;
}


void initPID(Eeprom* _eeprom, bool loadDefaultParameters) {
    // TODO : A Remettre
    // rollingTestMode = (getConfigValue() & CONFIG_ROLLING_TEST_MASK) != 0;
    rollingTestMode = false;
    initPidPersistence(_eeprom);
    loadPidParameters(loadDefaultParameters);
    RobotKinematics* robotKinematics = getRobotKinematics();
    loadRobotKinematicsParameters(robotKinematics, _eeprom, loadDefaultParameters);
    initPidTimer();
    initPidMotion();
}

void stopPID(void) {
    mustReachPosition = false;
}

float getWheelPulseByPidTimeAtFullSpeed() {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float result = getWheelPulseBySecondsAtFullSpeed(robotKinematics) / PID_UPDATE_MOTORS_FREQUENCY;
    return result;
}

float getUFactorAtFullSpeed() {
    // TODO : Why This Constant (must d epend on the voltage) !!!
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

void setPidParameter(int pidIndex, float p, float i, float d, float maxIntegral) {
    PidParameter* localPidParameter = getPidParameter(pidIndex, rollingTestMode);
    localPidParameter->p = p;
    localPidParameter->i = i;
    localPidParameter->d = d;
    localPidParameter->maxIntegral = maxIntegral;
}

PidParameter* getPidParameter(int index, unsigned int pidMode) {
    PidParameter* result = &(getPidMotion()->globalParameters.pidParameters[index]);
    return result;
}

enum DetectedMotionType updateMotors(void) {
    if (!mustReachPosition) {
        return DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
    }
    if (mustPidBeRecomputed()) {
        PidMotion* pidMotion = getPidMotion();
        float pidTime = (float) getPidTime();
        getPidMotion()->computationValues.pidTime = pidTime;

        computeErrorsUsingCoders(pidMotion);

        PidComputationValues* computationValues = &(pidMotion->computationValues);
        PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
        PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);

        float thetaError = computationValues->thetaError;
        float alphaError = computationValues->alphaError;

        PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);
        MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
        MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

        // Change PID type for final Approach
        if ((thetaError < ERROR_FOR_STRONG_PID) && (pidTime > thetaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)
                && (alphaError < ERROR_FOR_STRONG_PID) && (pidTime > alphaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)) {
            thetaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
            alphaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
        }

        // Computes the PID
        motionDefinition->computeU(pidMotion);

        // 2 dependant Wheels Alpha/Theta (direction +/- angle) => Left/Right correction
        float leftMotorSpeed = computeLeft(thetaCurrentValues->u, alphaCurrentValues->u);
        float rightMotorSpeed = computeRight(thetaCurrentValues->u, alphaCurrentValues->u);
        setMotorSpeeds((int)leftMotorSpeed, (int) rightMotorSpeed);

        // If we maintain the position, we consider that we must maintain indefinitely the position
        if (thetaInst->motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
            return DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN;
        }

        MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter();
        MotionEndInfo* thetaEndMotion = &(computationValues->motionEnd[THETA]);
        MotionEndInfo* alphaEndMotion = &(computationValues->motionEnd[ALPHA]);
    
        thetaCurrentValues->currentSpeed = thetaCurrentValues->position - thetaCurrentValues->oldPosition;
        alphaCurrentValues->currentSpeed = alphaCurrentValues->position - alphaCurrentValues->oldPosition;

        updateEndMotionData(THETA, thetaEndMotion, endDetectionParameter, (int) pidTime);
        updateEndMotionData(ALPHA, alphaEndMotion, endDetectionParameter, (int) pidTime);

        bool isThetaEnd = isEndOfMotion(THETA, thetaEndMotion, endDetectionParameter);
        bool isAlphaEnd = isEndOfMotion(ALPHA, alphaEndMotion, endDetectionParameter);

        bool isThetaBlocked = isRobotBlocked(THETA, thetaEndMotion, endDetectionParameter);
        bool isAlphaBlocked = isRobotBlocked(ALPHA, alphaEndMotion, endDetectionParameter);

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
