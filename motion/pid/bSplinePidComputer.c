#include <math.h>

#include "bSplinePidComputer.h"

#include "pidComputer.h"
#include "pid.h"

#include "../../common/2d/2d.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../motion/extended/bspline.h"

#include "../../motion/pid/pidComputer.h"
#include "../../motion/position/trajectory.h"

#include "../../robot/robotConstants.h"

void bSplineMotionUCompute() {
    PidMotion* pidMotion = getPidMotion();
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);

    BSplineCurve* curve = &(motionDefinition->curve);
    float pidTime = computationValues->pidTime;
    MotionInstruction* thetaInst = &(motionDefinition->inst[INSTRUCTION_THETA_INDEX]);
    float normalPosition = computeNormalPosition(thetaInst, pidTime);

    // Computes the time of the bSpline in [0.00, 1.00]
    float bSplineTime = computeBSplineTimeAtDistance(curve, normalPosition);

    Point normalPoint;

    // Computes the normal Point where the robot must be
    computeBSplinePoint(curve, bSplineTime, &normalPoint);
    // Convert normalPoint into mm space
    normalPoint.x = normalPoint.x * WHEEL_AVERAGE_LENGTH;
    normalPoint.y = normalPoint.y * WHEEL_AVERAGE_LENGTH;

    Position* robotPosition = getPosition();
    Point robotPoint = robotPosition->pos;

    // GET PID
    unsigned pidIndex = getIndexOfPid(INSTRUCTION_THETA_INDEX, thetaInst->pidType);
    unsigned char rollingTestMode = getRollingTestMode();
    Pid* pid = getPID(pidIndex, rollingTestMode);

    // ALPHA
    MotionError* alphaMotionError = &(computationValues->err[INSTRUCTION_ALPHA_INDEX]);    

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
    float alphaPulseError = (- WHEELS_DISTANCE_FROM_CENTER * alphaError) / WHEEL_AVERAGE_LENGTH;

    // THETA
    MotionError* thetaMotionError = &(computationValues->err[INSTRUCTION_THETA_INDEX]);

    // thetaError must be in Pulse and not in MM
    float thetaError = distanceBetweenPoints(&robotPoint, &normalPoint) /  WHEEL_AVERAGE_LENGTH;
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
    float thetaU = computePidCorrection(thetaMotionError, pid, normalSpeed, thetaErrorWithCos);

    Motion* thetaMotion = &(computationValues->motion[INSTRUCTION_THETA_INDEX]);
    thetaMotion->u = thetaU;

    // ALPHA CORRECTION
    alphaPulseError *= 5.0f;
    float alphaCorrection = -0.00050f * normalSpeed * thetaError * (alphaAndThetaDiff);
    // float alphaCorrection = 0.0f;
    alphaPulseError += alphaCorrection;
    float alphaU = computePidCorrection(alphaMotionError, pid, 0, alphaPulseError);

    Motion* alphaMotion = &(computationValues->motion[INSTRUCTION_ALPHA_INDEX]);
    alphaMotion->u = alphaU;
    
    // LOG
    /*
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
    */
}
