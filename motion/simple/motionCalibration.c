#include "motionCalibration.h"

#include "../motion.h"
#include "simpleMotion.h"
#include "../extended/bsplineMotion.h"

#include "../../common/math/cenMath.h"

// CALIBRATION

void squareCalibrationRotationLeft(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        rightSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
    else {
        leftSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
}

void squareCalibrationRotationRight(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        leftSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
    else {
        rightSimpleDegree(pidMotion, DEG_90, notificationOutputStream);
    }
}
void squareCalibrationLine(PidMotion* pidMotion, float x, float y, float angle, bool inverse, OutputStream* notificationOutputStream) {
    float cp = 100.0f;
    if (inverse) {
        gotoSpline(pidMotion, x, -y, -angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
    else {
        gotoSpline(pidMotion, x, y, angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
}

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    bool inverse = (type == 0);
    
    // Active the Motion Mode + to add several motion
    setMotionModeAdd(pidMotion);

    // turn on right
    squareCalibrationRotationRight(pidMotion, inverse, notificationOutputStream);

    // to the bottom right
    squareCalibrationLine(pidMotion, 0, -lengthInMM2, -DEG_90, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top right
    squareCalibrationLine(pidMotion, lengthInMM, -lengthInMM2, 0.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top left
    squareCalibrationLine(pidMotion, lengthInMM, lengthInMM2, DEG_90, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom left
    squareCalibrationLine(pidMotion, 0, lengthInMM2, DEG_180, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom middle
    squareCalibrationLine(pidMotion, 0, 0, -DEG_90, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);
}
