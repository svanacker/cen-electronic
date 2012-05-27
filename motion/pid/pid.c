#include <math.h>
#include <stdlib.h>

#include "pid.h"
#include "pidComputer.h"
#include "pidPersistence.h"
#include "pidDebug.h"
#include "motionEndDetection.h"
#include "pidTimer.h"
#include "pidMotionProfileComputer.h"

// Commons

#include "pidTimer.h"

#include "../../common/commons.h"

#include "../../common/error/error.h"

#include "../../common/math/cenMath.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/motor/pwmMotor.h"

#include "../../motion/extended/bspline.h"

#include "../../motion/position/coders.h"
#include "../../motion/position/coderErrorComputer.h"
#include "../../motion/position/trajectory.h"

#include "../../motion/simple/motion.h"

#include "../../robot/robotConstants.h"

// Contains all information about current motion
static PidMotion pidMotion;

/** Indicates if we use the testing Board (we take lower values for PID). */
static unsigned char rollingTestMode = ROLLING_BOARD_TEST_MODE_OFF;

unsigned char getIndexOfPid(unsigned char instructionIndex, unsigned char pidType) {
    return pidType * INSTRUCTION_COUNT + instructionIndex;
}

unsigned char getRollingTestMode() {
    return rollingTestMode;
}

BOOL getMustReachPosition(void) {
    return pidMotion.currentMotionDefinition == NULL;
}

void setEnabledPid(int pidIndex, unsigned char enabled) {
    Pid * localPid = getPID(pidIndex, rollingTestMode);
    localPid->enabled = enabled;
}

PidMotion* getPidMotion() {
	return &pidMotion;
}

MotionEndDetectionParameter* getMotionEndDetectionParameter() {
	return &(pidMotion.globalParameters.motionEndDetectionParameter);
}

BOOL isMotionDefinitionListEmpty() {
	return pidMotion.readMotionInstructionIndex == pidMotion.writeMotionInstructionIndex;
}

BOOL isMotionDefinitionListFull() {
    return ((pidMotion.writeMotionInstructionIndex + 1) % NEXT_MOTION_DEFINITION_COUNT) == pidMotion.readMotionInstructionIndex;
}

void clearMotionDefinitionList() {
    appendString(getDebugOutputStreamLogger(), "\nclearMotionDefinitionList\n");

	pidMotion.currentMotionDefinition = NULL;
	pidMotion.readMotionInstructionIndex = 0;
	pidMotion.writeMotionInstructionIndex = 0;
}

void initForNextMotionDefinition() {
	initNextPositionVars(INSTRUCTION_ALPHA_INDEX);
	initNextPositionVars(INSTRUCTION_THETA_INDEX);

	updateTrajectory();
	updateTrajectoryAndClearCoders();
	clearPidTime();
}

void gotoNextMotionDefinition() {
    appendString(getDebugOutputStreamLogger(), "\ngotoNextMotionDefinition\n");
	initForNextMotionDefinition();

	pidMotion.currentMotionDefinition = NULL;
	
	if (getMotionDefinitionElementsCount() >= 2) {
		pidMotion.currentMotionDefinition = getPidMotionDefinitionToRead();	
	}
}

int getMotionDefinitionElementsCount() {
    int result = pidMotion.writeMotionInstructionIndex - pidMotion.readMotionInstructionIndex;
    if (result < 0) {
        result += NEXT_MOTION_DEFINITION_COUNT;
    }
    return result;
}

PidMotionDefinition* getCurrentPidMotionDefinition() {
	return pidMotion.currentMotionDefinition;
}

PidMotionDefinition* getPidMotionDefinitionToRead() {
    appendString(getDebugOutputStreamLogger(), "\ngetPidMotionDefinitionToRead\n");

	BOOL isEmpty = isMotionDefinitionListEmpty();
	if (!isEmpty) {
		PidMotionDefinition* result = &(pidMotion.motionDefinitions[pidMotion.readMotionInstructionIndex]);

        pidMotion.readMotionInstructionIndex++;
        pidMotion.readMotionInstructionIndex %= NEXT_MOTION_DEFINITION_COUNT;

		return result;
	}
	else {
		writeError(MOTION_DEFINITION_EMPTY);		
	}
	return NULL;
}

