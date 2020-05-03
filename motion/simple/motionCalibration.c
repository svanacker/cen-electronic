#include "motionCalibration.h"

#include "../../motion/motion.h"
#include "../../motion/motionConstants.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../common/math/cenMath.h"

// CALIBRATION

void squareCalibrationRotationLeft(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        rightSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    } else {
        leftSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
}

void squareCalibrationRotationRight(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        leftSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    } else {
        rightSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
}

void squareCalibrationSpline(PidMotion* pidMotion, bool inverse, float cp, float sourceX, float sourceY, float sourceAngleDegree, float destX, float destY, float targetAngleDegree, OutputStream* notificationOutputStream) {
    if (inverse) {
        gotoSpline(pidMotion, sourceX, -sourceY, -degToRad(sourceAngleDegree), destX, -destY, -degToRad(targetAngleDegree), cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
    else {
        gotoSpline(pidMotion, sourceX, sourceY, degToRad(sourceAngleDegree), destX, destY, degToRad(targetAngleDegree), cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
}

void squareCalibrationLine(PidMotion* pidMotion, float distanceMM, OutputStream* notificationOutputStream) {
    forwardSimpleMM(pidMotion, distanceMM, notificationOutputStream);
}

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    // left = 0 => inverse = true
    bool inverse = (type == 0);

    // Active the Motion Mode + to add several motion
    setMotionModeAdd(pidMotion);

    // Forward
    squareCalibrationLine(pidMotion, lengthInMM2, notificationOutputStream);

    // turn on right
    squareCalibrationRotationRight(pidMotion, inverse, notificationOutputStream);

    // to the bottom right
    squareCalibrationLine(pidMotion, lengthInMM2, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top right
    squareCalibrationLine(pidMotion, lengthInMM, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top left
    squareCalibrationLine(pidMotion, lengthInMM, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom left
    squareCalibrationLine(pidMotion, lengthInMM, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom middle
    squareCalibrationLine(pidMotion, lengthInMM2, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // Go back to initial point
    backwardSimpleMM(pidMotion, lengthInMM2, notificationOutputStream);
}


void squareCalibrationUsingSpline(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    bool inverse = (type == 0);
    float cp = lengthInMM / 10.0f;

    // Active the Motion Mode + to add several motion
    setMotionModeAdd(pidMotion);

    // Forward
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              0.0f,        0.0f, 0.0f,
                                              lengthInMM2, 0.0,  0.0f, 
                                              notificationOutputStream);

    // turn on right
    squareCalibrationRotationRight(pidMotion, inverse, notificationOutputStream);

    // to the bottom left
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              lengthInMM2, 0.0f        , -90.0f,
                                              lengthInMM2, -lengthInMM2, -90.0f,
                                              notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top right
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              lengthInMM2             , -lengthInMM2, 0.0f,
                                              lengthInMM2 + lengthInMM, -lengthInMM2, 0.0f,
                                              notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top left
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              lengthInMM2 + lengthInMM, -lengthInMM2, 90.0f,
                                              lengthInMM2 + lengthInMM, lengthInMM2, 90.0f,
                                              notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom left
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              lengthInMM2 + lengthInMM, lengthInMM2, 180.0f,
                                              lengthInMM2             , lengthInMM2, 180.0f,
                                              notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom middle
    squareCalibrationSpline(pidMotion, inverse, cp,
                                              lengthInMM2, lengthInMM2, 270.0f,
                                              lengthInMM2, 0.0f       , 270.0f,
                                              notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // Go back to initial point
    squareCalibrationSpline(pidMotion, inverse, -cp,
                                              lengthInMM2, 0.0f, 0.0f,
                                              0.0f       , 0.0f, 0.0f,
                                              notificationOutputStream);
}
