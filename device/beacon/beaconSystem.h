#ifndef BEACON_SYSTEM_H
#define BEACON_SYSTEM_H

#include "../../common/commons.h"
#include "../../common/io/buffer.h"
#include "../../common/2d/2d.h"

#include "../../device/device.h"

#define LASER_COUNT 2

#define LASER_INDEX_1 0
#define LASER_INDEX_2 1

#define LASER_SERVO_INDEX_1 1
#define LASER_SERVO_INDEX_2 4


/**
 * Structures which stores each element related to beacon detection system.
 */
typedef struct {
	/** enabled or not the rotation. */
	bool enabled;	

	/** The lasers instances. */
	Laser lasers[LASER_COUNT];
	
	/** Distance between beacons. */
	float distanceBetweenBeacon;
	
	/** Position of opponent robot. */
	Point opponentRobotPosition;

	/** Point used for calibration. */
	Point calibrationPoint;

	/** Time in milliseconds the signal is lost. */
	float lastDetectionTime;

	/** 
	* Time in milliseconds we consider that we do not send the position (because the last
	* detection is too old (it's a risk to send obsolete Information).
	*/
	float obsoleteDetectionTimeThreshold;

	/**
	* Time in milliseconds period to notify the robot position via the zigbee.
 	*/
	float notifyTimeDelay;

	/**
	* last Notification time.
	*/
	float lastNotifyTime;
} BeaconSystem;

/**
 * Gets the position of the laser by triangulation of the infomation gived by the both laser.
 * If information is not correct, we give a position of (0, 0).
 */
Point* getOpponentRobotPosition();


/**
* Init all the laser beacon detection system.
*/
void initLaserBeacon();

/**
* Stop the laser beacon detection system.
*/
void stopLaserBeacon();

/**
* Enabled or not the detection by the lasers and the rotation via servo.
*/
void setBeaconSystemEnabled(bool enabled);

/**
 * Get the laser struct with index "laserIndex"
 */
Laser* getLaser(int laserIndex);

// CONFIGURATION

/**
 * Set the distance between the two beacons.
 */
void setDistanceBetweenBeacon(float aDistanceBetweenBeacon);

/**
 * Get the distance between the two beacons.
 */
float getDistanceBetweenBeacon();

/** 
* Time in milliseconds we consider that we do not send the position (because the last
* detection is too old (it's a risk to send obsolete Information).
*/
float getObsoleteDetectionTimeThreshold();

void setObsoleteDetectionTimeThreshold(float obsoleteDetectionTimeThreshold);

/**
 * Time in milliseconds period to notify the robot position via the zigbee.
 */
void setNotifyTimeDelay(float notifyTimeDelay);

float getNotifyTimeDelay();

/**
* Notify the robot position.
* @return true if the method add data to be sent by the zigbee
*/
bool notifyRobotPositionIfNecessary();

/**
 * Set the position of the calibration point.
 */
void setCalibrationPoint(float x, float y);

// CALIBRATION

/**
 * Do a calibration with the help of a temporary beacon help placed on the third beacon location.
 */
void doBeaconCalibration();

// DEBUG FUNCTIONS

/**
 * Print all configuration data of beacon system
 * - laser Information
 * - position of the opponent robot
 * - calibration information
 */
void printBeaconSystemConfiguration(OutputStream* outputStream);

#endif
