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
float bSplineMotionUComputeAlphaError(float normalAlpha, float realAlpha, bool backward) {
    // backward management
    if (backward) {
        realAlpha += PI;
    }
    float alphaErrorInRadian = (normalAlpha - realAlpha);
    // restriction to [-PI, PI]
    alphaErrorInRadian = mod2PI(alphaErrorInRadian);

    // Convert angleError into pulse equivalent
    RobotKinematics* robotKinematics = getRobotKinematics();

    // Convert the alpha error into a "distance" equivalence
    // TODO : To review
    float result = rotationInRadiansToRealDistanceForLeftWheel(robotKinematics, alphaErrorInRadian);
    return result;
}

float bSplineMotionUComputeThetaError(float distanceBetweenRealAndNormalPoint,
                                      float angleBetweenRealAndNormalOrientation,
                                      float normalAlpha, 
                                      bool backward) {
    if (backward) {
        angleBetweenRealAndNormalOrientation += PI;
    }
    float alphaAndThetaDiff = angleBetweenRealAndNormalOrientation - normalAlpha;

    // restriction to [-PI, PI]
    alphaAndThetaDiff = mod2PI(alphaAndThetaDiff);

    float cosAlphaAndThetaDiff = cosf(alphaAndThetaDiff);
    float result = distanceBetweenRealAndNormalPoint * cosAlphaAndThetaDiff;
    
    return result;
}

void bSplineMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    BSplineCurve* curve = &(motionDefinition->curve);
	PidComputationValues* computationValues = &(pidMotion->computationValues);
    float pidTime = computationValues->pidTimeInSecond;

    // Distance
    MotionInstruction* thetaInstruction = &(motionDefinition->inst[THETA]);
    float normalPosition = computeNormalPosition(thetaInstruction, pidTime);

    // Computes the time of the bSpline in [0.00, 1.00]
    float bSplineTime = computeBSplineTimeAtDistance(curve, normalPosition);

    Point normalPoint;

    // Computes the normal Point where the robot must be
    computeBSplinePoint(curve, bSplineTime, &normalPoint);

    Position* robotPosition = getPosition();
    Point robotPoint = robotPosition->pos;

    // GET PID to use
    PidParameter* thetaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_GO_INDEX);
    PidParameter* alphaPidParameter = getPidParameterByPidType(pidMotion, PID_TYPE_MAINTAIN_POSITION_INDEX);

    // ALPHA CORRECTION
    PidComputationInstructionValues* alphaValues = &(computationValues->values[ALPHA]);
    float normalAlpha = computeBSplineOrientationWithDerivative(curve, bSplineTime);
    float realAlpha = robotPosition->orientation;
    float alphaError = bSplineMotionUComputeAlphaError(normalAlpha, realAlpha, curve->backward);
    // TODO : To check : not really true if the curve is strong !!
    float alphaNormalSpeed = 0.0f;
    alphaValues->u = computePidCorrection(alphaValues, alphaPidParameter, alphaNormalSpeed, alphaError);
    
    PidComputationInstructionValues* alphaComputationInstructionValues = &(computationValues->values[ALPHA]);
    alphaComputationInstructionValues->error = alphaError;
    alphaComputationInstructionValues->normalSpeed = alphaNormalSpeed;
    alphaComputationInstructionValues->normalPosition = normalAlpha;
    storePidComputationInstructionValueHistory(alphaComputationInstructionValues, pidTime);

    // THETA
    PidComputationInstructionValues* thetaValues = &(computationValues->values[THETA]);
    // This value is always positive (distance), so we must know if the robot is in front of or in back of this distance
    float distanceRealAndNormalPoint = distanceBetweenPoints(&robotPoint, &normalPoint);
    // Angle between the robot and the point where it should be
    float angleRealAndNormalOrientation = angleOfVector(&robotPoint, &normalPoint);
    // Computes the real thetaError by managing different angles
    float thetaError = bSplineMotionUComputeThetaError(distanceRealAndNormalPoint, angleRealAndNormalOrientation, normalAlpha, curve->backward);
    float thetaNormalSpeed = computeNormalSpeed(thetaInstruction, pidTime);
    thetaValues->u = computePidCorrection(thetaValues, thetaPidParameter, thetaNormalSpeed, thetaError);
    // For history
    PidComputationInstructionValues* thetaComputationInstructionValues = &(computationValues->values[THETA]);
    thetaComputationInstructionValues->error = thetaError;
    thetaComputationInstructionValues->normalSpeed = thetaNormalSpeed;
    storePidComputationInstructionValueHistory(thetaComputationInstructionValues, pidTime);

    // ALPHA/THETA CORRECTION
    // TODO : Introduce Parameters stored in Eeprom !
    /* TODO 
    alphaPulseError *= 5.0f;
    float alphaCorrection = -0.00050f * normalSpeed * thetaError * (alphaAndThetaDiff);
    // float alphaCorrection = 0.0f;
    alphaPulseError += alphaCorrection;
    */
    // LOG
    // OutputStream* out = getDebugOutputStreamLogger();
    
    // appendStringAndDecf(out, "pt=", pidTime);
	/*
    appendStringAndDecf(out, ",t=", bSplineTime);

    // Normal Position
    appendStringAndDecf(out, ",nx=", normalPoint.x);
    appendStringAndDecf(out, ",ny=", normalPoint.y);
    appendStringAndDecf(out, ",na=", normalAlpha);

    // Real position

    appendStringAndDecf(out, ",rx=", robotPoint.x);
    appendStringAndDecf(out, ",ry=", robotPoint.y);
    appendStringAndDecf(out, ",ra=", realAlpha);

    // ALPHA
    appendStringAndDecf(out, ",ta=", thetaAngle);
    appendStringAndDecf(out, ",ae=", alphaError);
    //appendStringAndDecf(out, ",atdiff=", alphaAndThetaDiff);
    //appendStringAndDecf(out, ",catdiff=", cosAlphaAndThetaDiff);
    appendStringAndDecf(out, ",au=", alphaU);
    appendStringAndDecf(out, ",ac=", alphaCorrection);

    // THETA

    // appendString(out, ",np=");
    // appendDecf(out, normalPosition);

    appendStringAndDecf(out, ",te=", thetaError);
    appendStringAndDecf(out, ",tec=", thetaErrorWithCos);
    appendStringAndDecf(out, ",tu=", thetaU);
    
    appendCRLF(out);
	*/
}
