#include <math.h>

#include "laserBeacon.h"
#include "laserBeaconDevice.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"
#include "../../common/delay/delay30F.h"

#include "../../common/pwm/servoPwm.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"
#include "../../common/2d/2d.h"

#include "../../drivers/jennic/jennic5139Driver.h"

#include "../../robot/robotDetector.h"


void initLaserDetectorStruct(Laser* laser, int servoIndex, pinValueFunction *pinValue,
        int maxLeft, int maxRight, int shortTrackingInterval,
        float angleFactorCompute, int servoInitValueCompute, int beaconAngleDegree) {
    laser->pinValue = pinValue;
    // start at average value
    laser->servoPosition = (maxLeft + maxRight) / 2;
    laser->servoIndex = servoIndex;
    int direction;
    for (direction = 0; direction < DIRECTION_COUNT; direction++) {
        laser->lastServoPositionHit[direction] = 0;
        laser->oldServoPositionHit[direction] = 0;
        laser->hitDuringLast[direction] = FALSE;
    }
    laser->laserHitCounter = 0;
    laser->direction = RIGHT_DIRECTION;
    laser->maxLeft = maxLeft;
    laser->maxRight = maxRight;
    laser->shortTrackingInterval = shortTrackingInterval;
    laser->currentMaxLeft = laser->maxLeft;
    laser->currentMaxRight = laser->maxRight;
    laser->updatePositionCounter = 0;
    laser->speed = 2;

    // For compute of object position
    laser->angleFactorCompute = angleFactorCompute;
    laser->servoInitValueCompute = servoInitValueCompute;
    laser->beaconAngleDegree = beaconAngleDegree;
}

/**
 * @private
 * Update the laser to change his next position to search detection object.
 * @param laserIndex the index of laser
 */
void updateLaserPosition(Laser* laserDetector) {
    // Right sense
    if (laserDetector->direction == RIGHT_DIRECTION) {
        laserDetector->servoPosition++;
        // we reach the limit
        if (laserDetector->servoPosition > laserDetector->currentMaxRight) {
            // if we don't reach the target
            if (!laserDetector->hitDuringLast[RIGHT_DIRECTION]) {
                // we try to increase the limit
                // -> we are at the maximum
                if (laserDetector->servoPosition >= laserDetector->maxRight) {
                    // we change the turn
                    laserDetector->direction = LEFT_DIRECTION;
                    // reset the hit for the new direction
                    laserDetector->hitDuringLast[LEFT_DIRECTION] = FALSE;
                    laserDetector->laserHitCounter = 0;
                    laserDetector->currentMaxRight = laserDetector->maxRight;
                }                    // -> we are under the maximum
                else {
                    // we increase with the limit of MAX_RIGHT
                    laserDetector->currentMaxRight = minInt(laserDetector->maxRight, laserDetector->currentMaxRight + laserDetector->shortTrackingInterval);
                }
            } else {
                // we change the turn
                laserDetector->direction = LEFT_DIRECTION;
                // reset the hit for the new direction
                laserDetector->hitDuringLast[LEFT_DIRECTION] = FALSE;
                laserDetector->laserHitCounter = 0;
            }
        }
    } else {
        // left sense
        laserDetector->servoPosition--;
        if (laserDetector->servoPosition < laserDetector->currentMaxLeft) {
            // if we don't reach the target
            if (!laserDetector->hitDuringLast[LEFT_DIRECTION]) {
                // we try to increase
                // -> we are at the minimum
                if (laserDetector->servoPosition < laserDetector->maxLeft) {
                    // we change the turn
                    laserDetector->direction = RIGHT_DIRECTION;
                    // reset the hit for the new direction
                    laserDetector->hitDuringLast[RIGHT_DIRECTION] = FALSE;
                    laserDetector->laserHitCounter = 0;
                    laserDetector->currentMaxLeft = laserDetector->maxLeft;
                }                    // -> we try to decrease the limit
                else {
                    // we decrease with the limit of MAX_RIGHT
                    laserDetector->currentMaxLeft = maxInt(laserDetector->maxLeft, laserDetector->currentMaxLeft - laserDetector->shortTrackingInterval);
                }
            } else {
                // we change the turn
                laserDetector->direction = RIGHT_DIRECTION;
                // reset the hit for the new direction
                laserDetector->hitDuringLast[RIGHT_DIRECTION] = FALSE;
                laserDetector->laserHitCounter = 0;
            }
        }
    }
    // update the position of the servo
    pwmServo(laserDetector->servoIndex, 0xFF, laserDetector->servoPosition);
}

/**
 * Sub routine in charge of detecting the value of the laser, and saves the differents hits.
 * @param laserIndex the index of laser
 */
