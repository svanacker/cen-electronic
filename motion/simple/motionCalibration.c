#include "motionCalibration.h"

#include "../motion.h"
#include "simpleMotion.h"
#include "../extended/bsplineMotion.h"

#include "../../common/math/cenMath.h"

// CALIBRATION

void squareCalibrationRotationLeft(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        rightSimpleDegreeAndWait(pidMotion, DEG_90, notificationOutputStream);
    }
    else {
        leftSimpleDegreeAndWait(pidMotion, DEG_90, notificationOutputStream);
    }
}

void squareCalibrationRotationRight(PidMotion* pidMotion, bool inverse, OutputStream* notificationOutputStream) {
    if (inverse) {
        leftSimpleDegreeAndWait(pidMotion, DEG_90, notificationOutputStream);
    }
    else {
        rightSimpleDegreeAndWait(pidMotion, DEG_90, notificationOutputStream);
    }
}
void squareCalibrationLine(PidMotion* pidMotion, float x, float y, float angle, bool inverse, OutputStream* notificationOutputStream) {
    float cp = 100.0f;
    if (inverse) {
        gotoSimpleSpline(pidMotion, x, -y, -angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
    else {
        gotoSimpleSpline(pidMotion, x, y, angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false, notificationOutputStream);
    }
    handleAndWaitFreeMotion(pidMotion);
}

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    bool inverse = (type == 0);

    // turn on right
    squareCalibrationRotationRight(pidMotion, inverse, notificationOutputStream);

    // to the bottom right
    squareCalibrationLine(pidMotion, 0, -lengthInMM2, -900.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top right
    squareCalibrationLine(pidMotion, lengthInMM, -lengthInMM2, 0.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the top left
    squareCalibrationLine(pidMotion, lengthInMM, lengthInMM2, 900.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom left
    squareCalibrationLine(pidMotion, 0, lengthInMM2, 1800.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);

    // to the bottom middle
    squareCalibrationLine(pidMotion, 0, 0, -900.0f, inverse, notificationOutputStream);
    squareCalibrationRotationLeft(pidMotion, inverse, notificationOutputStream);
}
