#include "pidPc.h"

#include "../../../motion/simulation/motionSimulation.h"

#include "../../../motion/pid/alphaTheta.h"
#include "../../../motion/pid/computer/pidComputer.h"

#include "../../../motion/position/coderType.h"
#include "../../../motion/position/coders.h"

/**
* @private
*/
void simulateCurrentPositionReachIfNeeded(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
	MotionSimulationParameter* motionSimulationParameter = getMotionSimulationParameter();
	if (motionSimulationParameter->simulateCoders) {
		MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
		MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

		float pidTime = pidMotion->computationValues.pidTime;

		float normalThetaPosition = computeNormalPosition(thetaInst, pidTime);
		float normalAlphaPosition = computeNormalPosition(alphaInst, pidTime);

		float normalLeftCoderValue = computeLeft(normalThetaPosition, normalAlphaPosition);
		float normalRightCoderValue = computeRight(normalThetaPosition, normalAlphaPosition);

		setCoderValue(CODER_LEFT, (long)normalLeftCoderValue);
		setCoderValue(CODER_RIGHT, (long)normalRightCoderValue);
	}
}

