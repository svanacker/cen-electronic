#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "trajectory.h"

#include "../../common/2d/2d.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../motion/position/coders.h"
#include "../../motion/pid/pid.h"
#include "../../robot/robotConstants.h"

// Position update threshold in mm
// #define UPDATE_THRESHOLD 5.0f
// No Threshold, we compute at the end of a trajectory
#define UPDATE_THRESHOLD 1.0f

// wheels distance in true length
static float width;
// Position on the board in true length
static Position position = {
    {0.0f, 0.0f}, 0.0f, 0.0f};

// Last left coder value
static float lastLeft = 0.0f;
// Last right coder value
static float lastRight = 0.0f;
// Last angle
static float lastAngle = 0.0f;

void initializeTrajectory() {
    width = WHEELS_DISTANCE;
    clearTrajectory();
}


void clearTrajectory() {
    setPosition(0, 0, 0);
    lastLeft = 0.0f;
    lastRight = 0.0f;
    lastAngle = 0.0f;
}

void setPosition(float x, float y, float orientation) {
    position.pos.x = x;
    position.pos.y = y;
    position.initialOrientation = orientation - position.orientation + position.initialOrientation;
    position.orientation = orientation;
    lastAngle = 0.0f;
}

Position* getPosition(void) {
    return &position;
}

float getWheelsDistance(void) {
    return width;
}

void setWheelsDistance(float distance) {
    width = distance;
}

// --------------------------------------------------- NEW METHOD --------------------------------------------------------------------

void debugTrajectoryVariables(char* valueName1, float value1, char* valueName2, float value2) {
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDecf(outputStream, valueName1, value1);
    appendStringAndDecf(outputStream, valueName2, value2);
    appendCRLF(outputStream);
}

/**
 * @private
 * Computes and updates the position from the sp�cified
 * values from the coders.
 * @param left the value of the left coder
 * @param right the value of the right coder
 * @return 1 if the position has been updated, 0 otherwise
 */
int absoluteUpdateFromCoders(signed long left, signed long right, bool useThreshold, bool debug) {
    if (debug) {
        debugTrajectoryVariables("left=", left, ", right=", right);
    }
    float l = (float) left * WHEEL_LENGTH_LEFT;
    float r = (float) right * WHEEL_LENGTH_RIGHT;
    if (debug) {
        debugTrajectoryVariables("l=", l, ", r=", r);
    }
    float dl = l - lastLeft;
    float dr = r - lastRight;
    if (debug) {
        debugTrajectoryVariables("dl=", dl, ", dr=", dr);
    }
    if (useThreshold) {
        if (fabsf(dl) <= UPDATE_THRESHOLD && fabsf(dr) <= UPDATE_THRESHOLD) {
            return 0;
        }
    }

    // difference des distances parcourues par les roues en m
    float dw = r - l;
    // orientation finale = difference des distances / demi-distance des roues
    float orientation = fmod(dw / width, 2.0f * PI) + lastAngle + position.initialOrientation;
    // angle relatif au dernier mouvement
    // lastAngle is only used when we clear Coders !
    float relativePositionOrientation = position.orientation;
    float angle = orientation - relativePositionOrientation;
    float meanOrientation = (orientation + relativePositionOrientation) / 2.0f;

    if (debug) {
        debugTrajectoryVariables("dw=", dw, ", orien=", orientation);
        debugTrajectoryVariables("angle=", angle, ",meanOrien=", meanOrientation);
    }

    // distance during last move
    float d = (dl + dr) / 2.0f;
    // project distance according the angle
    float k = 1.0f;
    if (angle != 0.0f) {
        float t = angle / 2.0f;
        k = sin(t) / t;
    }

    float dx = d * k * cosf(meanOrientation);
    float dy = d * k * sinf(meanOrientation);
    if (debug) {
        debugTrajectoryVariables("dx=", dx, ", dy=", dy);
    }

    // mise a jour de la position
    position.pos.x += dx;
    position.pos.y += dy;
    position.orientation = orientation;

    lastLeft = l;
    lastRight = r;

    return 1;
}

void updateTrajectory() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    //    curveUpdateFromCoders(left, right);
    absoluteUpdateFromCoders(left, right, true, false);
}

void updateTrajectoryWithNoThreshold() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    // do not use threshold
    absoluteUpdateFromCoders(left, right, false, false);
}

void updateTrajectoryAndClearCoders() {
    updateTrajectoryWithNoThreshold();
    lastAngle = position.orientation - position.initialOrientation;
    clearCoders();
    lastLeft = 0;
    lastRight = 0;
}

void printPosition(OutputStream* outputStream) {
    // clearScreen();
    appendCRLF(outputStream);
    Position* p = getPosition();
    appendStringAndDec(outputStream, "left=", getCoderValue(CODER_LEFT));
    appendStringAndDec(outputStream, " | right=", getCoderValue(CODER_RIGHT));

    printPoint(outputStream, &(p->pos), " mm");

    appendStringAndAngleInDeg(outputStream, "\rang:", p->orientation);
    appendStringAndAngleInDeg(outputStream, "\rang ini:", p->initialOrientation);

    appendStringAndDec(outputStream, "\rlastLeft:", lastLeft);
    appendString(outputStream, " pulse");

    appendStringAndDec(outputStream, "\rlastRight:", lastRight);
    appendString(outputStream, " pulse");

    appendStringAndAngleInDeg(outputStream, "\rlastAng:", lastAngle);
    appendString(outputStream, " deg");

    println(outputStream);
}
