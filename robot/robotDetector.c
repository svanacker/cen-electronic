#include <p30Fxxxx.h>
#include <libpic30.h>
#include <math.h>

#include "robotDetector.h"

#include "../common/commons.h"
#include "robotConfig.h"

#include "../common/delay/delay30F.h"
#include "../common/serial/serialUtils.h"
#include "../common/serial/serial.h"
#include "../common/pwm/pwmPic.h"

#include "../device/drivers/srf02.h"
#include "../device/drivers/lcd.h"

#include "../motion/pid/pid.h"
#include "match/endMatchDetector.h"

// GLOBAL

/** If we debug or not. */
char debug = false;

/** If the robot detector is enabled or not. */
int robotDetectorEnabled = false;

/** Last time we notify an obstacle. */
unsigned int lastNotifyObstacleTime;

unsigned int getLastNotifyObstacleTime() {
    return lastNotifyObstacleTime;
}

void setLastNotifyObstacleTime(unsigned int value) {
    lastNotifyObstacleTime = value;
}

// SONAR

/** The distance measured between an object. */
unsigned int distances[HISTORY_SIZE];

/** The counter to store the current index of distance which is computed. */
unsigned int distanceIndex = 0;

// The delay for ranging (=> frequency is 72 Hz / RANGING_DELAY)
unsigned int rangingIndex = 0;

// LASER PART INTERFACE

/** The servo Position. */
unsigned int servoPosition = 1500;

#define LEFT_DIRECTION 0
#define RIGHT_DIRECTION 1

/** The servo position for the last hit. */
unsigned int lastServoPositionHit[2];

/** The old value. */
unsigned int oldServoPositionHit[2];

/** If there is a hit during the last move. */
unsigned char hitDuringLast[2];

int laserHitCounter = 0;

// Default values
#define SERVO_LASER_MAX_LEFT_POSITION_DEFAULT_VALUE 1000
#define SERVO_LASER_MAX_RIGHT_POSITION_DEFAULT_VALUE 2000


/** Defines the interval to search, when we are in tracking mode. */
#define SHORT_TRACKING_INTERVAL 50

/** turn of the rotation for the robot. */
int direction = RIGHT_DIRECTION;

/** The absolute max left value. */
int maxLeft = SERVO_LASER_MAX_LEFT_POSITION_DEFAULT_VALUE;

/** The absolute max right value. */
int maxRight = SERVO_LASER_MAX_RIGHT_POSITION_DEFAULT_VALUE;

/** The current maxLeft value */
int currentMaxLeft = SERVO_LASER_MAX_LEFT_POSITION_DEFAULT_VALUE;

/** The current maxRight value */
int currentMaxRight = SERVO_LASER_MAX_RIGHT_POSITION_DEFAULT_VALUE;

/** A counter to know when we must update the position. */
volatile int updatePositionCounter = 0;

/** the speed of the search. */
static int speed = 4;

// SONAR PART IMPLEMENTATION

void clearDistances() {
    int i;
    for (i = 0; i < HISTORY_SIZE; i++) {
        distances[i] = 0;
    }
}

void printDistances() {
    int i;
    for (i = 0; i < HISTORY_SIZE; i++) {
        sendDec(distances[i]);
        println();
    }
}

unsigned int getAverageRangingValue(void) {
    unsigned int result = 0;
    int n = HISTORY_SIZE;
    int i;
    for (i = 0; i < n; i++) {
        result += distances[i];
    }
    return result / n;
}

void clearObstacle(void) {
    lastServoPositionHit[LEFT_DIRECTION] = 0;
    lastServoPositionHit[RIGHT_DIRECTION] = 0;
}

