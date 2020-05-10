#include "motionEndDetectionStatusUpdater.h"

#include <math.h>
#include "../../../common/math/cenMath.h"

#include "../../../robot/kinematics/robotKinematics.h"
#include "../../pid/endDetection/parameters/motionEndDetectionParameter.h"
#include "../pidComputationInstructionValues.h"
#include "../motionInstruction.h"
#include "../pidMotion.h"

/**
 * Update the status of the currentValues for the detection of an acceleration too high
 */
void updateEndDetectionStatusRegisterAccelerationTooHigh(MotionEndDetectionParameter* endDetectionParameter, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absCurrentAcceleration = fabsf(currentValues->currentAcceleration);

    RobotKinematics* robotKinematics = getRobotKinematics();
    // Avoid to detect too high acceleration / deceleration
    float maxAcceleration = getRobotAccelerationMaxMillimeterBySecondSquare(robotKinematics);

    // Result : we must compare absNormalAcceleration with maxAcceleration of the robot and not normal Acceleration, because
    // when we deal with Trapeze motion, there is a moment in which the robot has a normal acceleration of 0 (constant speed)
    // A shock occured when acceleration / deceleration is much higher than the motor capacity / torque
    currentValues->status.absAccelerationTooHighThanExpected = absCurrentAcceleration >= (maxAcceleration * endDetectionParameter->accelerationTooHighTresholdFactor);
}

/**
 * Update the status of the currentValues for the detection of a speed too low compared to the expected speed
 */
void updateEndDetectionStatusRegisterSpeedTooLow(MotionEndDetectionParameter* endDetectionParameter, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absNormalSpeed = fabsf(currentValues->normalSpeed);
    if (absNormalSpeed < endDetectionParameter->speedMinThreshold) {
        currentValues->status.absSpeedTooLowThanExpected = false;
        return;
    }

    float absCurrentSpeed = fabsf(currentValues->currentSpeed);

    // Result
    currentValues->status.absSpeedTooLowThanExpected = (absCurrentSpeed * endDetectionParameter->speedTooLowThresholdFactor) <= absNormalSpeed;
}

/**
 * Update the status of the currentValues for the detection of a u too high compared to the expected speed.
 */
void updateEndDetectionStatusRegisterUTooHigh(MotionEndDetectionParameter* endDetectionParameter, MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absNormalU = fabsf(currentValues->normalU);
    // When we go very slowly, we don't detect that U is too much
    if (absNormalU < endDetectionParameter->uMinThresholdValue) {
        currentValues->status.absUTooHighThanExpected = false;
        return;
    }
    float absCurrentU = fabsf(currentValues->u);

    // Result
    if (motionInstruction->speed != 0.0f) {
        float factor = 1.0f + fabsf(endDetectionParameter->uTooHighTresholdFactor / (logf(E_CONST + fabsf(currentValues->normalSpeed / 10.0f))));
        currentValues->status.absUTooHighThanExpected = absCurrentU > (absNormalU * factor);
    }
    else {
        currentValues->status.absUTooHighThanExpected = false;
    }
}

void updateEndDetectionStatusRegister(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionEndDetectionParameter* endDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    PidComputationValues* computationValues = &(pidMotion->computationValues);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    // Acceleration too high
    updateEndDetectionStatusRegisterAccelerationTooHigh(endDetectionParameter, thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterAccelerationTooHigh(endDetectionParameter, alphaMotionInstruction, alphaCurrentValues);

    // Speed too slow
    updateEndDetectionStatusRegisterSpeedTooLow(endDetectionParameter, thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterSpeedTooLow(endDetectionParameter, alphaMotionInstruction, alphaCurrentValues);

    // U too high
    updateEndDetectionStatusRegisterUTooHigh(endDetectionParameter, thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterUTooHigh(endDetectionParameter, alphaMotionInstruction, alphaCurrentValues);
}