#include <math.h>

#include "laserBeacon.h"
#include "beaconSystem.h"
#include "laserBeaconDevice.h"
#include "commonBeaconDeviceInterface.h"

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
#include "../../drivers/beacon/beaconLaserDriver.h"

#include "../../robot/robotDetector.h"

/** Defines the code for the timer dedicated to the beacon. */
#define BEACON_TIMER_CODE 100

/** The beacon system. */
static BeaconSystem beaconSystem;

// TIMER

/**
 * Internal timer callback.
 */
void beaconTimerCallback(Timer* timer) {
	if (!beaconSystem.enabled) {
		return;
	}
	// Count the number of laser which track something
	int trackCounter = 0; 

    int laserIndex;
    for (laserIndex = 0; laserIndex < LASER_COUNT; laserIndex++) {
		Laser* laser = getLaser(laserIndex);
        detectsLaser(laser);
		if (hasTrackSomething(laser)) {
			trackCounter++;
		}
    }
	// all laser detects something !
	if (trackCounter == LASER_COUNT) {
		beaconSystem.lastDetectionTime = 0.0f;
	}
	else {
		// The code is execute at 2000 Hz, so if we want milliSeconds, we increment by 0.5f
		beaconSystem.lastDetectionTime += 0.5f;
	}
}

// CONFIGURATION

void setDistanceBetweenBeacon(float aDistanceBetweenBeacon) {
    beaconSystem.distanceBetweenBeacon = aDistanceBetweenBeacon;
}

float getDistanceBetweenBeacon() {
    return beaconSystem.distanceBetweenBeacon;
}

void setObsoleteDetectionTimeThreshold(float obsoleteDetectionTimeThreshold) {
    beaconSystem.obsoleteDetectionTimeThreshold = obsoleteDetectionTimeThreshold;
}

float getObsoleteDetectionTimeThreshold() {
	return beaconSystem.obsoleteDetectionTimeThreshold;
}

int getLastDetectionTimeInMillis() {
	return beaconSystem.lastDetectionTime;
}

void setCalibrationPoint(float x, float y) {
	beaconSystem.calibrationPoint.x = x;
	beaconSystem.calibrationPoint.y = y;
}

// Notification

void setNotifyTimeDelay(float notifyTimeDelay) {
	beaconSystem.notifyTimeDelay = notifyTimeDelay;
}

float getNotifyTimeDelay() {
	return beaconSystem.notifyTimeDelay;
}

BOOL notifyRobotPositionIfNecessary() {
	// Don't notify if the servo does not move
	if (!beaconSystem.enabled) {
		return FALSE;
	}
	Timer* beaconTimer = getTimerByCode(BEACON_TIMER_CODE);
	// delay is exceed => must notify
	if (beaconTimer->time > beaconSystem.lastNotifyTime + beaconSystem.notifyTimeDelay) {
		// for the next time, mark it
		beaconSystem.lastNotifyTime = beaconTimer->time; 
		Point* point = getOpponentRobotPosition();
		notifyRobotPosition(point);
		return TRUE;
	}
	return FALSE;
}

// INIT / STOP

void initLaserBeacon() {
    addTimer(BEACON_TIMER_CODE, TIME_DIVISER_2000_HERTZ, beaconTimerCallback);
}

void stopLaserBeacon() {
    // Shutdown timer
    Timer* beaconTimer = getTimerByCode(BEACON_TIMER_CODE);
    stopTimer(beaconTimer);
}


void setBeaconSystemEnabled(BOOL enabled) {
	beaconSystem.enabled = enabled;
}

Laser* getLaser(int laserIndex) {
    Laser* result = &(beaconSystem.lasers[laserIndex]);
    return result;
}

/**
 * @private
 * Computes the value of the detected position for the servo based on the last hits.
 * set to 0 if there are not both value of left and right.
 * @return the position, 0 if not detected
 */
int updateDetectedPosition(Laser* laser) {
    int result = 0;
    if (hasTrackSomething(laser)) {
        // do the average
        result = (laser->lastServoPositionHit[LEFT_DIRECTION] + laser->lastServoPositionHit[RIGHT_DIRECTION]) / 2;
    }
    laser->detectedPosition = result;
    return result;
}

/**
 * @private
 * Get the position by calculing	the following formula :
 * x = d - a2 * d / (a1 + a2)
 */