void detectsLaser(Laser* laserDetector) {
    // if the laser detects something on the PIN dedicated to the laser
    int detectionPin = laserDetector->pinValue();
    if (detectionPin != 0) {
        laserDetector->laserHitCounter += HIT_FACTOR;
        if (laserDetector->laserHitCounter > 0) {
            int direction = laserDetector->direction;
            // reset counter
            laserDetector->laserHitCounter = 0;
            // saves the position for the direction
            laserDetector->lastServoPositionHit[direction] = laserDetector->servoPosition;
            // saves that we touch the target
            laserDetector->hitDuringLast[direction] = TRUE;
            if (laserDetector->lastServoPositionHit[direction] != laserDetector->oldServoPositionHit[direction]) {
                laserDetector->oldServoPositionHit[direction] = laserDetector->lastServoPositionHit[direction];
                if (direction == RIGHT_DIRECTION) {
                    laserDetector->currentMaxRight = laserDetector->servoPosition + laserDetector->shortTrackingInterval;
                } else {
                    laserDetector->currentMaxLeft = laserDetector->servoPosition - laserDetector->shortTrackingInterval;
                }
            }
        }
    }
    else {
        if (laserDetector->laserHitCounter > 0) {
            laserDetector->laserHitCounter--;
        }
    }
    laserDetector->updatePositionCounter++;
    if (laserDetector->updatePositionCounter > laserDetector->speed) {
        updateLaserPosition(laserDetector);
        laserDetector->updatePositionCounter = 0;
    }
}

bool hasTrackSomething(Laser* laser) {
	return (laser->lastServoPositionHit[LEFT_DIRECTION] != 0 && laser->lastServoPositionHit[RIGHT_DIRECTION] != 0);
}

/**
 * @private
 * Get the computed angle of the laser.
 */
float getAngleInDegree(Laser* laser) {
    // this rules is based on measure and observations
    // which transforms value from the servo moteur to angle in degree
    float result = ((float) (laser->servoInitValueCompute - laser->detectedPosition)) / (float) laser->angleFactorCompute;

    // Saves the value
    laser->computedAngleDegree = result;
    return result;
}

/**
 * @private
 * Get the a factor corresponding to atan2(x, y).
 */
float getAngleInRadian(Laser* laser) {
    // this rules is based on measure and observations
    // which transforms value from the servo moteur to angle in degree
    float result = getAngleInDegree(laser);
    // converts the value into radian
    result = result * PI / 180.0f;

    laser->computedAngleRadian = result;

    return result;
}

// CALIBRATION

void recalibrateServoInitValue(OutputStream* outputStream, Laser* laser, float relativeCalibrationX, float relativeCalibrationY) {
	float normalRadianAngle = atan(relativeCalibrationX / relativeCalibrationY);
	float normalRadianDegree = 90.0f - (normalRadianAngle / PI_DIVIDE_180);

	appendStringAndDec(outputStream, "laserIdx=", laser->servoIndex);
	appendCRLF(outputStream);
	appendStringAndDecf(outputStream, "normalRadianAngle=", normalRadianAngle);
	appendCRLF(outputStream);
	appendStringAndDecf(outputStream, "normalRadianDegree=", normalRadianDegree);
	appendCRLF(outputStream);

	appendStringAndDecf(outputStream, "prev:servoInitValueCompute=", laser->servoInitValueCompute);
	appendCRLF(outputStream);

	laser->servoInitValueCompute = normalRadianDegree * laser->angleFactorCompute + laser->detectedPosition;
	appendStringAndDecf(outputStream, "new:servoInitValueCompute=", laser->servoInitValueCompute);
	appendCRLF(outputStream);
	appendCRLF(outputStream);
}

// DEBUG


void printLaserStruct(OutputStream* outputStream, Laser* laser) {
	appendStringAndDec(outputStream, "servoIdx=", laser->servoIndex);
	appendCRLF(outputStream);

	int pinValue = laser->pinValue();
	appendStringAndDec(outputStream, "pinValue=", pinValue);
	appendCRLF(outputStream);

    appendStringAndDec(outputStream, "servoPos=", laser->servoPosition);
    appendCRLF(outputStream);

    appendStringAndDec(outputStream, "lastServoPositionHit=", laser->lastServoPositionHit[LEFT_DIRECTION]);
    appendStringAndDec(outputStream, "/", laser->lastServoPositionHit[RIGHT_DIRECTION]);
    appendCRLF(outputStream);

    appendStringAndDec(outputStream, "detectedPosition=", laser->detectedPosition);
    appendCRLF(outputStream);

    appendStringAndDec(outputStream, "currentMax=", laser->currentMaxLeft);
    appendStringAndDec(outputStream, "/", laser->currentMaxRight);
    appendCRLF(outputStream);

    appendStringAndDecf(outputStream, "angleFactorCompute=", laser->angleFactorCompute);
    appendCRLF(outputStream);

    appendStringAndDec(outputStream, "servoInitValueCompute=", laser->servoInitValueCompute);
    appendCRLF(outputStream);

    appendStringAndDecf(outputStream, "beaconAngleDegree=", laser->beaconAngleDegree);
    appendCRLF(outputStream);

    appendStringAndDecf(outputStream, "computedAngleDegree=", laser->computedAngleDegree);
    appendCRLF(outputStream);

    appendStringAndDecf(outputStream, "computedAngleRadian=", laser->computedAngleRadian);
    appendCRLF(outputStream);
}