void clearMotionInstruction(MotionInstruction* motionInstruction) {
    motionInstruction->nextPosition = 0;
    motionInstruction->a = 0;
    motionInstruction->initialSpeed = 0;
    motionInstruction->speed = 0;
	motionInstruction->speedMax = 0;
	motionInstruction->endSpeed = 0;
    motionInstruction->t1 = 0;
    motionInstruction->t2 = 0;
	motionInstruction->t3 = 0;
    motionInstruction->p1 = 0;
    motionInstruction->p2 = 0;
    motionInstruction->profileType = 0;
    motionInstruction->motionType = 0;
    motionInstruction->pidType = 0;	
}

void clearMotionDefinition(PidMotionDefinition* motionDefinition) {
    MotionInstruction* alphaInst = &(motionDefinition->inst[INSTRUCTION_ALPHA_INDEX]);
    MotionInstruction* thetaInst = &(motionDefinition->inst[INSTRUCTION_THETA_INDEX]);
	clearMotionInstruction(alphaInst);
	clearMotionInstruction(thetaInst);
	initFirstTimeBSplineCurve(&(motionDefinition->curve));
	motionDefinition->computeU = NULL;
}

PidMotionDefinition* getPidMotionDefinitionToWrite() {
    appendString(getDebugOutputStreamLogger(), "\ngetPidMotionDefinitionToWrite\n");

	BOOL isFull = isMotionDefinitionListFull();

    if (!isFull) {
		PidMotionDefinition* result = &(pidMotion.motionDefinitions[pidMotion.writeMotionInstructionIndex]);
		clearMotionDefinition(result);
        pidMotion.writeMotionInstructionIndex++;
		pidMotion.writeMotionInstructionIndex %= NEXT_MOTION_DEFINITION_COUNT;
		printPidMotion(getDebugOutputStreamLogger());

	   return result;
    } else {
        // We must log the problem
        writeError(MOTION_DEFINITION_FULL);
    }
	return NULL;
}

/**
 * Init global variable storing information about motion.
 */
void initPidMotion() {
	initMotionEndParameter(getMotionEndDetectionParameter());
	int i;
	for (i = 0; i < NEXT_MOTION_DEFINITION_COUNT; i++) {
		clearMotionDefinition(&(pidMotion.motionDefinitions[i]));
	}
	clearMotionDefinitionList();
}

void initPID(void) {
    // TODO : A Remettre
    // rollingTestMode = (getConfigValue() & CONFIG_ROLLING_TEST_MASK) != 0;
    rollingTestMode = 0;
    loadPID();
    initPidTimer();
    initPidMotion();
}

void stopPID(void) {
    clearMotionDefinitionList();
}

/**
 * Returns the tension which must be applied to the motor to reach normalSpeed, with no load on motor.
 */
float getNormalU(float pulseAtSpeed) {
    // at full Speed (value = 127), 7 rotations / seconds * 20000 impulsions
	// at Frequency of 200 Hz => 730 pulses by pidTime at full Speed
	
	// NormalU = (pulseAtSpeed / pulseAtFullSpeed) * MAX_U
    float result = pulseAtSpeed * U_FACTOR_AT_FULL_SPEED;
	// float result = 0.0f;
    return result;
}

void setPID(int pidIndex, float p, float i, float d, float maxIntegral) {
    Pid* localPid = getPID(pidIndex, rollingTestMode);
    localPid->p = p;
    localPid->i = i;
    localPid->d = d;
    localPid->maxIntegral = maxIntegral;
}

Pid* getPID(int index, unsigned int pidMode) {
    Pid* result = &(pidMotion.globalParameters.pid[index]);
    return result;
}

