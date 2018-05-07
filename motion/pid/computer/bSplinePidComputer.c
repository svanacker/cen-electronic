#include <math.h>
#include <stdbool.h>

#include "bSplinePidComputer.h"

#include "pidComputer.h"
#include "../pidComputationValues.h"
#include "../pid.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../motionInstruction.h"
#include "../pidComputationInstructionValues.h"

#include "../../../common/2d/2d.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../motion/extended/bspline.h"

#include "../../../motion/pid/computer/pidComputer.h"
#include "../../../motion/position/trajectory.h"

#include "../../../robot/kinematics/robotKinematics.h"

/**
 * @private
 * @param curve
 * @param bSplineTime
 * @return 
 */
float bSplineMotionGetNormalAlpha(BSplineCurve* curve, float bSplineTime) {
    // Normal Alpha
    float normalAlpha = computeBSplineOrientationWithDerivative(curve, bSplineTime);
    // backward management
    if (curve->backward) {
        normalAlpha += PI;
        normalAlpha = mod2PI(normalAlpha);
    }
    
    return normalAlpha;
}

float bSplineMotionComputeAlphaAndThetaDiff(Point* robotPoint, Point* normalPoint, float normalAlpha) {
    // Angle between the robot and the point where it should be
    float angleRealAndNormalOrientation = angleOfVector(robotPoint, normalPoint);
    // Computes the real thetaError by managing different angles

    /* TODO : Check if necessary
    if (curve->backward) {
        angleRealAndNormalOrientation += PI;
    }
    */
    float alphaAndThetaDiff = angleRealAndNormalOrientation - normalAlpha;

    // restriction to [-PI, PI]
    alphaAndThetaDiff = mod2PI(alphaAndThetaDiff);

    return alphaAndThetaDiff;
}


/**
 * @private
 * Compute the Alpha part of the PID
 */
float bSplineMotionUComputeAlphaError(PidMotion* pidMotion, BSplineCurve* curve, Position* robotPosition, float normalAlpha, float alphaAndThetaDiff, float distanceRealAndNormalPoint) {
    // Real Alpha
    float realAlpha = robotPosition->orientation;
    // Error
    float alphaErrorInRadian = (normalAlpha - realAlpha);
    // restriction to [-PI, PI]
    alphaErrorInRadian = mod2PI(alphaErrorInRadian);

    // Convert angleError into pulse equivalent
    RobotKinematics* robotKinematics = getRobotKinematics();

    // Convert the alpha error into a "distance" equivalence
    // TODO : To review
    float alphaDistanceEquivalentError = rotationInRadiansToRealDistanceForLeftWheel(robotKinematics, alphaErrorInRadian);
    
    // But it's not finished, because even if alphaError is equal to 0, and "theta" is OK, the risk is too
    // Follow a "parallel" curve to the right One
    // So we try to compute a complementary distance equivalent to the distance between this "parallel curve" (the normal curve)
    // and the robot curve
    float additionalError = -(sinf(alphaAndThetaDiff) * distanceRealAndNormalPoint);
    if (curve->backward) {
        alphaDistanceEquivalentError -= additionalError;  
    }
    else {
        alphaDistanceEquivalentError += additionalError;  
    }
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* alphaValues = &(computationValues->values[ALPHA]);

    // TODO : To check : not really true if the curve is strong !!
    float alphaNormalSpeed = 0.0f;
    // The PID Parameters used must be strong to keep the angle => We use PID_TYPE_MAINTAIN_POSITION_INDEX
    PidParameter* alphaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_MAINTAIN_POSITION_INDEX);
    alphaValues->u = computePidCorrection(alphaValues, alphaPidParameter, alphaNormalSpeed, alphaDistanceEquivalentError);
    
    // For History
    PidComputationInstructionValues* alphaComputationInstructionValues = &(computationValues->values[ALPHA]);
    alphaComputationInstructionValues->error = alphaDistanceEquivalentError;
    alphaComputationInstructionValues->normalSpeed = alphaNormalSpeed;
    alphaComputationInstructionValues->normalPosition = normalAlpha;
    float pidTime = computationValues->pidTimeInSecond;
    storePidComputationInstructionValueHistory(alphaComputationInstructionValues, pidTime);

    return normalAlpha;
}

