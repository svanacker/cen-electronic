#include "bsplineMotion.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../../common/commons.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../parameters/motionParameterType.h"
#include "../parameters/motionParameter.h"
#include "../parameters/motionPersistence.h"

#include "../extended/bsplineDebug.h"

#include "../pid/detectedMotionType.h"
#include "../pid/pid.h"
#include "../pid/pidMotion.h"
#include "../pid/pidType.h"
#include "../pid/pidDebug.h"
#include "../pid/alphaTheta.h"
#include "../pid/profile/pidMotionProfileComputer.h"
#include "../pid/computer/bSplinePidComputer.h"

#include "../position/coders.h"
#include "../position/trajectory.h"

#include "../../device/motor/pwmMotor.h"
#include "../../device/motion/simple/motionDevice.h"

#include "../../main/motorboard/motorBoard.h"

#include "../../robot/kinematics/robotKinematics.h"

/**
 * Go to a position;
 */
void gotoPosition(float left, float right, float a, float speed) {

    // Update trajectory before clearing coders
    updateTrajectory();

    updateTrajectoryAndClearCoders();

    // resets the time
    clearPidTime();

    // determine the type of motion
    enum MotionParameterType motionParameterType = getMotionParameterType(left, right);
    // determine the pidType to execute motionParameterType
    enum PidType pidType = getPidType(motionParameterType);

    // Alpha / Theta
    float theta = computeTheta(left, right);
    float alpha = computeAlpha(left, right);
    setNextPosition(THETA, motionParameterType, pidType, theta, (float) a, (float) speed);
    setNextPosition(ALPHA, motionParameterType, pidType, alpha, (float) a, (float) speed);

    PidMotion* pidMotion = getPidMotion();
    PidMotionDefinition* pidMotionDefinition = &(pidMotion->currentMotionDefinition);
    OutputStream* outputStream = getDebugOutputStreamLogger();
	printInst(outputStream, &(pidMotionDefinition->inst[THETA]));
    printInst(outputStream, &(pidMotionDefinition->inst[ALPHA]));

    // Indicates that the robot must reach the position
    setMustReachPosition(true);
}

/**
* @private
*/
void updateSimpleSplineWithDistance(float destX, float destY, 
                                    float destAngle, 
                                    float distance1, float distance2, 
                                    unsigned char accelerationFactor, unsigned char speedFactor,
                                    bool relative) {

    /*
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDecf(outputStream, "destX=", destX);
    appendStringAndDecf(outputStream, ",destY=", destY);
    appendStringAndDecf(outputStream, ",destAngle=", destAngle);
    appendStringAndDecf(outputStream, ",dist1=", distance1);
    appendStringAndDecf(outputStream, ",dist2=", distance2);
    */    

    // If the distance of the control point is negative, we considerer that we go
    // back
    bool backward = distance1 < 0.0f;

	RobotKinematics* robotKinematics = getRobotKinematics();
	float wheelAverageLength = robotKinematics->wheelAverageLengthForOnePulse;
    
    /*
    appendString(outputStream, ",rel=");
    appendbool(outputStream, relative);
    appendString(outputStream, ",backward=");
    appendbool(outputStream, backward);
    */    

    Position* position = getPosition();
    // scale coordinates
    float x = position->pos.x;
    float y = position->pos.y;
    float a = position->orientation;
	float xScaled = x / wheelAverageLength;
	float yScaled = y / wheelAverageLength;

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

    BSplineCurve* curve = &(getPidMotion()->currentMotionDefinition.curve);

    // Update the bspline curve
    // P0
    resetBSplineCurve(curve, xScaled, yScaled, backward);
    curve->accelerationFactor = accelerationFactor;
    curve->speedFactor = speedFactor;

    // P1
    Point* point = &(curve->p1);
    // P1 along x axis
    point->x = (x + dca1);
    point->y = (y + dsa1);
	scale(point, wheelAverageLength);
    
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
    // Scale points
	scale(&(curve->p2), wheelAverageLength);
	scale(&(curve->p3), wheelAverageLength);

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
 * Goto a position from the current position, with a certain distance to do the angle
 */
void gotoSimpleSpline(float destX, float destY,
                      float destAngle, 
                      float controlPointDistance1, float controlPointDistance2,
                      unsigned int accelerationFactor, unsigned int speedFactor,
                      bool relative) {
    updateSimpleSplineWithDistance(destX, destY,
                                    destAngle,
                                    controlPointDistance1, controlPointDistance2,
                                    accelerationFactor, speedFactor,
                                    relative);
    OutputStream* outputStream = getDebugOutputStreamLogger();
    println(outputStream);

    gotoSpline();
}

/**
* Computes the best speed for the bspline, and take into consideration the derivative value (to avoid a too big speed)
*/
float computeBestSpeedForBSpline(BSplineCurve* curve, float speed) {
    float result = (speed * curve->speedFactor) / MOTION_SPEED_FACTOR_MAX;
    
    return result;
}

/**
* Computes the best acceleration for the bspline, and take into consideration the derivative value (to avoid a too big acceleration)
*/
float computeBestAccelerationForBSpline(BSplineCurve* curve, float a) {
    float result = (a * curve->accelerationFactor) / MOTION_ACCELERATION_FACTOR_MAX;
    return result;
}

/**
 * Goto a position using a spline.
 */
void gotoSpline() {
    OutputStream* outputStream = getDebugOutputStreamLogger();

    BSplineCurve* curve = &(getPidMotion()->currentMotionDefinition.curve);
	RobotKinematics* robotKinematics = getRobotKinematics();
	float wheelAverageLength = robotKinematics->wheelAverageLengthForOnePulse;

	writeBSplineControlPoints(outputStream, curve, wheelAverageLength);

    // Update trajectory before clearing coders
    updateTrajectory();

    updateTrajectoryAndClearCoders();

    float curveLength = computeBSplineArcLength(curve, BSPLINE_TIME_INCREMENT);
    
    // debug
    // writeBSpline(getDebugOutputStreamLogger(), curve);

    // resets the time
    clearPidTime();

    // determine the type of motion
    enum MotionParameterType motionParameterType = getMotionParameterType(curveLength, curveLength);
    // determine the pidType to execute motionType
    enum PidType pidType = getPidType(motionParameterType);

    // do as if we follow a straight line
    MotionParameter* motionParameter = getDefaultMotionParameters(MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD);
    float bestA = computeBestAccelerationForBSpline(curve, motionParameter->a);
    float bestSpeed = computeBestSpeedForBSpline(curve, motionParameter->speed);

    setNextPosition(THETA, motionParameterType, pidType, curveLength, bestA, bestSpeed);
    setNextPosition(ALPHA, motionParameterType, pidType, 0.0f, motionParameter->a, motionParameter->speed);

    getPidMotion()->currentMotionDefinition.computeU = &bSplineMotionUCompute;

    // Indicates that the robot must reach the position
    setMustReachPosition(true);
}

