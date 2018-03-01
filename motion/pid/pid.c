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

void setEnabledPid(PidMotion* pidMotion, int pidIndex, unsigned char enabled) {
    PidParameter * localPidParameter = getPidParameter(pidMotion, pidIndex, pidMotion->rollingTestMode);
    localPidParameter->enabled = enabled;
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

void updateMotorsAndDetectedMotionType(PidMotion* pidMotion) {
    PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    if (motionDefinition == NULL) {
        pidMotion->computationValues.detectedMotionType = DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
        return;
    }
    if (motionDefinition->state != PID_MOTION_DEFINITION_STATE_ACTIVE) {
        pidMotion->computationValues.detectedMotionType = DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
        return;
    }
    if (!mustPidBeRecomputed()) {
        pidMotion->computationValues.detectedMotionType = DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS;
        return;
    }
    // Here, we must recompute pid
    float pidTime = (float) getPidTime();
    pidMotion->computationValues.pidTime = pidTime;

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
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);
    float leftMotorSpeed = computeLeft(thetaCurrentValues->u, alphaCurrentValues->u);
    float rightMotorSpeed = computeRight(thetaCurrentValues->u, alphaCurrentValues->u);
    setMotorSpeeds((int)leftMotorSpeed, (int) rightMotorSpeed);

    // If we maintain the position, we consider that we must do not check the end of motion (next paragraph)
    /*
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    if (thetaInst->motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        pidMotion->computationValues.detectedMotionType = DETECTED_MOTION_TYPE_POSITION_TO_MAINTAIN;
        return;
    }
    */
    
    // Detection if the robot is blocked or not
    pidMotion->computationValues.detectedMotionType = isRobotBlocked(pidMotion, motionDefinition);
}