unsigned char hasRobotObstacle(void) {
    unsigned useSonar = false;
    if (useSonar) {
        if (rangingIndex == 0) {
            // start ranging at the first index, because it takes 65 ms to have value
            startSRF02Ranging();
        }
        rangingIndex++;
        // At the end of ranging index, we get the value of distance
        if (rangingIndex == RANGING_DELAY) {
            rangingIndex = 0;
            unsigned int rangingValue = getSRF02DistanceEndRanging();
            /*
            sendDec(rangingValue);
            println();
             */

            // Manage history
            // we cancel low value, as it is often parasite
            if (rangingValue > MIN_DETECTION_DISTANCE_CM) {
                distances[distanceIndex++] = rangingValue;
                if (distanceIndex >= HISTORY_SIZE) {
                    distanceIndex = 0;
                }

                // Check the history of ranging to know
                int i = 0;
                int n = HISTORY_SIZE;
                unsigned count = 0;
                for (i = 0; i < n; i++) {
                    // char notToClosed = (distances[(i + distanceIndex) % n] > MIN_DETECTION_DISTANCE);
                    // char closed = (distances[(i + distanceIndex) % n] < OBSTACLE_DISTANCE_CM);
                    // char notToClosed = (distances[i] > MIN_DETECTION_DISTANCE_CM);
                    char closed = (distances[i] < OBSTACLE_DISTANCE_CM);
                    // if (notToClosed && closed) {
                    if (closed) {
                        count++;
                    }
                }
                if (count >= n - 2) {
                    unsigned lastLaserPosition = getLastLaserServoPosition();
                    if (lastLaserPosition > SERVO_VALUE_MIN_NOTIFY_OBSTACLE && lastLaserPosition < SERVO_VALUE_MAX_NOTIFY_OBSTACLE) {
                        //                    sendHex4(lastLaserPosition);
                        return OBSTACLE;
                    }
                }
            }
        }
        return NO_OBSTACLE;
    } else {
        // we wait time to notify again
        unsigned int currentTimeInSecond = getCurrentTimeInSecond();
        if (currentTimeInSecond > getLastNotifyObstacleTime() + OBSTACLE_DELAY_BEFORE_NEXT_NOTIFICATION) {
            if ((lastServoPositionHit[LEFT_DIRECTION] > 0) && (lastServoPositionHit[RIGHT_DIRECTION] > 0)) {
                return OBSTACLE;
            }
        }
    }
    return NO_OBSTACLE;
}

// LASER PART IMPLEMENTATION

void setMaxLeftAndRight(unsigned int left, unsigned int right) {
    maxLeft = left;
    maxRight = right;
}

signed int getAngleInDegreeWithRobot() {
    return 0;
}

int getLastLaserServoPosition(void) {
    int result = 0;
    int count = 0;
    if (lastServoPositionHit[LEFT_DIRECTION] > 0) {
        count++;
        result += lastServoPositionHit[LEFT_DIRECTION];
    }
    if (lastServoPositionHit[RIGHT_DIRECTION] > 0) {
        count++;
        result += lastServoPositionHit[RIGHT_DIRECTION];
    }
    if (count != 0) {
        return result / count;
    }
    // Clear values to avoid that the robot think that there is always an object
    lastServoPositionHit[LEFT_DIRECTION] = 0;
    lastServoPositionHit[RIGHT_DIRECTION] = 0;

    return result;
}

int getLastLaserServoWidth(void) {
    return lastServoPositionHit[RIGHT_DIRECTION] - lastServoPositionHit[LEFT_DIRECTION];
}

void setRobotDetectorSpeed(char value) {
    speed = value;
}

int min(int value1, int value2) {
    if (value1 < value2) {
        return value1;
    }
    return value2;
}

int max(int value1, int value2) {
    if (value1 > value2) {
        return value1;
    }
    return value2;
}

