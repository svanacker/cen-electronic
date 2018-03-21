#include "motionEndDetectionStatusUpdater.h"

#include <math.h>

#include "../../../robot/kinematics/robotKinematics.h"

#include "../pidComputationInstructionValues.h"
#include "../motionInstruction.h"
#include "../pidMotion.h"

#define ACCELERATION_TOO_HIGH_THRESHOLD_FACTOR    5.0f
#define SPEED_TOO_LOW_THRESHOLD_FACTOR            5.0f
#define U_TOO_HIGH_THRESHOLD_FACTOR               5.0f

// MIN / MAX VALUE

// In mm / sec
#define SPEED_MIN_THRESHOLD                       10.0f
// U is between 0 and 255 (or superior, but corresponding to max value)
#define U_MIN_THRESHOLD                           10.0f

/**
 * Update the status of the currentValues for the detection of an acceleration too high
 */
void updateEndDetectionStatusRegisterAccelerationTooHigh (MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absCurrentAcceleration = fabsf(currentValues->currentAcceleration);

    RobotKinematics* robotKinematics = getRobotKinematics();
    // Avoid to detect too high acceleration / deceleration
    float maxAcceleration = getRobotAccelerationMaxMillimeterBySecondSquare(robotKinematics);

    // Result : we must compare absNormalAcceleration with maxAcceleration of the robot and not normal Acceleration, because
    // when we deal with Trapeze motion, there is a moment in which the robot has a normal acceleration of 0 (constant speed)
    // A shock occured when acceleration / deceleration is much higher than the motor capacity / torque
    currentValues->status.absAccelerationTooHighThanExpected = absCurrentAcceleration >= (maxAcceleration * ACCELERATION_TOO_HIGH_THRESHOLD_FACTOR);
}

/**
* Update the status of the currentValues for the detection of a speed too low compared to the expected speed
*/
void updateEndDetectionStatusRegisterSpeedTooLow(MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absNormalSpeed = fabsf(currentValues->normalSpeed);
    if (absNormalSpeed < SPEED_MIN_THRESHOLD) {
        currentValues->status.absSpeedTooLowThanExpected = false;
        return;
    }

    float absCurrentSpeed = fabsf(currentValues->currentSpeed);

    // Result
    currentValues->status.absSpeedTooLowThanExpected = (absCurrentSpeed * SPEED_TOO_LOW_THRESHOLD_FACTOR) <= absNormalSpeed;
}

/**
* Update the status of the currentValues for the detection of a u too high compared to the expected speed.
*/
void updateEndDetectionStatusRegisterUTooHigh(MotionInstruction* motionInstruction, PidComputationInstructionValues* currentValues) {
    float absNormalU = fabsf(currentValues->normalU);
    if (absNormalU < U_MIN_THRESHOLD) {
        currentValues->status.absUTooHighThanExpected = false;
        return;
    }
    float absCurrentU = fabsf(currentValues->u);

    // Result
    currentValues->status.absUTooHighThanExpected = absCurrentU > (absNormalU * U_TOO_HIGH_THRESHOLD_FACTOR);
}

void updateEndDetectionStatusRegister(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);

    MotionInstruction* thetaMotionInstruction = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaMotionInstruction = &(motionDefinition->inst[ALPHA]);

    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    // Acceleration too high
    updateEndDetectionStatusRegisterAccelerationTooHigh(thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterAccelerationTooHigh(alphaMotionInstruction, alphaCurrentValues);

    // Speed too slow
    updateEndDetectionStatusRegisterSpeedTooLow(thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterSpeedTooLow(alphaMotionInstruction, alphaCurrentValues);

    // U too high
    updateEndDetectionStatusRegisterUTooHigh(thetaMotionInstruction, thetaCurrentValues);
    updateEndDetectionStatusRegisterUTooHigh(alphaMotionInstruction, alphaCurrentValues);
}