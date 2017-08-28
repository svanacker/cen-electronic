#include "motionCalibration.h"

#include "../motion.h"
#include "simpleMotion.h"
#include "../extended/bsplineMotion.h"

#include "../../common/math/cenMath.h"

// CALIBRATION

void squareCalibrationRotationLeft(PidMotion* pidMotion, bool inverse) {
    if (inverse) {
        rightSimpleDegreeAndWait(pidMotion, DEG_90);
    }
    else {
        leftSimpleDegreeAndWait(pidMotion, DEG_90);
    }
}

void squareCalibrationRotationRight(PidMotion* pidMotion, bool inverse) {
    if (inverse) {
        leftSimpleDegreeAndWait(pidMotion, DEG_90);
    }
    else {
        rightSimpleDegreeAndWait(pidMotion, DEG_90);
    }
}
void squareCalibrationLine(PidMotion* pidMotion, float x, float y, float angle, bool inverse) {
    float cp = 100.0f;
    if (inverse) {
        gotoSimpleSpline(pidMotion, x, -y, -angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false);
    }
    else {
        gotoSimpleSpline(pidMotion, x, y, angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false);
    }
    handleAndWaitFreeMotion(pidMotion);
}

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    bool inverse = (type == 0);

    // turn on right
    squareCalibrationRotationRight(pidMotion, inverse);

    // to the bottom right
    squareCalibrationLine(pidMotion, 0, -lengthInMM2, -900.0f, inverse);
    squareCalibrationRotationLeft(pidMotion, inverse);

    // to the top right
    squareCalibrationLine(pidMotion, lengthInMM, -lengthInMM2, 0.0f, inverse);
    squareCalibrationRotationLeft(pidMotion, inverse);

    // to the top left
    squareCalibrationLine(pidMotion, lengthInMM, lengthInMM2, 900.0f, inverse);
    squareCalibrationRotationLeft(pidMotion, inverse);

    // to the bottom left
    squareCalibrationLine(pidMotion, 0, lengthInMM2, 1800.0f, inverse);
    squareCalibrationRotationLeft(pidMotion, inverse);

    // to the bottom middle
    squareCalibrationLine(pidMotion, 0, 0, -900.0f, inverse);
    squareCalibrationRotationLeft(pidMotion, inverse);
}
