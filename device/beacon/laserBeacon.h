#ifndef LASER_BEACON_H
#define LASER_BEACON_H

#include "../../common/commons.h"
#include "../../common/io/buffer.h"
#include "../../common/2d/2d.h"

#include "../../device/device.h"

/** The hit factor defines how much we increase the hit counter when we hit the beacon with the laser. */
#define HIT_FACTOR 5;

// LASER PART INTERFACE
#define DIRECTION_COUNT 2
#define LEFT_DIRECTION 0
#define RIGHT_DIRECTION 1


/**
 * Definition of a function which returns a pin value.
 */
typedef int pinValueFunction();

/**
 * Define the structure use to detect laser, and control servo Motor used to rotate the laser.
 */
typedef struct {
    /** pin to detect the laser. */
    pinValueFunction *pinValue;
    /** The servo Position. */
    int servoPosition;
    /** The servo Index. */
    int servoIndex;
    /** The servo position for the last hit. */
    unsigned int lastServoPositionHit[2];
    /** The position of the detected object, 0 if not found. */
    unsigned int detectedPosition;
    /** The old value of the last hit. */
    unsigned int oldServoPositionHit[2];
    /** If there is a hit during the last move. */
    bool hitDuringLast[2];
    /** The counter. */
    int laserHitCounter;
    /** turn of the rotation for the robot. */
    int direction;
    /** The absolute max left value. */
    int maxLeft;
    /** The absolute max right value. */
    int maxRight;
    /** The current maxLeft value */
    int currentMaxLeft;
    /** The current maxRight value */
    int currentMaxRight;
    /** Defines the interval to search, when we are in tracking mode. */
    int shortTrackingInterval;
    /** A counter to know when we must update the position. */
    int updatePositionCounter;
    /** the speed of the search. */
    int speed;
    /** The factor used to transform the servo Information (generally between 1000 and 2000), into a angle in degree. */
    float angleFactorCompute;
    /** The value of the servo for compute (arround the value of 1500). */
    float servoInitValueCompute;
    /** the angle of the beacon. */
    float beaconAngleDegree;
    /** the computed angle of the beacon in radians. */
    float computedAngleDegree;
    /** the computed angle of the beacon in radians. */
    float computedAngleRadian;
} Laser;

/**
 * Get the a factor corresponding to atan2(x, y).
 */
float getAngleInRadian(Laser* laser);

/**
 * Initialize the detector laser object.
 * @param laserIndex the laser index
 * @param servoIndex the servo index
 * @param detectorPin the detector pin
 * @param maxLeft the absolute maximal value for left detection (does not change during program)
 * @param maxRight the absolute maximal value for right detection (does not change during program)
 */
void initLaserDetectorStruct(Laser* laser, int servoIndex, pinValueFunction *pinValue,
        int maxLeft, int maxRight, int shortTrackingInterval,
        float angleFactorCompute, int servoInitValueCompute, int beaconAngleDegree);

/**
 * Sub routine in charge of detecting the value of the laser, and saves the differents hits.
 */
void detectsLaser(Laser* laser);

/**
 * Return if the laser has track something
 * We consider that a laser track something if it detects something during LEFT and RIGHT scanning
 */
bool hasTrackSomething(Laser* laser);

// CALIBRATION

/**
 * Recompute servoInitData (which is the value which can vary if we change servo geometry initial value.
 * The method used to do this calibration is to recompute servoInitData so that it corresponds to the angle done with
 * calibrationPoint
 */
void recalibrateServoInitValue(OutputStream* outputStream, Laser* laser, float relativeCalibrationX, float relativeCalibrationY);

// DEBUG

/**
 * Print on the serial the information about laser.
 * @param outputStream the buffer struct in which we send information
 */
void printLaserStruct(OutputStream* outputStream, Laser* laser);

#endif
