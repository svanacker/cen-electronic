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
 * Compute the Alpha part of the PID
 */
float bSplineMotionUComputeAlphaError(PidMotion* pidMotion, PidMotionDefinition* motionDefinition, Position* robotPosition, float bSplineTime) {
    PidParameter* alphaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_MAINTAIN_POSITION_INDEX);
    BSplineCurve* curve = &(motionDefinition->curve);
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    float pidTime = computationValues->pidTimeInSecond;

    // Real Alpha
    float realAlpha = robotPosition->orientation;

    // Normal Alpha
    float normalAlpha = computeBSplineOrientationWithDerivative(curve, bSplineTime);
    // backward management
    if (curve->backward) {
        normalAlpha += PI;
        normalAlpha = mod2PI(normalAlpha);
    }

    float alphaErrorInRadian = (normalAlpha - realAlpha);
    // restriction to [-PI, PI]
    alphaErrorInRadian = mod2PI(alphaErrorInRadian);

    // Convert angleError into pulse equivalent
    RobotKinematics* robotKinematics = getRobotKinematics();

    // Convert the alpha error into a "distance" equivalence
    // TODO : To review
    float alphaError = rotationInRadiansToRealDistanceForLeftWheel(robotKinematics, alphaErrorInRadian);

    PidComputationInstructionValues* alphaValues = &(computationValues->values[ALPHA]);

    // TODO : To check : not really true if the curve is strong !!
    float alphaNormalSpeed = 0.0f;
    alphaValues->u = computePidCorrection(alphaValues, alphaPidParameter, alphaNormalSpeed, alphaError);
    // alphaValues->u = 0.0f;
    PidComputationInstructionValues* alphaComputationInstructionValues = &(computationValues->values[ALPHA]);
    alphaComputationInstructionValues->error = alphaError;
    alphaComputationInstructionValues->normalSpeed = alphaNormalSpeed;
    alphaComputationInstructionValues->normalPosition = normalAlpha;
    storePidComputationInstructionValueHistory(alphaComputationInstructionValues, pidTime);

    return normalAlpha;
}

float bSplineMotionUComputeThetaError(PidMotion* pidMotion,
                                      PidMotionDefinition* motionDefinition,
                                      Position* robotPosition,
                                      float bSplineTime, 
                                      float normalAlpha) {
    BSplineCurve* curve = &(motionDefinition->curve);
    PidParameter* thetaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_GO_INDEX);
    MotionInstruction* thetaInstruction = &(motionDefinition->inst[THETA]);
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    float pidTime = computationValues->pidTimeInSecond;
    PidComputationInstructionValues* thetaValues = &(computationValues->values[THETA]);

    Point normalPoint;
    // Computes the normal Point where the robot must be
    computeBSplinePoint(curve, bSplineTime, &normalPoint);

    Point robotPoint = robotPosition->pos;
    // This value is always positive (distance), so we must know if the robot is in front of or in back of this distance
    float distanceRealAndNormalPoint = distanceBetweenPoints(&robotPoint, &normalPoint);
    // Angle between the robot and the point where it should be
    float angleRealAndNormalOrientation = angleOfVector(&robotPoint, &normalPoint);
    // Computes the real thetaError by managing different angles

    /*
    if (curve->backward) {
        angleRealAndNormalOrientation += PI;
    }
    */
    float alphaAndThetaDiff = angleRealAndNormalOrientation - normalAlpha;

    // restriction to [-PI, PI]
    alphaAndThetaDiff = mod2PI(alphaAndThetaDiff);

    float cosAlphaAndThetaDiff = cosf(alphaAndThetaDiff);
    float thetaError = distanceRealAndNormalPoint * cosAlphaAndThetaDiff;

    float normalPosition = computeNormalPosition(thetaInstruction, pidTime);
    float thetaNormalSpeed = computeNormalSpeed(thetaInstruction, pidTime);
    thetaValues->u = computePidCorrection(thetaValues, thetaPidParameter, thetaNormalSpeed, thetaError);

    // For history
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

    // ALPHA CORRECTION
    Position* robotPosition = getPosition();
    float realAlpha = robotPosition->orientation;
    float normalAlpha = bSplineMotionUComputeAlphaError(pidMotion, motionDefinition, robotPosition, bSplineTime);

    // THETA
    float thetaError = bSplineMotionUComputeThetaError(pidMotion, motionDefinition, robotPosition, bSplineTime, normalAlpha);

    // ALPHA/THETA CORRECTION
    // TODO : Introduce Parameters stored in Eeprom !
    /* TODO 
    alphaPulseError *= 5.0f;
    float alphaCorrection = -0.00050f * normalSpeed * thetaError * (alphaAndThetaDiff);
    // float alphaCorrection = 0.0f;
    alphaPulseError += alphaCorrection;
    */
}
