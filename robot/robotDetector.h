#ifndef ROBOTDETECTOR_H
#define ROBOTDETECTOR_H

#include "../device/device.h"

// SONAR CONSTANT

/** Define the minimum of servo value to notify there is a robot on the obstacle. */
#define SERVO_VALUE_MIN_NOTIFY_OBSTACLE 1350

/** Define the maximum of servo value to notify there is a robot on the obstacle. */
#define SERVO_VALUE_MAX_NOTIFY_OBSTACLE 1750

/** The distance minimal for detection. Don't take values under this threshold in consideration. */
#define MIN_DETECTION_DISTANCE_CM 10

/** The number of centimeter for which we stop the motor. */
#define OBSTACLE_DISTANCE_CM 45

#define OBSTACLE_DELAY_BEFORE_NEXT_NOTIFICATION 7

/** Divide frequency factor in comparison with PID => 72 Hz / RANGING_DELAY */
#define RANGING_DELAY 6

/** The size of the history. */
#define HISTORY_SIZE 5

/** Address of the sonar */
#define SONAR_ADDRESS 0xE2


/** Defines the constant when no obstacle is found */
#define NO_OBSTACLE 0

/** Defines the constant for obstacle found */
#define OBSTACLE 1

// LASER CONSTANT

/** The laser has not found anything. */
#define ANGLE_NOT_FOUND 0

/** The pin for the laser detection. */
#define PIN_LASER PORTDbits.RD2

// GLOBAL

/**
 * Get the last notify obstacle.
 */
unsigned int getLastNotifyObstacleTime();

void setLastNotifyObstacleTime(unsigned int value);

void clearObstacle(void);

// LASER INTERFACE

/**
 * Change the width of rotation for the laser.
 * @param maxLeft 
 * @param maxRight
 */
void setMaxLeftAndRight(unsigned int maxLeft, unsigned int maxRight);

/**
 * Get the real angle with the robot.
 */
signed int getAngleInDegreeWithRobot();

/**
 * Returns if the laser is Enabled or not.
 */
unsigned char isRobotDetectorEnabled();

/**
 * Enable or disable robot detector.
 */
void setRobotDetectorEnabled(unsigned char value);

/**
 * Get the position with the last position.
 */
int getLastLaserServoPosition(void);

/**
 * Get the difference between last right position and left position to determine a width of detection.
 * With trigonometric function, we can determine further the distance of the object.
 */
int getLastLaserServoWidth(void);

/**
 * Set the speed of detection
 * @param value speed of detection.
 */
void setRobotDetectorSpeed(char value);


// SONAR Interface

/**
 * Try to detects the robot, and return OBSTACLE or NO_OBSTACLE.
 */
unsigned char hasRobotObstacle(void);

/**
 * Get the average value of last ranging.
 */
unsigned int getAverageRangingValue(void);

/**
 * Prints the distances found by the sonar
 */
void printDistances(void);

// DEVICE INTERFACE

/**
 * Returns a descriptor on the robot detector device.
 */
DeviceDescriptor getRobotDetectorDeviceDescriptor();

/**
 * Init the device
 */
void initRobotDetector(void);

#endif


