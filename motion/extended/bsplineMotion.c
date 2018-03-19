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

#include "../extended/bsplineDebug.h"

#include "../pid/pid.h"
#include "../pid/pidMotion.h"
#include "../pid/pidDebug.h"
#include "../pid/alphaTheta.h"
#include "../pid/profile/pidMotionProfileComputer.h"
#include "../pid/computer/bSplinePidComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../device/motor/pwmMotor.h"

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

    // If the distance of the control point is negative, we considerer that we go
    // back
    bool backward = distance1 < 0.0f;

    Position* position = getPosition();
    // scale coordinates
    float x = position->pos.x;
    float y = position->pos.y;
    float a = position->orientation;

    // For P0-P1
    float c1 = cosf(a);
    float s1 = sinf(a);

    float dca1 = (distance1 * c1);
    float dsa1 = (distance1 * s1);

    // For P2-P3
    float c2 = cosf(destAngle);
    float s2 = sinf(destAngle);

    float dca2 = (distance2 * c2);
    float dsa2 = (distance2 * s2);

    // Update the bspline curve
    // P0
    resetBSplineCurve(curve, x, y, backward);
    curve->accelerationFactor = accelerationFactor;
    curve->speedFactor = speedFactor;

    // P1
    Point* point = &(curve->p1);
    // P1 along x axis
    point->x = (x + dca1);
    point->y = (y + dsa1);
    
    if (relative) {    

        // P2
        point = &(curve->p2);
        //rotate(point, a, (destX - x - dca2), (destY - y - dsa2));
        rotate(point, a, (destX - dca2), (destY - dsa2));
        point->x += x;
        point->y += y;

        // P3
        point = &(curve->p3);
        //rotate(point, a, (destX - x), (destY - y));
        rotate(point, a, (destX), (destY));
        point->x += x;
        point->y += y;
    }
    else {
        // P2
        point = &(curve->p2);
        point->x = (destX - dca2);
        point->y = (destY - dsa2);

        // P3
        point = &(curve->p3);
        point->x = destX;
        point->y = destY;
    }
    computeBSplineArcLength(curve, BSPLINE_TIME_INCREMENT);
    /*
    curve->p1->x = (x  +  distance1        * c) / WHEEL_AVERAGE_LENGTH;
    curve->p1->y = (y  +  distance1     * s) / WHEEL_AVERAGE_LENGTH,
    
    curve->p2->x = (x + (destX - dca2)  * c - (destY - dsa2)  * s) / WHEEL_AVERAGE_LENGTH;
    curve->p2->y = (y + (destX - dca2)  * s + (destY - dsa2)  * c) / WHEEL_AVERAGE_LENGTH;
    
    curve->p3->x = (x +    destX        * c -      destY      * s) / WHEEL_AVERAGE_LENGTH;
    curve->p3->y = (y +    destX         * s +      destY       * c) / WHEEL_AVERAGE_LENGTH;
    */
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

