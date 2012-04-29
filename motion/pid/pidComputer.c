#include "pidComputer.h"
#include "pid.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

float computePidCorrection(MotionError* motionError,
        Pid* pid,
        float normalSpeed,
        float error) {
    // Computes the error, and limit too high value
    motionError->error = error;

    // Computes the integral error, and limit too high value
    motionError->integralError += motionError->error;
    motionError->integralError = limit(motionError->integralError, pid->maxIntegral);

    // Saves the error
    // When error increases if speed > 0 : error - previousError > 0 (Ex : error (t) = 200, error (t-1) = 150 => 50 (=> increases u)
    // When error decreases if speed > 0 : error - previousError < 0 (Ex : error (t) = 180, error (t-1) = 220 => -40 (=> limits u)

    motionError->derivativeError = motionError->error - motionError->previousError;
    motionError->previousError = motionError->error;

    // Computes PID
    float u = (motionError->error * pid->p
            + motionError->integralError * pid->i
            + motionError->derivativeError * pid->d);

    // We divide to be on cool range when defining PID constant
    float result = (u / PID_GLOBAL_DIVISER);

    // Corresponds to the normal speed which must be added
    result += getNormalU(normalSpeed);

    // Limits the value of "u"
    result = limit(result, PID_NEXT_VALUE_LIMIT);

    return result;
}

float computeNormalSpeed(MotionInstruction* inst, float time) {
    float result = inst->initialSpeed;

    // If we must move
    if (inst->a == 0.0f) {
        return result;
    }

    // Acceleration phase
    if (time <= inst->t1) {
        // normalSpeed = initialSpeed + (a * t)
        result = inst->initialSpeed + (inst->a * time);
    } else if (time <= inst->t2) {
        // speed = normalSpeed
        result = inst->speedMax;
    } else if (time <= inst->t3) {
        // normalSpeed = speedMax - a * (time - t2) 
        float dt = time - inst->t2;
        result = inst->speedMax - (inst->a * dt);
    } else {
		result = inst->endSpeed;
	}
    return result;
}

float computeNormalPosition(MotionInstruction* inst, float time) {
    float result = 0.0f;
    // If we must move
    if (inst->a == 0.0f) {
        return result;
    }
    // Acceleration phase
    if (time <= inst->t1) {
        // P = initialSpeed * T + 1/2 * a * T * T
        result = (inst->initialSpeed * time) + (inst->a * (time * time)) / 2.0f;
    } else if (time <= inst->t2) {
        // P = P1 + SpeedMax * (time - T1)
        result = inst->p1 + (inst->speedMax * (time - inst->t1));
    } else if (time <= inst->t3) {
        // P = P2 + speedMax * dt - 1/2 * a * dt * dt
        float dt = time - inst->t2;
		// TODO : A Vérifier
        result = inst->p2 + (inst->speedMax * dt) - (inst->a * dt * dt) / 2.0f;
    } else {
        // P = normalPosition + endSpeed * diffTimeSinceT3
		float dt = time - inst->t3;
        result = inst->nextPosition + inst->endSpeed * dt;
    }
    return result;
}

/**
 * @private
 * Computes the next value of the pid.
 * @param instructionIndex the pid that we want to compute (0 = alpha, 1 = theta)
 * @param pidType the type of pid that we want to compute (between 0 and PID_TYPE_COUNT)
 * @param currentPosition the current position of the wheels (either alphaPosition, either thetaPosition)
 * @param time the time in pid sampling
 */
float computeNextPID(int instructionIndex,
        unsigned char pidType,
        float currentPosition,
        float time) {
    MotionInstruction* motionInstruction = getMotionInstruction(instructionIndex);
    MotionError* motionError = getMotionError(instructionIndex);

    unsigned char rollingTestMode = getRollingTestMode();

    // instructionIndex = Alpha / Theta
    // pidType = Forward / Rotation / Final Approach ...
    unsigned pidIndex = getIndexOfPid(instructionIndex, pidType);
    Pid* pid = getPID(pidIndex, rollingTestMode);

    if (!pid->enabled) {
        return 0.0f;
    }

    float normalPosition = computeNormalPosition(motionInstruction, time);
    float normalSpeed = computeNormalSpeed(motionInstruction, time);

	float positionError = normalPosition - currentPosition;
    float result = computePidCorrection(motionError, pid, normalSpeed, positionError);

    return result;
}

/**
 * Compute the PID when the instruction is very simple (not b spline)
 */
void simpleMotionUCompute(MotionInstruction* thetaInst,
                                    MotionInstruction* alphaInst,
                                    Motion* thetaMotion,
                                    Motion* alphaMotion, 
									float pidTime) {
        thetaMotion->u = computeNextPID(INSTRUCTION_THETA_INDEX, thetaInst->pidType, thetaMotion->position, pidTime);
        alphaMotion->u = computeNextPID(INSTRUCTION_ALPHA_INDEX, alphaInst->pidType, alphaMotion->position, pidTime);
}
