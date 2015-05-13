#ifndef ROBOT_INFRARED_DETECTOR_H
#define ROBOT_INFRARED_DETECTOR_H

#include <stdbool.h>

#include "../../common/io/outputStream.h"

/** 
 * Define the underlying function type attached to a group to evaluate if 
 * the infrared detect something.
 */
typedef bool InfraredDetectorFunction();

/** 
 * Type of Group of Detector
 */
enum InfraredDetectorGroupType {
    /** The group of Detector to go forward. */
    DETECTOR_GROUP_TYPE_FORWARD = 0,
    /** The group of Detector to go backward. */
    DETECTOR_GROUP_TYPE_BACKWARD = 1
};

/**
 * Detection is based on 2 GPD12 on left / right, and a gp2y0a02yk on the center
 */
typedef struct InfraredDetectorGroup {
    // DEFINITION VALUES
    /** Group Type. */
    enum InfraredDetectorGroupType type;
    /** The function to evaluate it. */
    InfraredDetectorFunction* function;
    /** If we must notify when we detects something */
    bool notifyIfDetected;
    // COMPUTATION VALUES
    /** Returns the last Result. */
    bool lastResult;    
    /** Current result : we try to maintain the value for a while. */
    bool result;
    /** Indicates if we have to notify someone. */
    bool notifyFlag;
    /** A counter to avoid to notify to often. */
    int nextNotifyCounter;
    /** The number of count which was detected. */
    int detectedCount;
} InfraredDetectorGroup;

/** 
 * Initializes a group of detector.
 * @param the type of group of detector (backward / forward)
 * @param function the function to evaluate if there is a detection associated with the group
 */
void initInfraredDetectorGroup(InfraredDetectorGroup* group, enum InfraredDetectorGroupType type, InfraredDetectorFunction* function);

/**
 * Encapsulates the all informations about detector
 */
typedef struct RobotInfraredDetector {
    /** Group of detector for forward move. */
    InfraredDetectorGroup forwardDetectorGroup;
    /** Group of detector for backward. */
    InfraredDetectorGroup backwardDetectorGroup;
} RobotInfraredDetector;

/**
 * Init and a timer to search via infrared detector.
 */
void initRobotInfraredDetector(RobotInfraredDetector* robotInfraredDetector);

// READ VALUES

/**
 * Returns if there is an obstacle forward.
 */
bool getRobotInfraredObstacleForward(void);

/**
 * Returns if there is an obstacle backward.
 */
bool getRobotInfraredObstacleBackward(void);

// NOTIFY MANAGEMENT

void setInfraredRobotNotification(enum InfraredDetectorGroupType type, bool enable);

bool mustNotifyRobotInfraredObstacleForward(void);

bool mustNotifyRobotInfraredObstacleBackward(void);

void resetNotifyRobotInfraredObstacleForward(void);

void resetNotifyRobotInfraredObstacleBackward(void);

// SINGLETON

/** 
 * Returns the global instance of RobotInfrared.
 */
RobotInfraredDetector* getRobotInfraredDetector(void);

// DEBUG

void printRobotInfraredDetectorGroup(OutputStream* outputStream, InfraredDetectorGroup* group);

#endif