void updateServoPosition() {
    // Right sense
    if (direction == RIGHT_DIRECTION) {
        servoPosition++;
        // we reach the limit
        if (servoPosition > currentMaxRight) {
            // if we don't reach the target
            if (!hitDuringLast[RIGHT_DIRECTION]) {
                // we try to increase the limit
                // -> we are at the maximum
                if (servoPosition >= maxRight) {
                    // we change the turn
                    direction = LEFT_DIRECTION;
                    // reset the hit for the new direction
                    hitDuringLast[LEFT_DIRECTION] = 0;
                    laserHitCounter = 0;
                    currentMaxRight = maxRight;
                }// -> we are under the maximum
                else {
                    // we increase with the limit of MAX_RIGHT
                    currentMaxRight = min(maxRight, currentMaxRight + SHORT_TRACKING_INTERVAL);
                }
            } else {
                // we change the turn
                direction = LEFT_DIRECTION;
                // reset the hit for the new direction
                hitDuringLast[LEFT_DIRECTION] = 0;
                laserHitCounter = 0;
            }
        }
    } else {
        servoPosition--;
        if (servoPosition < currentMaxLeft) {
            // if we don't reach the target
            if (!hitDuringLast[LEFT_DIRECTION]) {
                // we try to increase    
                // -> we are at the minimum
                if (servoPosition < maxLeft) {
                    // we change the turn
                    direction = RIGHT_DIRECTION;
                    // reset the hit for the new direction
                    hitDuringLast[RIGHT_DIRECTION] = 0;
                    laserHitCounter = 0;
                    currentMaxLeft = maxLeft;
                }// -> we try to decrease the limit
                else {
                    // we decrease with the limit of MAX_RIGHT
                    currentMaxLeft = max(maxLeft, currentMaxLeft - SHORT_TRACKING_INTERVAL);
                }
            } else {
                // we change the turn
                direction = RIGHT_DIRECTION;
                // reset the hit for the new direction
                hitDuringLast[RIGHT_DIRECTION] = 0;
                laserHitCounter = 0;
            }
        }
    }
    // update the position of the servo
    pwmServo1(servoPosition);
}

void detectsLaser(void) {
    if (!robotDetectorEnabled) {
        return;
    }
    // if the laser detects something on the PIN dedicated to the laser
    if (PIN_LASER) {
        laserHitCounter++;
        if (laserHitCounter > 20) {
            // reset counter
            laserHitCounter = 0;
            // saves the position for the direction
            lastServoPositionHit[direction] = servoPosition;
            // saves that we touch the target
            hitDuringLast[direction] = 1;
            if (lastServoPositionHit[direction] != oldServoPositionHit[direction]) {
                oldServoPositionHit[direction] = lastServoPositionHit[direction];
                if (direction == RIGHT_DIRECTION) {
                    currentMaxRight = servoPosition + SHORT_TRACKING_INTERVAL;
                } else {
                    currentMaxLeft = servoPosition - SHORT_TRACKING_INTERVAL;
                }
                /*
                printValue("laserP=", getLastLaserServoPosition());    
                printValue(",laserW=", getLastLaserServoWidth());
                println();
                 */
            }
        }
    } else {
        if (laserHitCounter > 0) {
            laserHitCounter--;
        }
    }
    updatePositionCounter++;
    if (updatePositionCounter > speed) {
        updateServoPosition();
        updatePositionCounter = 0;
    }
}

unsigned char isRobotDetectorEnabled(void) {
    return robotDetectorEnabled;
}

void setRobotDetectorEnabled(unsigned char value) {
    robotDetectorEnabled = value;
}

// DEVICE INTERFACE

void initRobotDetector(void) {
    registerInterrupt(ROBOT_DETECTOR_TIMER_INDEX, 2, detectsLaser);
    currentMaxLeft = SERVO_LASER_MAX_LEFT_POSITION_DEFAULT_VALUE;
    currentMaxRight = SERVO_LASER_MAX_RIGHT_POSITION_DEFAULT_VALUE;
    lastServoPositionHit[0] = 0;
    lastServoPositionHit[1] = 0;
    oldServoPositionHit[0] = 0;
    oldServoPositionHit[1] = 0;
    hitDuringLast[0] = 0;
    hitDuringLast[1] = 0;

    lastNotifyObstacleTime = 0;

    initPwmForServo(1500);

    clearDistances();
}

void stopRobotDetector(void) {
    robotDetectorEnabled = false;
}

unsigned int isRobotDetectorDeviceOk() {
    return isSRF02DeviceWithAddressOk(SONAR_ADDRESS);
}

const char* getRobotDetectorDeviceName() {
    return "RobotDetector";
}

unsigned int getRobotDetectorSoftwareRevision() {
    return getSRF02SoftwareRevision(SONAR_ADDRESS);
}

DeviceDescriptor getRobotDetectorDeviceDescriptor() {
    DeviceDescriptor result;
    result.deviceInit = &initRobotDetector;
    result.deviceShutDown = &stopRobotDetector;
    result.deviceIsOk = &isRobotDetectorDeviceOk;
    result.deviceGetSoftwareRevision = &getRobotDetectorSoftwareRevision;
    result.deviceGetName = &getRobotDetectorDeviceName;
    result.enabled = 1;
    return result;
}
