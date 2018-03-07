#include "pidComputer.h"

#include "../../../common/pwm/motor/dualHBridgeMotorPwm.h"
#include "../pidComputationValues.h"
#include "../pid.h"
#include "../pidTimer.h"
#include "../instructionType.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../pidComputationInstructionValues.h"

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

float pulseByPidTimeSpeedToMMBySecondSpeed(float pulseSpeed) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float result = pulseSpeed * getCoderAverageWheelLengthForOnePulse(robotKinematics) * PID_UPDATE_MOTORS_FREQUENCY_HERTZ;
    return result;
}

float getCoderWheelPulseByPidTimeAtFullSpeed(bool rotation) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    float result = getCoderWheelPulseBySecondsAtFullSpeed(robotKinematics, rotation) / PID_UPDATE_MOTORS_FREQUENCY_HERTZ;
    return result;
}

float getUFactorAtFullSpeed(bool rotation) {
    // TODO : This expression must also depend on the voltage !!!
    float result = MAX_PWM / getCoderWheelPulseByPidTimeAtFullSpeed(rotation);
    return result;
}

/**
 * Returns the tension which must be applied to the motor to reach normalSpeed, with no load on motor.
 */
float getNormalU(float pulseAtSpeed) {
    // at full Speed (value = 127), 7 rotations / seconds * 20000 impulsions
    // at Frequency of 200 Hz => 730 pulses by pidTime at full Speed
    
    // NormalU = (pulseAtSpeed / pulseAtFullSpeed) * MAX_U
    // TODO : Manage when rotation
    float result = pulseAtSpeed * getUFactorAtFullSpeed(false);
    return result;
}

float computePidCorrection(PidComputationInstructionValues* values,
                            PidParameter* pidParameter,
                            float normalSpeed,
                            float error) {
    // Computes the error, and limit too high value
    values->error = error;

    // Computes the integral error, and limit too high value
    values->integralError += values->error;
    values->integralError = limitFloat(values->integralError, pidParameter->maxIntegral);

    // Saves the error
    // When error increases if speed > 0 : error - previousError > 0 (Ex : error (t) = 200, error (t-1) = 150 => 50 (=> increases u)
    // When error decreases if speed > 0 : error - previousError < 0 (Ex : error (t) = 180, error (t-1) = 220 => -40 (=> limits u)

    values->derivativeError = values->error - values->previousError;
    values->previousError = values->error;

    // Computes PID
    float u = (values->error * pidParameter->p
        + values->integralError * pidParameter->i
        + values->derivativeError * pidParameter->d);

    // We divide to be on cool range when defining PID constant
    float result = (u / PID_GLOBAL_DIVISER);

    // Corresponds to the normal speed which must be added if we would like to 
    // go to the desired speed
    result += getNormalU(normalSpeed);

    // Limits the value of "u"
    result = (float) limitFloat(result, PID_NEXT_VALUE_LIMIT);

    return result;
}
