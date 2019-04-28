#include "bsplineMotion.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../../common/io/outputStream.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../parameters/motionParameterType.h"
#include "../parameters/motionParameter.h"
#include "../parameters/motionParameterPersistence.h"

#include "../motionConstants.h"
#include "../extended/bsplineDebug.h"

#include "../pid/pid.h"
#include "../pid/pidMotion.h"
#include "../pid/pidDebug.h"
#include "../pid/alphaTheta.h"
#include "../pid/profile/pidMotionProfileComputer.h"
#include "../pid/computer/bSplinePidComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../robot/kinematics/robotKinematics.h"

/**
* @private
*/
void updateSimpleSplineWithDistance(BSplineCurve* curve,
									float destX, float destY, 
                                    float destAngle, 
                                    float distance1, float distance2, 
                                    float accelerationFactor, float speedFactor,
                                    bool relative) {

    Position* position = getPosition();

    parameterBSplineWithDistanceAndAngle(curve, position->pos.x, position->pos.y, position->orientation,
                                                destX, destY, destAngle,
                                                distance1, distance2,
                                                accelerationFactor, speedFactor,
                                                relative);
}

/**
* Computes the best speed for the bspline, and take into consideration the derivative value (to avoid a too big speed)
*/
float computeBestSpeedForBSpline(BSplineCurve* curve, float speed) {
    float result = (speed * curve->speedFactor) * MOTION_SPEED_FACTOR_MAX;
    
    return result;
}

/**
* Computes the best acceleration for the bspline, and take into consideration the derivative value (to avoid a too big acceleration)
*/
float computeBestAccelerationForBSpline(BSplineCurve* curve, float a) {
    float result = (a * curve->accelerationFactor) * MOTION_ACCELERATION_FACTOR_MAX;
    return result;
}

void gotoSpline(PidMotion* pidMotion,
					  float destX, float destY,
                      float destAngle, 
                      float controlPointDistance1, float controlPointDistance2,
                      float accelerationFactor, float speedFactor,
                      bool relative,
					  OutputStream* notificationOutputStream) {
    // Takes the new motion Definition to write
	PidMotionDefinition* motionDefinition = pidMotionGetNextToWritePidMotionDefinition(pidMotion);
    motionDefinition->notificationOutputStream = notificationOutputStream;
	motionDefinition->motionType = MOTION_TYPE_BSPLINE;
	BSplineCurve* curve = &(motionDefinition->curve);
    
    updateSimpleSplineWithDistance(curve,
									destX, destY,
                                    destAngle,
                                    controlPointDistance1, controlPointDistance2,
                                    accelerationFactor, speedFactor,
                                    relative);
	
    float nextPositionEquivalent = curve->curveLength;

    // determine the type of motion
    // TODO : Left and Right does not have the same speed
    enum MotionParameterType motionParameterType = getMotionParameterType(nextPositionEquivalent, nextPositionEquivalent);

    // do as if we follow a straight line for the speed / motion parameters
    MotionParameter* motionParameter = getMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    float bestA = computeBestAccelerationForBSpline(curve, motionParameter->a);
    float bestSpeed = computeBestSpeedForBSpline(curve, motionParameter->speed);

    setNextPosition(motionDefinition, THETA, motionParameterType, nextPositionEquivalent, bestA, bestSpeed);
    
    // Does nothing as we just use THETA in Spline Mode
    setNextPosition(motionDefinition, ALPHA, motionParameterType, 0.0f, motionParameter->a, motionParameter->speed);

	motionDefinition->computeU = &bSplineMotionUCompute;
    motionDefinition->state = PID_MOTION_DEFINITION_STATE_SET;
}