void fillPositionWithValues(Point* point, float d, float a1, float a2) {
    float addition = a1 + a2;
    float a2_mul_d = a2 * d;
    point->x = a2_mul_d / addition;
    point->y = a1 * a2_mul_d / addition;
}

/**
 * Gets the position of the laser by triangulation of the information gived by the both laser.
 * If information is not correct, we give a position of (0, 0).
 */
Point* getOpponentRobotPosition() {
    Timer* beaconTimer = getTimerByCode(BEACON_TIMER_CODE);

    // we want to avoid that position change during compute
    lockAndWaitForTimer(beaconTimer);

    Laser* laser1 = getLaser(LASER_INDEX_1);
    Laser* laser2 = getLaser(LASER_INDEX_2);

    // Updates the detected Position of the laser
    int detectedPosition1 = updateDetectedPosition(laser1);
    int detectedPosition2 = updateDetectedPosition(laser2);

	Point* opponentRobotPosition = &(beaconSystem.opponentRobotPosition);

    // if there is a detected object (by both laser)
    if (detectedPosition1 != 0 && detectedPosition2 != 0) {
		// Too obsolete Information
		if (getLastDetectionTimeInMillis() > getObsoleteDetectionTimeThreshold()) {
	        opponentRobotPosition->x = 0;
	        opponentRobotPosition->y = 0;
			OutputStream* outputStream = getOutputStreamLogger(INFO);
			appendStringAndDec(outputStream, "LOST OBJECT SINCE=", getLastDetectionTimeInMillis());
			println(outputStream);
		}
		else {
	        float angleInRadian1 = getAngleInRadian(laser1);
	        float angleInRadian2 = getAngleInRadian(laser2);
	        float a1 = tan(angleInRadian1);
	        float a2 = tan(angleInRadian2);
			// Compute the position
	        fillPositionWithValues(opponentRobotPosition, beaconSystem.distanceBetweenBeacon, a1, a2);
		}
    } else {
		// Reset Robot Position
        opponentRobotPosition->x = 0;
        opponentRobotPosition->y = 0;
    }
    unlockTimer(beaconTimer);

    return opponentRobotPosition;
}

void doBeaconCalibration() {
	// Update the robot Position (which must normally coincides with calibration Point)
	getOpponentRobotPosition();
	Point* calibrationPoint = &(beaconSystem.calibrationPoint);

	OutputStream* outputStream = getOutputStreamLogger(INFO);

	recalibrateServoInitValue(outputStream, getLaser(LASER_INDEX_1), calibrationPoint->x, calibrationPoint->y);
	recalibrateServoInitValue(outputStream, getLaser(LASER_INDEX_2), getDistanceBetweenBeacon() - calibrationPoint->x, calibrationPoint->y);
}

// DEBUG

void printBeaconSystemConfiguration(OutputStream* outputStream) {
	Point* opponentPoint = getOpponentRobotPosition();
	
	Laser* laser1 = getLaser(LASER_INDEX_1);
	Laser* laser2 = getLaser(LASER_INDEX_2);
	
	printLaserStruct(outputStream, laser1);
	println(outputStream);
	printLaserStruct(outputStream, laser2);
	
	appendCRLF(outputStream);
	
	// Last Detection Time
	appendStringAndDecf(outputStream, "lastDetectionTime=", getLastDetectionTimeInMillis());
	println(outputStream);
	
	// Obsolete Detection Time Threshold
	appendStringAndDecf(outputStream, "obsoleteDetectionTimeThreshold=", getObsoleteDetectionTimeThreshold());
	println(outputStream);
	
	// Notify Time Delay
	appendStringAndDecf(outputStream, "notifyTimeDelay=", getNotifyTimeDelay());
	println(outputStream);
	
	// Opponent Position
	appendString(outputStream, "opponentPosition:");
	printPoint(outputStream, opponentPoint, " mm");
	
	// Distance between beacon
	appendStringAndDecf(outputStream, "distanceBetweenBeacon=", getDistanceBetweenBeacon());
	appendString(outputStream, " mm");
	println(outputStream);
	
	// Calibration Point
	appendString(outputStream, "calibrationPoint:");
	printPoint(outputStream, &(beaconSystem.calibrationPoint), " mm");
	
	// Opponent Position
	appendString(outputStream, "opponentPosition:");
	printPoint(outputStream, opponentPoint, " mm");
}

