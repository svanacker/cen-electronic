#include "motionCalibration.h"

#include "../motion.h"
#include "simpleMotion.h"
#include "../extended/bsplineMotion.h"

#include "../../common/math/cenMath.h"

// CALIBRATION

void squareCalibrationRotationLeft(bool inverse) {
    if (inverse) {
        rightSimpleDegreeAndWait(DEG_90);
    }
    else {
        leftSimpleDegreeAndWait(DEG_90);
    }
}

void squareCalibrationRotationRight(bool inverse) {
    if (inverse) {
        leftSimpleDegreeAndWait(DEG_90);
    }
    else {
        rightSimpleDegreeAndWait(DEG_90);
    }
}
void squareCalibrationLine(float x, float y, float angle, bool inverse) {
    float cp = 100.0f;
    if (inverse) {
        gotoSimpleSpline(x, -y, -angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false);
    }
    else {
        gotoSimpleSpline(x, y, angle, cp, cp, MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL, false);
    }
    handleAndWaitFreeMotion();
}

void squareCalibration(unsigned char type, float lengthInMM) {
    // to the bottom middle
    float lengthInMM2 = lengthInMM / 2.0f;

    bool inverse = (type == 0);

    // turn on right
    squareCalibrationRotationRight(inverse);

    // to the bottom right
    squareCalibrationLine(0, -lengthInMM2, -900.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the top right
    squareCalibrationLine(lengthInMM, -lengthInMM2, 0.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the top left
    squareCalibrationLine(lengthInMM, lengthInMM2, 900.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the bottom left
    squareCalibrationLine(0, lengthInMM2, 1800.0f, inverse);
    squareCalibrationRotationLeft(inverse);

    // to the bottom middle
    squareCalibrationLine(0, 0, -900.0f, inverse);
    squareCalibrationRotationLeft(inverse);
}