unsigned int updateMotors(void) {
    if (isMotionDefinitionListEmpty()) {
        return NO_POSITION_TO_REACH;
    }
	if (mustPidBeRecomputed()) {
		PidMotionDefinition* motionDefinition = getCurrentPidMotionDefinition();
		if (motionDefinition == NULL) {
	        return NO_POSITION_TO_REACH;
		}

        float pidTime = (float) getPidTime();
        pidMotion.computationValues.pidTime = pidTime;

        MotionInstruction* thetaInst = &(motionDefinition->inst[INSTRUCTION_THETA_INDEX]);
        MotionInstruction* alphaInst = &(motionDefinition->inst[INSTRUCTION_ALPHA_INDEX]);

		PidComputationValues* computationValues = &(pidMotion.computationValues);
        Motion* thetaMotion = &(computationValues->motion[INSTRUCTION_THETA_INDEX]);
        Motion* alphaMotion = &(computationValues->motion[INSTRUCTION_ALPHA_INDEX]);

        computeErrorsUsingCoders(&pidMotion);

        float thetaError = computationValues->thetaError;
        float alphaError = computationValues->alphaError;

		// Change PID type for final Approach
        if ((thetaError < ERROR_FOR_STRONG_PID) && (pidTime > thetaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)
                && (alphaError < ERROR_FOR_STRONG_PID) && (pidTime > alphaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)) {
            thetaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
            alphaInst->pidType = PID_TYPE_FINAL_APPROACH_INDEX;
        }

        // Computes the PID
		motionDefinition->computeU();

        // 2 dependant Wheels (direction + angle)
        float leftMotorSpeed = (thetaMotion->u + alphaMotion->u) / 2.0f;
        float rightMotorSpeed = (thetaMotion->u - alphaMotion->u) / 2.0f;
        setMotorSpeeds(leftMotorSpeed, rightMotorSpeed);

        // If we maintain the position, we consider that we must maintain indefinitely the position
        if (thetaInst->motionType == MOTION_TYPE_MAINTAIN_POSITION) {
            return POSITION_TO_MAINTAIN;
        }

		MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter();
		MotionEndInfo* thetaEndMotion = &(computationValues->motionEnd[INSTRUCTION_THETA_INDEX]);
		MotionEndInfo* alphaEndMotion = &(computationValues->motionEnd[INSTRUCTION_ALPHA_INDEX]);
	
		thetaMotion->currentSpeed = thetaMotion->position - thetaMotion->oldPosition;
		alphaMotion->currentSpeed = alphaMotion->position - alphaMotion->oldPosition;

		updateEndMotionData(INSTRUCTION_THETA_INDEX, thetaEndMotion, endDetectionParameter, pidTime);
		updateEndMotionData(INSTRUCTION_ALPHA_INDEX, alphaEndMotion, endDetectionParameter, pidTime);

		BOOL isThetaEnd = isEndOfMotion(INSTRUCTION_THETA_INDEX, thetaEndMotion, endDetectionParameter);
		BOOL isAlphaEnd = isEndOfMotion(INSTRUCTION_ALPHA_INDEX, alphaEndMotion, endDetectionParameter);

		BOOL isThetaBlocked = isRobotBlocked(INSTRUCTION_THETA_INDEX, thetaEndMotion, endDetectionParameter);
		BOOL isAlphaBlocked = isRobotBlocked(INSTRUCTION_ALPHA_INDEX, alphaEndMotion, endDetectionParameter);

		if (isThetaEnd && isAlphaEnd) {
			if (isThetaBlocked || isAlphaBlocked) {
				// Clear navigation List
//				clearMotionDefinitionList();
				gotoNextMotionDefinition();

				return POSITION_BLOCKED_WHEELS;
            } else {
				// GOTO Next motion
				gotoNextMotionDefinition();
                return POSITION_REACHED;
            }
		}
    }
    return POSITION_IN_PROGRESS;
}