/**
 * @private
 * Theta means distance management, but we need to have in mind that to know
 * if we are before (slower) or after (too quick) in terms of distance, we must
 * project the point perpendicular to the curve
 * The problem with that approach is that the robot could consider that everything
 * is ok if he is "parallel" to the curve.
 * @param pidMotion
 * @param motionDefinition
 * @param robotPosition
 * @param bSplineTime
 * @param normalAlpha
 * @return 
 */
float bSplineMotionUComputeThetaError(PidMotion* pidMotion,
                                      PidMotionDefinition* motionDefinition,
                                      float alphaAndThetaDiff,
                                      float distanceRealAndNormalPoint) {
    float cosAlphaAndThetaDiff = cosf(alphaAndThetaDiff);
    
    // We do the "projection" point to determine if we are the error only
    // the Distance error (theta Error))
    float thetaError = distanceRealAndNormalPoint * cosAlphaAndThetaDiff;

    // Compute the THETA PID with this data 
    MotionInstruction* thetaInstruction = &(motionDefinition->inst[THETA]);
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    float pidTime = computationValues->pidTimeInSecond;
    float normalPosition = computeNormalPosition(thetaInstruction, pidTime);
    float thetaNormalSpeed = computeNormalSpeed(thetaInstruction, pidTime);

    PidParameter* thetaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_GO_INDEX);
        
    // We take GO PID, because it's relative to a distance Management
    PidComputationInstructionValues* thetaValues = &(computationValues->values[THETA]);

    thetaValues->u = computePidCorrection(thetaValues, thetaPidParameter, thetaNormalSpeed, thetaError);

    // For history Management
    PidComputationInstructionValues* thetaComputationInstructionValues = &(computationValues->values[THETA]);
    thetaComputationInstructionValues->error = thetaError;
    thetaComputationInstructionValues->normalPosition = normalPosition;
    thetaComputationInstructionValues->normalSpeed = thetaNormalSpeed;
    storePidComputationInstructionValueHistory(thetaComputationInstructionValues, pidTime);

    return thetaError;
}

void bSplineMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    // Distance
    BSplineCurve* curve = &(motionDefinition->curve);
	PidComputationValues* computationValues = &(pidMotion->computationValues);
    float pidTime = computationValues->pidTimeInSecond;
    MotionInstruction* thetaInstruction = &(motionDefinition->inst[THETA]);
    float normalPosition = computeNormalPosition(thetaInstruction, pidTime);
    float normalDistance = fabsf(normalPosition);

    // Computes the time of the bSpline in [0.00, 1.00]
    float bSplineTime = computeBSplineTimeAtDistance(curve, normalDistance);

    Position* robotPosition = getPosition();
    
    Point* robotPoint = &(robotPosition->pos);
    // SOME PRELIMINARY COMPUTATION
    float normalAlpha = bSplineMotionGetNormalAlpha(curve, bSplineTime);
    Point normalPoint;
    // Computes the normal Point where the robot must be
    computeBSplinePoint(curve, bSplineTime, &normalPoint);
    // Compute a kind of "angle" between normal Point and robot Point
    float alphaAndThetaDiff = bSplineMotionComputeAlphaAndThetaDiff(robotPoint, &normalPoint, normalAlpha);
    // This value is always positive (distance), so we must know if the robot is in front of or in back of this distance
    float distanceRealAndNormalPoint = distanceBetweenPoints(robotPoint, &normalPoint);

    // ALPHA CORRECTION
    normalAlpha = bSplineMotionUComputeAlphaError(pidMotion, curve, robotPosition, normalAlpha, alphaAndThetaDiff, distanceRealAndNormalPoint);

    // THETA
    bSplineMotionUComputeThetaError(pidMotion, motionDefinition, alphaAndThetaDiff, distanceRealAndNormalPoint);
}
