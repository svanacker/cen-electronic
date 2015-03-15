#include <math.h>

#include "bSplinePidComputer.h"

#include "pidComputer.h"
#include "../pidComputationValues.h"
#include "../pid.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../motionInstruction.h"
#include "../pidMotionDefinition.h"
#include "../pidCurrentValues.h"

#include "../../../common/2d/2d.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../motion/extended/bspline.h"

#include "../../../motion/pid/computer/pidComputer.h"
#include "../../../motion/position/trajectory.h"

#include "../../../robot/kinematics/robotKinematics.h"

void bSplineMotionUCompute(void) {
    PidMotion* pidMotion = getPidMotion();
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);

    BSplineCurve* curve = &(motionDefinition->curve);
    float pidTime = computationValues->pidTime;
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    float normalPosition = computeNormalPosition(thetaInst, pidTime);

    // Computes the time of the bSpline in [0.00, 1.00]
    float bSplineTime = computeBSplineTimeAtDistance(curve, normalPosition);

    Point normalPoint;

    // Computes the normal Point where the robot must be
    computeBSplinePoint(curve, bSplineTime, &normalPoint);
    // Convert normalPoint into mm space
    RobotKinematics* robotKinematics = getRobotKinematics();
    float wheelAverageLength = robotKinematics->wheelAverageLengthForOnePulse;

    normalPoint.x = normalPoint.x * wheelAverageLength;
    normalPoint.y = normalPoint.y * wheelAverageLength;

    Position* robotPosition = getPosition();
    Point robotPoint = robotPosition->pos;

    // GET PID
    unsigned pidIndex = getIndexOfPid(THETA, thetaInst->pidType);
    unsigned char rollingTestMode = getRollingTestMode();
    PidParameter* pidParameter = getPidParameter(pidIndex, rollingTestMode);

    // ALPHA
    PidMotionError* alphaMotionError = &(computationValues->err[ALPHA]);    

    float normalAlpha = computeBSplineOrientationWithDerivative(curve, bSplineTime);
    float realAlpha = robotPosition->orientation;
    
    // backward management
    if (curve->backward) {
        realAlpha += PI;
    }

    float alphaError = (normalAlpha - realAlpha);
    // restriction to [-PI, PI]
    alphaError = mod2PI(alphaError);

    // Convert angleError into pulse equivalent
    float wheelsDistanceFromCenter = getWheelsDistanceFromCenter(robotKinematics);
    float alphaPulseError = (-wheelsDistanceFromCenter * alphaError) / wheelAverageLength;

    // THETA
    PidMotionError* thetaMotionError = &(computationValues->err[THETA]);

    // thetaError must be in Pulse and not in MM
    float thetaError = distanceBetweenPoints(&robotPoint, &normalPoint) / wheelAverageLength;
    float thetaAngle = angleOfVector(&robotPoint, &normalPoint);
    if (curve->backward) {
        thetaAngle += PI;
    }
    float alphaAndThetaDiff = thetaAngle - normalAlpha;

    // restriction to [-PI, PI]
    alphaAndThetaDiff = mod2PI(alphaAndThetaDiff);

    float cosAlphaAndThetaDiff = cosf(alphaAndThetaDiff);
    float thetaErrorWithCos = thetaError * cosAlphaAndThetaDiff;
    
    float normalSpeed = computeNormalSpeed(thetaInst, pidTime);
    float thetaU = computePidCorrection(thetaMotionError, pidParameter, normalSpeed, thetaErrorWithCos);

    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    thetaCurrentValues->u = thetaU;

    // ALPHA CORRECTION
    alphaPulseError *= 5.0f;
    float alphaCorrection = -0.00050f * normalSpeed * thetaError * (alphaAndThetaDiff);
    // float alphaCorrection = 0.0f;
    alphaPulseError += alphaCorrection;
    float alphaU = computePidCorrection(alphaMotionError, pidParameter, 0, alphaPulseError);

    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);
    alphaCurrentValues->u = alphaU;
    
    // LOG
    OutputStream* out = getDebugOutputStreamLogger();
    
    // appendStringAndDecf(out, "pt=", pidTime);

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
}
