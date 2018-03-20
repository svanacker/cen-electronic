#include <math.h>

#include "../pid.h"
#include "../pidComputationInstructionValues.h"
#include "../computer/pidComputer.h"
#include "../computer/simplePidComputer.h"
#include "../profile/pidMotionProfileComputer.h"

#include "../../../common/commons.h"
#include "../../../common/error/error.h"
#include "../../../common/math/cenMath.h"

#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../motion/position/coderErrorComputer.h"

#include "../../../motion/simple/simpleMotion.h"

void clearInitialSpeeds(PidMotion* pidMotion) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);

    // TODO : For continuous trajectory : to change
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);
    alphaCurrentValues->currentSpeed = 0.0f;
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    thetaCurrentValues->currentSpeed = 0.0f;
}

void computeMotionInstruction(MotionInstruction* inst) {
    if (inst->a != 0.0f) {
        // Time must be > 0
        // We compute the difference between initialSpeed and speed and apply the "a" factor
        inst->t1 = fabsf((inst->speed - inst->initialSpeed) / inst->a);
        // P1 = (t1 * (is + s) * 1/2
        inst->p1 = inst->t1 * (inst->initialSpeed + inst->speed) / 2.0f;

        // decelerationTime (time to go from speed to endSpeed)
        float decelerationTime = fabsf((inst->speed - inst->endSpeed ) / inst->a);
        float decelerationDistance = decelerationTime * (inst->speed + inst->endSpeed) / 2.0f;

        // Distance during constant speed (P1 -> P2) = totalDistance - accelerationDistance - decelerationDistance
        float distanceAtConstantSpeed = inst->nextPosition - inst->p1 - decelerationDistance;

        // We detects if we have time to reach maxSpeed
        // we detect if the sign of speed is inverse to distanceAtConstantSpeed
        if (inst->speed * distanceAtConstantSpeed > 0) {
            inst->profileType = PROFILE_TYPE_TRAPEZE;
            inst->speedMax = inst->speed;
            // T = D / V
            inst->t2 = inst->t1 + fabsf(distanceAtConstantSpeed / inst->speed);
            inst->p2 = inst->p1 + distanceAtConstantSpeed;
        }        
        else {
            // the p1 position is greater than the final Position / 2 => TRIANGLE : we do not reach the max speed
            inst->profileType = PROFILE_TYPE_TRIANGLE;
            float numerator = fabsf(distanceAtConstantSpeed)*(inst->initialSpeed + inst->endSpeed)
                             + inst->speed * (2.0f * inst->nextPosition - inst->t1 * inst->initialSpeed - decelerationTime * inst->endSpeed);
            inst->speedMax = (float) (sqrt(fabsf(numerator) / (inst->t1 + decelerationTime)));
            // speedmax must be of the same sign of speed, and sqrt always returns a value > 0    
            if (inst->speedMax * inst->speed < 0) {
                inst->speedMax = -inst->speedMax;
            }
            // recompute t1/p1 with speedMax
            inst->t1 = fabsf((inst->initialSpeed - inst->speedMax) / inst->a);
            inst->p1 = (inst->initialSpeed * inst->t1) + (inst->a * inst->t1 * inst->t1) / 2.0f;

            inst->t2 = inst->t1;
            inst->p2 = inst->p1;

            decelerationTime = fabsf((inst->speedMax - inst->endSpeed ) / inst->a);
        }
        // In every case
        // inst->nextPosition = p3
        inst->t3 = inst->t2 + decelerationTime;

    } else {
        inst->profileType = PROFILE_TYPE_TRAPEZE;
        // profile "don't move"
        inst->t1 = 0;
        inst->t2 = 0;
        inst->t3 = 0;
        inst->p1 = 0;
        inst->p2 = 0;
    }
}

void setNextPosition(PidMotionDefinition* motionDefinition, 
		enum InstructionType instructionType,
        enum MotionParameterType motionParameterType,
        float pNextPosition,
        float pa,
        float pSpeed) {
	if (motionDefinition == NULL) {
		writeError(MOTION_DEFINITION_NULL);
		return;
	}
    MotionInstruction* localInst = &(motionDefinition->inst[instructionType]);

    localInst->nextPosition = pNextPosition;
    localInst->motionParameterType = motionParameterType;
    localInst->initialPidType = getPidType(motionParameterType, instructionType);

    if (pNextPosition > 0.001f) {
        localInst->a = pa;
        localInst->speed = pSpeed;
    } 
    // Acceleration and speed becomes negative
    else if (pNextPosition < -0.001f) {
        localInst->a = -pa;
        localInst->speed = -pSpeed;
    } 
    // pNextPosition == 0.0f Don't change the position
    else {
        if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
            localInst->a = pa;
            localInst->speed = pSpeed;
        } else {
            // Slavery free
            localInst->a = 0.0f;
            localInst->speed = 0.0f;
        }
    }
    computeMotionInstruction(localInst);
    
    // When using classic motion, we compute a U value with alpha/theta (2 main parameters), and not with spline (3 values)
    motionDefinition->computeU = &simpleMotionUCompute;
}

