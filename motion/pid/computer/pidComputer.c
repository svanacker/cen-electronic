#include "pidComputer.h"

#include "../pidComputationValues.h"
#include "../pid.h"
#include "../instructionType.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../pidCurrentValues.h"
#include "../pidMotionError.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

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
        // TODO : To be checked
        result = inst->p2 + (inst->speedMax * dt) - (inst->a * dt * dt) / 2.0f;
    } else {
        // P = normalPosition + endSpeed * diffTimeSinceT3
        float dt = time - inst->t3;
        result = inst->nextPosition + inst->endSpeed * dt;
    }
    return result;
}

float computePidCorrection(PidMotionError* motionError,
                            PidParameter* pidParameter,
                            float normalSpeed,
                            float error) {
    // Computes the error, and limit too high value
    motionError->error = error;

    // Computes the integral error, and limit too high value
    motionError->integralError += motionError->error;
    motionError->integralError = limitFloat(motionError->integralError, pidParameter->maxIntegral);

    // Saves the error
    // When error increases if speed > 0 : error - previousError > 0 (Ex : error (t) = 200, error (t-1) = 150 => 50 (=> increases u)
    // When error decreases if speed > 0 : error - previousError < 0 (Ex : error (t) = 180, error (t-1) = 220 => -40 (=> limits u)

    motionError->derivativeError = motionError->error - motionError->previousError;
    motionError->previousError = motionError->error;

    // Computes PID
    float u = (motionError->error * pidParameter->p
        + motionError->integralError * pidParameter->i
        + motionError->derivativeError * pidParameter->d);

    // We divide to be on cool range when defining PID constant
    float result = (u / PID_GLOBAL_DIVISER);

    // Corresponds to the normal speed which must be added
    result += getNormalU(normalSpeed);

    // Limits the value of "u"
    result = (float) limitFloat(result, PID_NEXT_VALUE_LIMIT);

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



