#include "pidComputer.h"

#include "../../../common/error/error.h"

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

float computeNormalAcceleration(MotionInstruction* inst, float time) {
    // Check If we must move
    if (inst->a == 0.0f) {
        return 0.0f;
    }

    // Acceleration phase
    if (time <= inst->t1) {
        return inst->a;
    }
    // Constant speed -> Acceleration = 0
    else if (time <= inst->t2) {
        // speed = normalSpeed
        return 0.0f;
    }
    // Deceleration : TODO : Manage initial and final Speed
    else if (time <= inst->t3) {
        return -inst->a;
    }
    return 0.0f;
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

float getUFactorAtFullSpeed(bool rotation) {
    // TODO : This expression must also depend on the voltage !!!
    RobotKinematics* robotKinematics = getRobotKinematics();
    float coderWheelDistanceMMBySeconds = getCoderWheelDistanceMMBySecondsAtFullSpeed(robotKinematics, rotation);
    if (coderWheelDistanceMMBySeconds < 0.001f) {
        writeError(ROBOT_KINEMATICS_EEPROM_NOT_INITIALIZED);
        return 0.0f;
    }
    // We calculate the ratio to apply for PWM !
    float result = (float) MAX_PWM / coderWheelDistanceMMBySeconds;
    return result;
}

/**
 * Returns the tension which must be applied to the motor to reach normalSpeed, with no load on motor.
 */
float getNormalU(float speed) {
    // at full Speed (value = 127), 7 rotations / seconds * 20000 impulsions
    // at Frequency of 200 Hz => 730 pulses by pidTime at full Speed
    
    // NormalU = (pulseAtSpeed / pulseAtFullSpeed) * MAX_U
    // TODO : Manage when rotation
    float result = speed * getUFactorAtFullSpeed(false);
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
    // We only limit if maxIntegral is set
    if (!floatEqualsZero( pidParameter->maxIntegral)) {
        values->integralError = limitFloat(values->integralError, pidParameter->maxIntegral);
    }
    // Saves the error
    // When error increases if speed > 0 : error - previousError > 0 (Ex : error (t) = 200, error (t-1) = 150 => 50 (=> increases u)
    // When error decreases if speed > 0 : error - previousError < 0 (Ex : error (t) = 180, error (t-1) = 220 => -40 (=> limits u)

    values->derivativeError = values->error - values->previousError;
    values->previousError = values->error;

    // Corresponds to the normal speed which must be added if we would like to 
    // go to the desired speed
    float result = getNormalU(normalSpeed);

    // Computes PID
    result += (values->error * pidParameter->p
        + values->integralError * pidParameter->i
        + values->derivativeError * pidParameter->d);

    return result;
}
